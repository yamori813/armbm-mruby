/*
 * Copyright (c) 2019 Hiroki Mori. All rights reserved.
 */

#include <string.h>

#include "platform.h"

#include "lwip/init.h"

#include "lwip/debug.h"

#include "lwip/etharp.h"
#include "netif/ethernet.h"

struct netif netif;

struct ethernetif {
  struct eth_addr *ethaddr;
  /* Add whatever per-interface state that is needed here. */
};

static err_t
low_level_output(struct netif *netif, struct pbuf *p)
{
	eth_send(p->payload, p->tot_len);
	return ERR_OK;
}

extern unsigned char default_eth_mac[];
extern unsigned char eth_mac[];

#define INQEULEN 16
 
struct pbuf *inque[INQEULEN];
int inquestart;
int inqueend;

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

ethernetif_init(struct netif *netif)
{
struct ethernetif *ethernetif;

	ethernetif = mem_malloc(sizeof(struct ethernetif));
	if (ethernetif == NULL) {
		LWIP_DEBUGF(NETIF_DEBUG, ("ethernetif_init: out of memory?n"));
		return ERR_MEM;
	}

	netif->state = ethernetif;
	netif->name[0] = 'k';
	netif->name[1] = 'e';

	memcpy( eth_mac, default_eth_mac, 6 );
	memcpy( netif->hwaddr, default_eth_mac, 6 );

	netif->output = etharp_output;
	netif->linkoutput = low_level_output;

	netif->hwaddr_len = ETHARP_HWADDR_LEN;
	netif->mtu = 1500;
	netif->flags = NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP |
	    NETIF_FLAG_LINK_UP;

	eth_reset();

//	irq_enable(KS8695_INT_LAN_RX_STATUS);

	inquestart = 0;
	inqueend = 0;

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
