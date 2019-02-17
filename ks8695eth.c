/*
 * ks8695eth.c -- KS8695 ethernet driver
 *
 * (C) Copyright 2004-2005, Greg Ungerer <greg.ungerer@opengear.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/****************************************************************************/

#include "sys/types.h"
#include "string.h"
#include "platform.h"

static void ks8695_dump_packet(int port, int dir, unsigned char *data, int len);

/****************************************************************************/

/*
 * Hardware register access to the KS8695 LAN ethernet port
 * (well, it is the 4 port switch really).
 */

/****************************************************************************/

/*
 * Define the descriptor in-memory data structures.
 */

struct ks8695_txdesc {
	uint32_t	owner;
	uint32_t	ctrl;
	uint32_t	addr;
	uint32_t	next;
};

struct ks8695_rxdesc {
	uint32_t	status;
	uint32_t	ctrl;
	uint32_t	addr;
	uint32_t	next;
};

/****************************************************************************/

/*
 * Allocate local data structures to use for receiving and sending
 * packets. Just to keep it all nice and simple.
 */

#define	TXDESCS		4
#define	RXDESCS		8
#define	BUFSIZE		2048

volatile struct ks8695_txdesc ks8695_tx[TXDESCS] __attribute__((aligned(256)));
volatile struct ks8695_rxdesc ks8695_rx[RXDESCS] __attribute__((aligned(256)));
volatile uint8_t ks8695_bufs[BUFSIZE*(TXDESCS+RXDESCS)] __attribute__((aligned(2048)));;

static int lanrx_index, lantx_index;
static int use_wan,save_use_wan, cmd_forced_use=0;
//struct net_device_stats ether_net_stats[2];
//static uint pkt_dump_flag=0, pkt_dump_port=NONE_PORT;


#ifdef CONFIG_NET_MULTI
static int force_use_wan = 0;
#endif

/****************************************************************************/

/*
 *	Ideally we want to use the MAC address stored in flash.
 *	But we do some sanity checks in case they are not present
 *	first.
 */
unsigned char default_eth_mac[] = {
#ifdef UBOOT_ORIG
	0x00, 0x13, 0xc6, 0x00, 0x00, 0x00
#else
	0x00, 0x10, 0xA1, 0x86, 0x95, 0x01
#endif
};
unsigned char eth_mac[] = { 0, 0, 0, 0, 0, 0 };


#if 0
#if 0
static int atoi(int i)
{
	if( i >= '0' && i <= '9' )
		return i-'0';
	else if( i >= 'a' && i <= 'f' )
		return i - 'a' + 10;
	else if( i >= 'A' && i <= 'F' )
		return i - 'A' + 10;
	else {
		xprintf("Input for ASCII conversion is wrong[0x%x]\n",i);
		return i;
	}
}

void ks8695_getmac(void)
{
	unsigned char *fp;
	unsigned char temp[32];

	memset(temp,0x00,sizeof(temp));
	fp = ( unsigned char* ) getenv("ethaddr");
	if (fp != NULL ) {
		eth_mac[0] = ( atoi( *(fp+0) ) << 4 | atoi( *(fp+1)) );
		eth_mac[1] = ( atoi( *(fp+3) ) << 4 | atoi( *(fp+4)) );
		eth_mac[2] = ( atoi( *(fp+6) ) << 4 | atoi( *(fp+7)) );
		eth_mac[3] = ( atoi( *(fp+9) ) << 4 | atoi( *(fp+10)) );
		eth_mac[4] = ( atoi( *(fp+12) ) << 4 | atoi( *(fp+13)) );
		eth_mac[5] = ( atoi( *(fp+15) ) << 4 | atoi( *(fp+16)) );
	}
}
#endif

#endif

/****************************************************************************/

static int eth_initted = 0;

