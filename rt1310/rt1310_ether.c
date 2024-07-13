/*
 * Copyright (c) 2024 Hiroki Mori. All rights reserved.
 */

#include <string.h>

#include "rt1310.h"
#include "rt1310_reg.h"
#include "rt1310_etherreg.h"

#include "lwip/init.h"

#include "lwip/debug.h"

#include "lwip/ethip6.h"
#include "lwip/etharp.h"
#include "netif/ethernet.h"

struct netif netif;

struct ethernetif {
	unsigned char		eth_mac[6];
	struct fv_desc		*txdesc_ring;
	struct fv_desc		*rxdesc_ring;
	int			inten;
	int			txnext;
	int			rxnext;
};

extern unsigned char default_eth_mac[];

#define INQEULEN 16
 
struct pbuf *inque[INQEULEN];
int inquestart;
int inqueend;

static int miibus_readreg(int, int, uint16_t *);

#define TXDESC_NEXT(x) txdesc_adjust((x), 1)
#define TXDESC_PREV(x) txdesc_adjust((x), -1)

#define RXDESC_NEXT(x) rxdesc_adjust((x), 1)
#define RXDESC_PREV(x) rxdesc_adjust((x), -1)

static inline int
txdesc_adjust(int x, int y)
{
	int res = x + y + FV_TX_RING_CNT;
	return res % FV_TX_RING_CNT;
}

static inline int
rxdesc_adjust(int x, int y)
{
	int res = x + y + FV_RX_RING_CNT;
	return res % FV_RX_RING_CNT;
}

eninque(struct pbuf *p)
{
	inque[inqueend] = p;
	++inqueend;
	if (inqueend == INQEULEN)
		inqueend = 0;
}

doque()
{
err_t err;
  
	if(inquestart != inqueend) {
		while (inquestart != inqueend) {
			err = netif.input(inque[inquestart], &netif);
			if (err != ERR_OK) {
				pbuf_free(inque[inquestart]);                  
			}
			++inquestart;
			if (inquestart == INQEULEN)
				inquestart = 0;
		}
	}
}

static err_t
low_level_output(struct netif *netif, struct pbuf *p)
{
	struct ethernetif *eth = netif->state;
	struct fv_desc *tdesc;
	tdesc = &eth->txdesc_ring[eth->txnext];
	memcpy(tdesc->fv_addr, p->payload, p->tot_len);
	tdesc->fv_stat = ADSTAT_OWN;
	tdesc->fv_devcs = FV_DMASIZE(p->tot_len);
	tdesc->fv_devcs |= ADCTL_Tx_FS | ADCTL_Tx_LS;
	if (eth->txnext == FV_TX_RING_CNT - 1)
		tdesc->fv_devcs |= ADCTL_ER;
	eth->txnext = TXDESC_NEXT(eth->txnext);

	rt1310_write(RT_MAC0_BASE + CSR_TXPOLL, TXPOLL_TPD);

	return ERR_OK;
}

int findenv(char *name, char *buf, char *res, int size)
{
char *ptr;
int len;
int i = 0;
char key[128];

	ptr = buf + 4;

	while(1) {
		for (i = 0; *(ptr + i) != '=' && i < sizeof(key) - 1; ++i)
			key[i] = *(ptr + i);
		key[i] = '\0';
		ptr += i + 1;
		if (strcmp(key, name) == 0) {
			if (strlen(ptr) < size) {
				strcpy(res, ptr);
				return 1;
			} else {
				return 0;
			}
		}
		for (; *ptr != '\0'; ++ptr) ;
		++ptr;
		if (*ptr == '\0') {
			res = '\0';
			return 0;
		}
	}
}

void
setfilt(struct ethernetif *eth)
{
uint16_t eaddr[3];
uint16_t *sp;

	sp = eth->txdesc_ring[eth->txnext].fv_addr;

	memset(sp, 0xff, FV_SFRAME_LEN);

	memcpy(eaddr, eth->eth_mac, 6);
	sp[90] = sp[91] = eaddr[0];
	sp[92] = sp[93] = eaddr[1];
	sp[94] = sp[95] = eaddr[2];

	eth->txdesc_ring[eth->txnext].fv_stat = ADSTAT_OWN;
	eth->txdesc_ring[eth->txnext].fv_devcs = ADCTL_Tx_SETUP |
	    FV_DMASIZE(FV_SFRAME_LEN);
 
	eth->txnext = TXDESC_NEXT(eth->txnext);

	rt1310_write(RT_MAC0_BASE + CSR_TXPOLL, 0xFFFFFFFF);
}

