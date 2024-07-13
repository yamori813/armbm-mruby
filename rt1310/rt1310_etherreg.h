/*
 * Copyright (c) 2024 Hiroki Mori. All rights reserved.
 */

#ifndef __RT1310_ETHERREG_H
#define	__RT1310_ETHERREG_H

#define FV_TX_RING_CNT	16
#define FV_RX_RING_CNT	16

#define FV_TXFRAGS	16

struct fv_desc {
	unsigned long	fv_stat;
	unsigned long	fv_devcs;
	unsigned long	fv_addr;
	unsigned long	fv_link;
};

#if 0
struct fv_ring_data {
	bus_dmamap_t		tx_dm[FV_TX_RING_CNT];
	struct mbuf		*tx_mb[FV_TX_RING_CNT];
	bus_dmamap_t		rx_dm[FV_RX_RING_CNT];
	struct mbuf		*rx_mb[FV_RX_RING_CNT];
};

#define FV_TX_RING_ADDR(sc, i)  \
    (sc->sc_txdesc_dmamap->dm_segs[0].ds_addr+ sizeof(struct fv_desc) * (i))
#define FV_RX_RING_ADDR(sc, i)  \
    (sc->sc_txdesc_dmamap->dm_segs[0].ds_addr + sizeof(struct fv_desc) * (i))
#endif

#define FV_DMASIZE(len)		((len)  & ((1 << 11)-1))                
#define FV_PKTSIZE(len)		((len & 0xffff0000) >> 16)

/* CSR_STATUS - Status */
#define	STATUS_TI		0x00000001	/* transmit interrupt */
#define	STATUS_TPS		0x00000002	/* transmit process stopped */
#define	STATUS_TU		0x00000004	/* transmit buffer unavail */
#define	STATUS_TJT		0x00000008	/* transmit jabber timeout */
#define	STATUS_UNF		0x00000020	/* transmit underflow */
#define	STATUS_RI		0x00000040	/* receive interrupt */
#define	STATUS_RU		0x00000080	/* receive buffer unavail */
#define	STATUS_RPS		0x00000100	/* receive process stopped */
#define	STATUS_ETI		0x00000400	/* early transmit interrupt */
#define	STATUS_SE		0x00002000	/* system error */
#define	STATUS_ER		0x00004000	/* early receive (21041) */
#define	STATUS_AIS		0x00008000	/* abnormal intr summary */
#define	STATUS_NIS		0x00010000	/* normal interrupt summary */
#define	STATUS_RS		0x000e0000	/* receive process state */
#define	STATUS_RS_STOPPED	0x00000000	/* Stopped */
#define	STATUS_RS_FETCH		0x00020000	/* Running - fetch receive
						   descriptor */
#define	STATUS_RS_CHECK		0x00040000	/* Running - check for end
						   of receive */
#define	STATUS_RS_WAIT		0x00060000	/* Running - wait for packet */
#define	STATUS_RS_SUSPENDED	0x00080000	/* Suspended */
#define	STATUS_RS_CLOSE		0x000a0000	/* Running - close receive
						   descriptor */
#define	STATUS_RS_FLUSH		0x000c0000	/* Running - flush current
						   frame from FIFO */
#define	STATUS_RS_QUEUE		0x000e0000	/* Running - queue current
						   frame from FIFO into
						   buffer */
#define	STATUS_TS		0x00700000	/* transmit process state */
#define	STATUS_TS_STOPPED	0x00000000	/* Stopped */
#define	STATUS_TS_FETCH		0x00100000	/* Running - fetch transmit
						   descriptor */
#define	STATUS_TS_WAIT		0x00200000	/* Running - wait for end
						   of transmission */
#define	STATUS_TS_READING	0x00300000	/* Running - read buffer from
						   memory and queue into
						   FIFO */
#define	STATUS_TS_SUSPENDED	0x00600000	/* Suspended */
#define	STATUS_TS_CLOSE		0x00700000	/* Running - close transmit
						   descriptor */
#define	STATUS_TX_ABORT		0x00800000	/* Transmit bus abort */
#define	STATUS_RX_ABORT		0x01000000	/* Transmit bus abort */