void eth_reset()
{
	uint i;
	int nTimeOut = 1000;
	unsigned int uReg;

	ks8695_write(KS8695_SWITCH_LPPM12, 0x0);
	ks8695_write(KS8695_SWITCH_LPPM34, 0x0);

//	debug ("%s(%d): eth_reset()\n", __FILE__, __LINE__);

	if ( eth_initted )
		goto skip_reset;

	/* Reset the ethernet engines first */
	ks8695_write(KS8695_WAN_DMA_TX, 0x80000000);
	ks8695_write(KS8695_WAN_DMA_RX, 0x80000000);
	ks8695_write(KS8695_LAN_DMA_TX, 0x80000000);
	ks8695_write(KS8695_LAN_DMA_RX, 0x80000000);
	lanrx_index = 0;
	lantx_index = 0;

	do
	{
		uReg = ks8695_read(KS8695_LAN_DMA_TX);
		if (!(uReg & 0x80000000))
			break;
	} while (--nTimeOut);

//	if (nTimeOut < 1) 
//	    debug ("%s(%d): eth_reset() ERROR!\n", __FILE__, __LINE__);

	/* Initialize descriptor rings */
	for (i = 0; (i < TXDESCS); i++) {
		ks8695_tx[i].owner = 0;
		ks8695_tx[i].ctrl = 0;
		ks8695_tx[i].addr = (uint32_t) &ks8695_bufs[i*BUFSIZE];
		ks8695_tx[i].next = (uint32_t) &ks8695_tx[i+1];
	}
	ks8695_tx[TXDESCS-1].ctrl = 0x02000000;
	ks8695_tx[TXDESCS-1].next = (uint32_t) &ks8695_tx[0];

	for (i = 0; (i < RXDESCS); i++) {
		ks8695_rx[i].status = 0x80000000;
		ks8695_rx[i].ctrl = BUFSIZE - 4;
		ks8695_rx[i].addr = (uint32_t) &ks8695_bufs[(i+TXDESCS)*BUFSIZE];
		ks8695_rx[i].next = (uint32_t) &ks8695_rx[i+1];
	}
	ks8695_rx[RXDESCS-1].ctrl |= 0x00080000;
	ks8695_rx[RXDESCS-1].next = (uint32_t) &ks8695_rx[0];

	/* Enable the ethernet engine */
	ks8695_write(KS8695_LAN_TX_LIST, (uint32_t) &ks8695_tx[0]);
	ks8695_write(KS8695_LAN_RX_LIST, (uint32_t) &ks8695_rx[0]);
	ks8695_write(KS8695_WAN_TX_LIST, (uint32_t) &ks8695_tx[0]);
	ks8695_write(KS8695_WAN_RX_LIST, (uint32_t) &ks8695_rx[0]);

	eth_initted = 1;
	cmd_forced_use = 1;

skip_reset:
/*	this flag is set while executing one of ether-related cli commands */
	if ( cmd_forced_use )
	{
		/* enable to rx broadcast/multicast/unicast */
		uReg = 0x71;
	}
	else
	{

#ifdef WAN_PRIORITY
		i = ks8695_read(KS8695_WAN_CONTROL);
        	if ( ( i & ( 1 << 23 )) ) {
			use_wan = 1;
        	}
        	else {
			use_wan = 0;
        	}
#else
        	i = ks8695_read(KS8695_SWITCH_AUTO0) ;
        	i |= ks8695_read(KS8695_SWITCH_AUTO1) ;

        	if( (((i >> 30) & 0x1 ) && ((i >> 23) & 0x1)) || 
        	    (((i >> 14) & 0x1 ) && ((i >> 7) & 0x1))) {
			use_wan = 0;
        	}
        	else {
			use_wan = 1;
        	}
#endif
		/* enable to rx unicast */
		uReg = 0x11;
	}

#ifdef CONFIG_NET_MULTI
	/* Specified port has no link. */
	if ( ( force_use_wan  &&  !use_wan )  ||
			( !force_use_wan  &&  use_wan ) ) {
		/* Need to reset the other port. */
		eth_initted = 0;
		return;
	}
#endif

#define	FLOW_CONTROL	0x08000200

	if ( use_wan ) {
		/* Set MAC address */
		ks8695_write(KS8695_WAN_MAC_LOW, (eth_mac[5] |
			(eth_mac[4] << 8) |
			(eth_mac[3] << 16) | (eth_mac[2] << 24)));
		ks8695_write(KS8695_WAN_MAC_HIGH, (eth_mac[1] |
			(eth_mac[0] << 8)));
		ks8695_write(KS8695_WAN_DMA_TX, 0x03 | FLOW_CONTROL );
		ks8695_write(KS8695_WAN_DMA_RX, uReg | FLOW_CONTROL );

		/* Put WAN port in normal mode to enable receive. */
		uReg = ks8695_read( 0xEA10 );
		/* For KS8695X. */
		uReg &= ~( 1 << 1 );
		/* For KS8695P. */
		uReg &= ~( 1 << 14 );
		ks8695_write( 0xEA10, uReg );
	}
	else {
		/* Set MAC address */
		ks8695_write(KS8695_LAN_MAC_LOW, (eth_mac[5] |
			(eth_mac[4] << 8) |
			(eth_mac[3] << 16) | (eth_mac[2] << 24)));
		ks8695_write(KS8695_LAN_MAC_HIGH, (eth_mac[1] |
			(eth_mac[0] << 8)));
		ks8695_write(KS8695_LAN_DMA_TX, 0x03 | FLOW_CONTROL );
		ks8695_write(KS8695_LAN_DMA_RX, uReg | FLOW_CONTROL );
	}

	if ( use_wan ) {
		ks8695_write(KS8695_WAN_DMA_RX_START, 0x1);
	}
	else {

		/* Turn the 4 port switch on */
		i = ks8695_read(KS8695_SWITCH_CTRL0);

		/* Turn on fast aging. */
		i |= 1 << 20;
		ks8695_write(KS8695_SWITCH_CTRL0, (i | 0x1));
		/* ks8695_write(KS8695_WAN_CONTROL, 0x3f000066); */

		ks8695_write(KS8695_LAN_DMA_RX_START, 0x1);
	}
}