ethernetif_init(struct netif *netif)
{
struct ethernetif *ethernetif;
char *envp;
char *buffp;
char macstr[32];
char *macptr;
int i;

	ethernetif = mem_malloc(sizeof(struct ethernetif));
	if (ethernetif == NULL) {
		LWIP_DEBUGF(NETIF_DEBUG, ("ethernetif_init: out of memory?n"));
		return ERR_MEM;
	}

	netif->state = ethernetif;
	netif->name[0] = 'f';
	netif->name[1] = 'v';

	netif->output = etharp_output;
	netif->output_ip6 = ethip6_output;
	netif->linkoutput = low_level_output;

	envp = FLASH_ADDR + UBOOTENVOFFSET;
	if (findenv("ethaddr", envp, macstr, sizeof(macstr))) {
		macptr = macstr;
	} else {
		macptr = "12:34:56:78:9a:bc";
	}
	xprintf("%s\n", macptr);

	netif->hwaddr_len = ETHARP_HWADDR_LEN;
	enet_parse_hwaddr(macptr, netif->hwaddr);
	memcpy(ethernetif->eth_mac, netif->hwaddr, netif->hwaddr_len);
/*
	for (i=0;i < 16;++i) {
	uint16_t val;
	miibus_readreg(0, i, &val);
	xprintf("%x\n", val);
	}
*/

	netif->mtu = 1500;
	netif->flags = NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP |
	    NETIF_FLAG_LINK_UP;

	irq_enable(RT_INTC_MAC0INT, ethernetif);

	ethernetif->txdesc_ring = (PYMEMEND & 0xfff00000);
	memset(ethernetif->txdesc_ring, 0, sizeof(struct fv_desc) *
	    FV_TX_RING_CNT);
	buffp = (PYMEMEND & 0xfff00000) + 0x80000;
	for (i = 0;i < FV_TX_RING_CNT; ++i) {
		ethernetif->txdesc_ring[i].fv_addr = buffp + 2048 * i;
	}
	ethernetif->txnext = 0;
	ethernetif->rxnext = 0;

	ethernetif->rxdesc_ring = (PYMEMEND & 0xfff00000) + 0x40000;
	memset(ethernetif->rxdesc_ring, 0, sizeof(struct fv_desc) *
	    FV_RX_RING_CNT);
	buffp = (PYMEMEND & 0xfff00000) + 0xc0000;
	for (i = 0;i < FV_RX_RING_CNT; ++i) {
		ethernetif->rxdesc_ring[i].fv_stat = ADSTAT_OWN;
		ethernetif->rxdesc_ring[i].fv_addr = buffp + 2048 * i;
		ethernetif->rxdesc_ring[i].fv_devcs = PKT_BUF_SZ;
	}
	ethernetif->rxdesc_ring[i - 1].fv_devcs |= ADCTL_ER;

//	rt1310_write(RT_MAC0_BASE + CSR_BUSMODE, BUSMODE_SWR);
	rt1310_write(RT_MAC0_BASE + CSR_BUSMODE, BUSMODE_BAR | BUSMODE_PBL_32LW);

	/* normal interrupts */
	ethernetif->inten = STATUS_TI | STATUS_TU | STATUS_RI | STATUS_NIS;

	ethernetif->inten |= STATUS_TPS | STATUS_TJT | STATUS_UNF |
	    STATUS_RU | STATUS_RPS | STATUS_SE | STATUS_AIS;

	rt1310_write(RT_MAC0_BASE + CSR_INTEN, ethernetif->inten);
	rt1310_write(RT_MAC0_BASE + CSR_STATUS, 0xffffffff);

	/*
	 * Give the transmit and receive rings to the chip.
	 */
	rt1310_write(RT_MAC0_BASE + CSR_TXLIST, ethernetif->txdesc_ring);
	rt1310_write(RT_MAC0_BASE + CSR_RXLIST, ethernetif->rxdesc_ring);

	inquestart = 0;
	inqueend = 0;

	/*
	 * Set the station address.
	 */
	setfilt(ethernetif);

	/*
	 * Write out the opmode.
	 */
	rt1310_write(RT_MAC0_BASE + CSR_OPMODE, OPMODE_SR | OPMODE_ST |
	    OPMODE_TR_128 | OPMODE_FDX | OPMODE_SPEED);

	/*
	 * Start the receive process.
	 */
	rt1310_write(RT_MAC0_BASE + CSR_RXPOLL, RXPOLL_RPD);

	return ERR_OK;
}