/* CSR_OPMODE - Operation Mode */
#define	OPMODE_SR		0x00000002	/* start receive */
#define	OPMODE_OSF		0x00000004	/* operate on second frame */
#define	OPMODE_PR		0x00000040	/* promiscuous mode */
#define	OPMODE_PM		0x00000080	/* pass all multicast */
#define	OPMODE_FDX		0x00000200	/* full duplex mode */
#define	OPMODE_ST		0x00002000	/* start transmitter */
#define	OPMODE_TR		0x0000c000	/* threshold control */
#define	OPMODE_TR_32		0x00000000	/*     32 words */
#define	OPMODE_TR_64		0x00004000	/*     64 words */
#define	OPMODE_TR_128		0x00008000	/*    128 words */
#define	OPMODE_TR_256		0x0000c000	/*    256 words */
#define	OPMODE_SF		0x00200000	/* store and forward mode */
#define	OPMODE_SPEED		0x80000000	/* speed 100M:1 10M:0 */

/* these are more or less normal Tulip registers */
#define	CSR_BUSMODE	(0x08*0)	/* bus mode */
#define	CSR_TXPOLL	(0x08*1)	/* tx poll demand */
#define	CSR_RXPOLL	(0x08*2)	/* rx poll demand */
#define	CSR_RXLIST	(0x08*3)	/* rx base descriptor address */
#define	CSR_TXLIST	(0x08*4)	/* tx base descriptor address */
#define	CSR_STATUS	(0x08*5)	/* (interrupt) status */
#define	CSR_OPMODE	(0x08*6)	/* operation mode */
#define	CSR_INTEN	(0x08*7)	/* interrupt enable */
#define	CSR_MISSED	(0x08*8)	/* missed frame counter */

#define	CSR_MIIMNG	(0x08*9)	/* MII Management Register */
#define	CSR_FULLDUP	(0x08*11)	/* Full Duplex Register */

/* 21143 like register */
#define	FULLDUP_CS		0x80000000	/* Cycle Size */
#define	FULLDUP_TT_SHIFT	27	/* Transmit Timer */
#define	FULLDUP_NTP_SHIFT	24	/* Number of Transmit Packets */
#define	FULLDUP_RT_SHIFT	20	/* Receive Timer */
#define	FULLDUP_NRP_SHIFT	17	/* Number of Receive Packets */
#define	FULLDUP_CON_MODE	0x00010000	/* Continuous Mode */
#define	FULLDUP_TIM_SHIFT	0	/* Timer Value */

/* CSR_TXPOLL - Transmit Poll Demand */
#define	TXPOLL_TPD		0x00000001	/* transmit poll demand */

/* CSR_RXPOLL - Receive Poll Demand */
#define	RXPOLL_RPD		0x00000001	/* receive poll demand */

/* CSR_STATUS - Status */
#define	STATUS_TI		0x00000001	/* transmit interrupt */
#define	STATUS_TPS		0x00000002	/* transmit process stopped */
#define	STATUS_TU		0x00000004	/* transmit buffer unavail */
#define	STATUS_TJT		0x00000008	/* transmit jabber timeout */
#define	STATUS_UNF		0x00000020	/* transmit underflow */
#define	STATUS_RI		0x00000040	/* receive interrupt */
#define	STATUS_RU		0x00000080	/* receive buffer unavail */
#define	STATUS_RPS		0x00000100	/* receive process stopped */
#define	STATUS_ETI		0x00000400	/* early transmit interrupt */
#define	STATUS_SE		0x00002000	/* system error */
#define	STATUS_ER		0x00004000	/* early receive (21041) */
#define	STATUS_AIS		0x00008000	/* abnormal intr summary */
#define	STATUS_NIS		0x00010000	/* normal interrupt summary */
#define	STATUS_RS		0x000e0000	/* receive process state */
#define	STATUS_RS_STOPPED	0x00000000	/* Stopped */
#define	STATUS_RS_FETCH		0x00020000	/* Running - fetch receive
						   descriptor */
#define	STATUS_RS_CHECK		0x00040000	/* Running - check for end
						   of receive */