#if 0
/****************************************************************************/

#ifdef CONFIG_NET_MULTI
static int  ksz_init (
	struct eth_device* dev,
#else
int eth_init (
#endif
	bd_t *bd)
{
	debug ("%s(%d): eth_init()\n", __FILE__, __LINE__);

#ifdef CONFIG_NET_MULTI
	if ( *(( int* ) dev->enetaddr ) == 0 ) {
		memcpy( eth_mac, default_eth_mac, 6 );
		if ( KS8695_WAN_DMA_TX == dev->iobase )
			eth_mac[ 5 ] ^= 0x10;
		memcpy( dev->enetaddr, eth_mac, 6 );
	}
	if ( KS8695_WAN_DMA_TX == dev->iobase )
		force_use_wan = 1;
	else
		force_use_wan = 0;
#endif
	if ( *(( int* ) bd->bi_enetaddr ) == 0 ) {
		memcpy( eth_mac, default_eth_mac, 6 );
		eth_mac[ 5 ] ^= 0x10;
		memcpy( bd->bi_enetaddr, eth_mac, 6 );
	}
#ifdef CONFIG_HAS_ETH1
	if ( *(( int* ) bd->bi_enet1addr ) == 0 ) {
		memcpy( eth_mac, default_eth_mac, 6 );
		memcpy( bd->bi_enet1addr, eth_mac, 6 );
	}
#endif

#ifdef CONFIG_NET_MULTI
	memcpy( eth_mac, dev->enetaddr, 6 );
#else
	memcpy( eth_mac, bd->bi_enetaddr, 6 );
	eth_initted = 0;
#endif

	eth_reset(bd);

#ifdef CONFIG_NET_MULTI
	if ( ( KS8695_WAN_DMA_TX == dev->iobase  &&  !use_wan )  ||
			( KS8695_LAN_DMA_TX == dev->iobase  &&  use_wan ) )
		return 0;
#endif
	return 1;
}

/****************************************************************************/

#ifdef CONFIG_NET_MULTI
static void ksz_halt (struct eth_device* dev)
#else
void eth_halt (void)
#endif
{
	unsigned int uReg;

	debug ("%s(%d): eth_halt()\n", __FILE__, __LINE__);

	/* Disable LAN MAC DMA transmit */
	uReg = ks8695_read(KS8695_LAN_DMA_TX);
	ks8695_write(KS8695_LAN_DMA_TX, (uReg & ~0x1));

	/* Disable LAN MAC DMA receive */
	uReg = ks8695_read(KS8695_LAN_DMA_RX);
	ks8695_write(KS8695_LAN_DMA_RX, (uReg & ~0x1));

	/* This is required to avoid the same problem in WAN port in which it
	   cannot receive after disabled.
	 */
	/* Disable Switch to receive or transmit */
	uReg = ks8695_read(KS8695_SWITCH_CTRL0);
	ks8695_write(KS8695_SWITCH_CTRL0, (uReg & ~0x1));

	/* Put WAN port in loopback mode to shut off receive. */
	uReg = ks8695_read( 0xEA10 );
	/* For KS8695X. */
	uReg |= ( 1 << 1 );
	/* For KS8695P. */
	uReg |= ( 1 << 14 );
	ks8695_write( 0xEA10, uReg );

	/* Disable WAN MAC DMA transmit */
	uReg = ks8695_read(KS8695_WAN_DMA_TX);
	ks8695_write(KS8695_WAN_DMA_TX, (uReg & ~0x1));

	/* Disable WAN MAC DMA receive */
	uReg = ks8695_read(KS8695_WAN_DMA_RX);
	ks8695_write(KS8695_WAN_DMA_RX, (uReg & ~0x1));
}

#endif
/****************************************************************************/

#ifdef CONFIG_NET_MULTI
static int  ksz_recv (struct eth_device* dev)
#else
int eth_rx (void)
#endif
{
	volatile struct ks8695_rxdesc *dp;
	int len = 0;

//	int portid = use_wan ? WAN_PORT : LAN_PORT;

	dp = &ks8695_rx[lanrx_index];

	while ((dp->status & 0x80000000) == 0) {
		len = (dp->status & 0x7ff) - 4;
//                ks8695_dump_packet(portid,INBOUND,(unsigned char*)dp->addr,len);
//		NetReceive((void *) dp->addr, len);
		net_rcv(dp->addr, len);
		dp->status = 0x80000000;
//                STAT_NET(portid,rx_packets++);
//                STAT_NET(portid,rx_bytes) += len;
		if (++lanrx_index >= RXDESCS)
			lanrx_index = 0;
		dp = &ks8695_rx[lanrx_index];
	}

	if ( len ) {
		if ( use_wan )
			ks8695_write(KS8695_WAN_DMA_RX_START, 0x1);
		else
			ks8695_write(KS8695_LAN_DMA_RX_START, 0x1);
	}

	return len;
}

/****************************************************************************/

#ifdef CONFIG_NET_MULTI
static int  ksz_send (
	struct eth_device* dev,
#else
int eth_send (
#endif
	volatile void *packet, int len)
{
	volatile struct ks8695_txdesc *dp;

//	debug ("%s(%d): eth_send(packet=%x,len=%d)\n", __FILE__, __LINE__,
//		packet, len);

	dp = &ks8695_tx[lantx_index];
	while( dp->owner & 0x80000000 ) ;
	memcpy((void *) dp->addr, (void *) packet, len);

	if (len < 64) {
		memset((void *) (dp->addr + len), 0, 64-len);
		len = 64;
	}

	dp->ctrl = len | 0xe0000000;
	dp->owner = 0x80000000;

	if ( use_wan ) {
		ks8695_write(KS8695_WAN_DMA_TX_START, 0x1);
/* Staticstic & packet dump */
//        	STAT_NET(WAN_PORT,tx_packets++);
//        	STAT_NET(WAN_PORT,tx_bytes) += len;
//        	ks8695_dump_packet(WAN_PORT,OUTBOUND,(unsigned char*)packet,len);
	}

	else {
		ks8695_write(KS8695_LAN_DMA_TX_START, 0x1);
/* Staticstic & packet dump */
//        	STAT_NET(LAN_PORT,tx_packets++);
//        	STAT_NET(LAN_PORT,tx_bytes) += len;
//        	ks8695_dump_packet(LAN_PORT,OUTBOUND,(unsigned char*)packet,len);
	}

	if (++lantx_index >= TXDESCS)
		lantx_index = 0;

	return len;
}

#if 0
void eth_link_status(struct eth_linksts *ptr )
{
	uint	i;
	memset(ptr,0x00,sizeof(struct eth_linksts));

	ptr->deviceid = ks8695_read(KS8695_DEVICE_ID) & 0xffff;
	i = ks8695_read(KS8695_WAN_CONTROL);
        if( (i >> 30) & 0x1 ) ptr->wanport =  (i >> 23) & 0x1;
        i = ks8695_read(KS8695_MANAGE_DATA);

        if( (i >> 30) & 0x1 )
		ptr->lanport[0] =  (i >> 23) & 0x1 ;
        if( (i >> 14) & 0x1 )
        	ptr->lanport[1] =  (i >> 7) & 0x1 ;

        i = ks8695_read(KS8695_LAN12_POWERMAGR) ;
        if( (i >> 30) & 0x1 )
		ptr->lanport[2] =  (i >> 23) & 0x1 ;
        if( (i >> 14) & 0x1 )
        	ptr->lanport[3] =  (i >> 7) & 0x1 ;

}

int eth_init_cmd(unsigned int portid)
{
        DECLARE_GLOBAL_DATA_PTR;
        bd_t *bd = gd->bd;
	cmd_forced_use = 1;
	save_use_wan = use_wan;
	/* overwrite use_wan */
	use_wan = (portid == WAN_PORT ) ? 1 : 0;
	return eth_init(bd);
}

void get_mib_reset(void);

void eth_halt_cmd(void)
{
	cmd_forced_use = 0;
#if 0
	get_mib_reset();
#endif
	use_wan = save_use_wan;
}


void eth_pktdump_update(uint port, uint flag)
{
        pkt_dump_port = port;
	pkt_dump_flag = flag;
}

void eth_buffer_link(uint BufNum,uint BufLen,uint SameBuf)
{
	char *pTxBuf = ( char* )( TEST_BUFFER_START );
	volatile struct ks8695_txdesc *dp;

	int	descinx=lantx_index;
	int	bufinx=0;
	int	lpcnt=0;

	for( lpcnt=0; lpcnt < TXDESCS; lpcnt++ )
	{	
		char *srcptr, *destptr;
		dp = &ks8695_tx[descinx];
		destptr = (char *)dp->addr;
		srcptr = (char *)(pTxBuf + (BufNum + bufinx)%TEST_BUFFER_COUNT * TEST_BUFSIZ);

		memcpy(destptr,srcptr,BufLen);

		if(!SameBuf) bufinx++;
		descinx = (descinx+1)%TXDESCS;
	}
}

int eth_send_fast(uint BufLen, uint cnt)
{
        volatile struct ks8695_txdesc *dp;
        uint    icnt=0;

	/* check only the last packet being sent. */
        while ( ks8695_tx[ (lantx_index+cnt-1)%TXDESCS ].owner & 0x80000000 ) ;

        for( icnt=0; icnt < cnt; ++icnt)
        {
                dp = &ks8695_tx[lantx_index];
                dp->ctrl = BufLen | 0xe0000000;
                dp->owner = 0x80000000;
                lantx_index = (lantx_index+1)%TXDESCS;
        }

	if ( use_wan ) {
		ks8695_write(KS8695_WAN_DMA_TX_START, 0x1);
	}

	else {
		ks8695_write(KS8695_LAN_DMA_TX_START, 0x1);
	}

	return BufLen;
}



int eth_rx_fast(void)
{
	volatile struct ks8695_rxdesc *dp;
	int len = 0;

	int portid = use_wan ? WAN_PORT : LAN_PORT;

	dp = &ks8695_rx[lanrx_index];

	while ((dp->status & 0x80000000) == 0) {
		len = (dp->status & 0x7ff) - 4;
                ks8695_dump_packet(portid,INBOUND,(unsigned char*)dp->addr,len);
		dp->status = 0x80000000;
                STAT_NET(portid,rx_packets++);
                STAT_NET(portid,rx_bytes) += len;
		if (++lanrx_index >= RXDESCS)
			lanrx_index = 0;
		dp = &ks8695_rx[lanrx_index];
	}

	if ( len ) {
		if ( use_wan )
			ks8695_write(KS8695_WAN_DMA_RX_START, 0x1);
		else
			ks8695_write(KS8695_LAN_DMA_RX_START, 0x1);
	}

	return len;
}


void get_ks8695_geninfo( struct genInfo *buf)
{
        strcpy(buf->portName, use_wan==1 ? "WAN" : "LAN");
        buf->txdesc = TXDESCS;
        buf->rxdesc = RXDESCS;
        buf->txdesc_addr = (uint) ks8695_tx;
        buf->rxdesc_addr = (uint) ks8695_rx;
        buf->bufsize = BUFSIZE;
        buf->bufstart = (uint) ks8695_bufs;
}

static void ks8695_dump_packet(int port, int dir, unsigned char *data, int len)
{
        /* we may need to have locking mechamism to use this function, since Rx call it within INT context
           and Tx call it in normal context */

        if ( pkt_dump_port >= NONE_PORT )
                return;

        if( pkt_dump_port != ALL_PORT &&  pkt_dump_port != port )
                return;

        if (pkt_dump_flag && len >= 18) {
		if( use_wan )
                	xprintf("\nWAN %s ", dir==INBOUND ? "Rx" : "Tx");
		else
                	xprintf("\nLAN Port=%d %s ", port, dir==INBOUND ? "Rx" : "Tx");
                if (pkt_dump_flag & DEBUG_PACKET_LEN) {
                        xprintf("Pkt-Len=0x%x\n", len);
                }
		else
                        xprintf("\n");

                if (pkt_dump_flag & DEBUG_PACKET_CONTENT) {
                        int     j = 0, k;

                        do {
                                xprintf(" %08x   ", (int)(data+j));
                                for (k = 0; (k < 16 && len); k++, data++, len--) {
                                        xprintf("%02x  ", *data);
                                }
                        	xprintf("\n");
                                j += 16;
                        } while (len > 0);
                        xprintf("\n");
                }
        }
}
#endif

#define	KS8695_SEIAC	0xE850
#define	KS8695_SEIADL	0xE85C
void get_mib_reset( )
{
	unsigned long reg,value=0;

	/* Use LAN port 4. */
	for (reg = 0x1c60; reg <= 0x1c7f; reg++)
	{
		ks8695_write(KS8695_SEIAC, reg);
		value = ks8695_read(KS8695_SEIADL);
	}
	for (reg = 0x1d00; reg <= 0x1d09; reg++)
	{
		ks8695_write(KS8695_SEIAC, reg);
		value = ks8695_read(KS8695_SEIADL);
	}
}

static uint ks8695_read_rep( uint reg )
{
	unsigned int value = 0;
	unsigned int cnt=0;
	while( ++cnt < 10000 )
	{
		value = ks8695_read(reg) ;
		if( value & 0x40000000 ) break;
		udelay(1000);
	}
	if( cnt >= 10000 )
		xprintf("Fail to read reg=0x%lx value=0x%lx\n", reg,value);
	return (value & 0x3fffffff);
}


void get_mib_count( uint *ptr)
{
	unsigned long reg;
	uint	*uptr = (uint *)ptr;
	
	/* Use LAN port 4. */
	for (reg = 0x1c60; reg < 0x1c80; reg++)
	{
		ks8695_write(KS8695_SEIAC, reg);
		*uptr = (uint) ks8695_read_rep(KS8695_SEIADL) ;
		uptr++;
	}
	for (reg = 0x1d00; reg < 0x1d0a; reg++)
	{
		ks8695_write(KS8695_SEIAC, reg);
		*uptr = (uint)( ks8695_read(KS8695_SEIADL) & 0xffff );
		uptr++;
	}
}