void net_rcv(char *data, int len)
{
struct pbuf *p;
int i;

	p = pbuf_alloc(PBUF_RAW, len, PBUF_POOL);
	pbuf_take(p, data, len);

	eninque(p);
/*
	if (netif.input(p, &netif) != ERR_OK) {
		pbuf_free(p);
		p = NULL;
	}
*/
}

void ether_intr(void *arg)
{
	int status;
	struct ethernetif *eth = (struct ethernetif *)arg;
	struct fv_desc *rdesc;
	int len;

	status = rt1310_read(RT_MAC0_BASE + CSR_STATUS);
	rt1310_write(RT_MAC0_BASE + CSR_STATUS, status);
	if (status & STATUS_RI) {
		for (;;) {
			rdesc = &eth->rxdesc_ring[eth->rxnext];
			if (rdesc->fv_stat & ADSTAT_OWN)
				break;
			len = ADSTAT_Rx_LENGTH(rdesc->fv_stat);
			net_rcv((char *)rdesc->fv_addr, len);
			rdesc->fv_stat = ADSTAT_OWN;
			rdesc->fv_devcs = PKT_BUF_SZ;
			if (eth->rxnext == FV_RX_RING_CNT - 1)
				rdesc->fv_devcs |= ADCTL_ER;
			eth->rxnext = RXDESC_NEXT(eth->rxnext);
		}
	}
}

static int
miibus_readbits(int count)
{
	int result;

	result = 0;
	while(count--) {
		result <<= 1;
		rt1310_write(RT_MAC0_BASE + CSR_MIIMNG, MII_RD);
		delay_ms(10);
		rt1310_write(RT_MAC0_BASE + CSR_MIIMNG, MII_RD | MII_CLK);
		delay_ms(10);
		if (rt1310_read(RT_MAC0_BASE +CSR_MIIMNG) & MII_DIN)
			result |= 1;
	}

	return (result);
}

static int
miibus_writebits(int data, int count)
{
	int bit;

	while(count--) {
		bit = ((data) >> count) & 0x1 ? MII_DOUT : 0;
		rt1310_write(RT_MAC0_BASE + CSR_MIIMNG, bit | MII_WR);
		delay_ms(10);
		rt1310_write(RT_MAC0_BASE + CSR_MIIMNG, bit | MII_WR | MII_CLK);
		delay_ms(10);
	}

	return (0);
}

static void
miibus_turnaround(int cmd)
{
	if (cmd == MII_WRCMD) {
		miibus_writebits(0x02, 2);
	} else {
		miibus_readbits(1);
	}
}

static int
miibus_readreg(int phy, int reg, uint16_t *val)
{

	miibus_writebits(MII_PREAMBLE, 32);
	miibus_writebits(MII_RDCMD, 4);
	miibus_writebits(phy, 5);
	miibus_writebits(reg, 5);
	miibus_turnaround(MII_RDCMD);
	*val = miibus_readbits(16);
	miibus_turnaround(MII_RDCMD);

	return 0;
}

static int
miibus_writereg(int phy, int reg, uint16_t val)
{

	miibus_writebits(MII_PREAMBLE, 32);
	miibus_writebits(MII_WRCMD, 4);
	miibus_writebits(phy, 5);
	miibus_writebits(reg, 5);
	miibus_turnaround(MII_WRCMD);
	miibus_writebits(val, 16);

	return 0;
}