#define	STATUS_RS_WAIT		0x00060000	/* Running - wait for packet */
#define	STATUS_RS_SUSPENDED	0x00080000	/* Suspended */
#define	STATUS_RS_CLOSE		0x000a0000	/* Running - close receive
						   descriptor */
#define	STATUS_RS_FLUSH		0x000c0000	/* Running - flush current
						   frame from FIFO */
#define	STATUS_RS_QUEUE		0x000e0000	/* Running - queue current
						   frame from FIFO into
						   buffer */
#define	STATUS_TS		0x00700000	/* transmit process state */
#define	STATUS_TS_STOPPED	0x00000000	/* Stopped */
#define	STATUS_TS_FETCH		0x00100000	/* Running - fetch transmit
						   descriptor */
#define	STATUS_TS_WAIT		0x00200000	/* Running - wait for end
						   of transmission */
#define	STATUS_TS_READING	0x00300000	/* Running - read buffer from
						   memory and queue into
						   FIFO */
#define	STATUS_TS_SUSPENDED	0x00600000	/* Suspended */
#define	STATUS_TS_CLOSE		0x00700000	/* Running - close transmit
						   descriptor */
#define	STATUS_TX_ABORT		0x00800000	/* Transmit bus abort */
#define	STATUS_RX_ABORT		0x01000000	/* Transmit bus abort */

/* CSR_OPMODE - Operation Mode */
#define	OPMODE_SR		0x00000002	/* start receive */
#define	OPMODE_OSF		0x00000004	/* operate on second frame */
#define	OPMODE_PR		0x00000040	/* promiscuous mode */
#define	OPMODE_PM		0x00000080	/* pass all multicast */
#define	OPMODE_FDX		0x00000200	/* full duplex mode */
#define	OPMODE_ST		0x00002000	/* start transmitter */
#define	OPMODE_TR		0x0000c000	/* threshold control */
#define	OPMODE_TR_32		0x00000000	/*     32 words */
#define	OPMODE_TR_64		0x00004000	/*     64 words */
#define	OPMODE_TR_128		0x00008000	/*    128 words */
#define	OPMODE_TR_256		0x0000c000	/*    256 words */
#define	OPMODE_SF		0x00200000	/* store and forward mode */
#define	OPMODE_SPEED		0x80000000	/* speed 100M:1 10M:0 */

/* CSR_BUSMODE - Bus Mode */
#define	BUSMODE_SWR		0x00000001	/* software reset */
#define	BUSMODE_BAR		0x00000002	/* bus arbitration */
#define	BUSMODE_DSL		0x0000007c	/* descriptor skip length */
#define	BUSMODE_BLE		0x00000080	/* data buf endian */
						/* programmable burst length */
#define	BUSMODE_PBL_DEFAULT	0x00000000	/*     default value */
#define	BUSMODE_PBL_1LW		0x00000100	/*     1 longword */
#define	BUSMODE_PBL_2LW		0x00000200	/*     2 longwords */
#define	BUSMODE_PBL_4LW		0x00000400	/*     4 longwords */
#define	BUSMODE_PBL_8LW		0x00000800	/*     8 longwords */
#define	BUSMODE_PBL_16LW	0x00001000	/*    16 longwords */
#define	BUSMODE_PBL_32LW	0x00002000	/*    32 longwords */
#define	BUSMODE_TAP_SHIFT	17		/* Transmit Automatic Polling */
#define	BUSMODE_DBO		0x00100000	/* descriptor endian */
#define	BUSMODE_ALIGN_16B	0x01000000	/* force oddhw rx buf align */

/*
 * MII Definitions for the 21041 and 21140/21140A/21142
 * copy from if_devar.h
 */
#define	MII_PREAMBLE            (~0)
#define	MII_TEST                0xAAAAAAAA
#define	MII_RDCMD               0x06
#define	MII_WRCMD               0x05
#define	MII_DIN                 0x00080000
#define	MII_RD                  0x00040000
#define	MII_WR                  0x00000000
#define	MII_DOUT                0x00020000
#define	MII_CLK                 0x00010000
#define	MII_CLKON               MII_CLK
#define	MII_CLKOFF              MII_CLK

/*
 * Descriptor Status bits common to transmit and receive.
 */
#define	ADSTAT_OWN	0x80000000	/* Tulip owns descriptor */
#define	ADSTAT_ES	0x00008000	/* Error Summary */

/*
 * Descriptor Status bits for Receive Descriptor.
 */
#define	ADSTAT_Rx_FF	0x40000000	/* Filtering Fail */
#define	ADSTAT_Rx_FL	0x3fff0000	/* Frame Length including CRC */
#define	ADSTAT_Rx_DE	0x00004000	/* Descriptor Error */
#define	ADSTAT_Rx_LE	0x00001000	/* Length Error */
#define	ADSTAT_Rx_RF	0x00000800	/* Runt Frame */
#define	ADSTAT_Rx_MF	0x00000400	/* Multicast Frame */
#define	ADSTAT_Rx_FS	0x00000200	/* First Descriptor */
#define	ADSTAT_Rx_LS	0x00000100	/* Last Descriptor */
#define	ADSTAT_Rx_TL	0x00000080	/* Frame Too Long */
#define	ADSTAT_Rx_CS	0x00000040	/* Collision Seen */
#define	ADSTAT_Rx_RT	0x00000020	/* Frame Type */
#define	ADSTAT_Rx_RW	0x00000010	/* Receive Watchdog */
#define	ADSTAT_Rx_RE	0x00000008	/* Report on MII Error */
#define	ADSTAT_Rx_DB	0x00000004	/* Dribbling Bit */
#define	ADSTAT_Rx_CE	0x00000002	/* CRC Error */
#define	ADSTAT_Rx_ZER	0x00000001	/* Zero (always 0) */

#define	ADSTAT_Rx_LENGTH(x)	(((x) & ADSTAT_Rx_FL) >> 16)

/*
 * Descriptor Status bits for Transmit Descriptor.
 */
#define	ADSTAT_Tx_ES	0x00008000	/* Error Summary */
#define	ADSTAT_Tx_TO	0x00004000	/* Transmit Jabber Timeout */
#define	ADSTAT_Tx_LO	0x00000800	/* Loss of Carrier */
#define	ADSTAT_Tx_NC	0x00000400	/* No Carrier */
#define	ADSTAT_Tx_LC	0x00000200	/* Late Collision */
#define	ADSTAT_Tx_EC	0x00000100	/* Excessive Collisions */
#define	ADSTAT_Tx_HF	0x00000080	/* Heartbeat Fail */
#define	ADSTAT_Tx_CC	0x00000078	/* Collision Count */
#define	ADSTAT_Tx_ED	0x00000004	/* Excessive Deferral */
#define	ADSTAT_Tx_UF	0x00000002	/* Underflow Error */
#define	ADSTAT_Tx_DE	0x00000001	/* Deferred */

#define	ADSTAT_Tx_COLLISIONS(x)	(((x) & ADSTAT_Tx_CC) >> 3)

/*
 * Descriptor Control bits common to transmit and receive.
 */
#define	ADCTL_SIZE1	0x000007ff	/* Size of buffer 1 */
#define	ADCTL_SIZE1_SHIFT 0

#define	ADCTL_SIZE2	0x003ff800	/* Size of buffer 2 */
#define	ADCTL_SIZE2_SHIFT 11

#define	ADCTL_ER	0x02000000	/* End of Ring */
#define	ADCTL_CH	0x01000000	/* Second Address Chained */

/*
 * Descriptor Control bits for Transmit Descriptor.
 */
#define	ADCTL_Tx_IC	0x80000000	/* Interrupt on Completion */
#define	ADCTL_Tx_LS	0x40000000	/* Last Segment */
#define	ADCTL_Tx_FS	0x20000000	/* First Segment */
#define	ADCTL_Tx_SETUP	0x08000000	/* Setup frame */
#define	ADCTL_Tx_AC	0x04000000	/* Add CRC Disable */
#define	ADCTL_Tx_DPD	0x00800000	/* Disabled Padding */

/* setup frame code refer dc code */

#define	FV_SFRAME_LEN		192
#define	FV_MIN_FRAMELEN		60

#define PKT_BUF_SZ		1536

#endif /* __RT1310_ETHERREG_H */
