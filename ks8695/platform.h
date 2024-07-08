/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307	 USA
 */
#ifndef __address_h
#define __address_h			1

#define KS8695_SDRAM_START	    0x00000000
#define KS8695_SDRAM_SIZE	    0x01000000
#define KS8695_MEM_SIZE		    KS8695_SDRAM_SIZE
#define KS8695_MEM_START	    KS8695_SDRAM_START

#define KS8695_PCMCIA_IO_BASE	    0x03800000
#define KS8695_PCMCIA_IO_SIZE	    0x00040000

#define KS8695_IO_BASE		    0x03FF0000
#define KS8695_IO_SIZE		    0x00010000

#define KS8695_SYSTEN_CONFIG	    0x00
#define KS8695_SYSTEN_BUS_CLOCK	    0x04

#ifdef UBOOT_ORIG
#define KS8695_FLASH_START	    0x02800000
#else
#define KS8695_FLASH_START	    0x02000000
#endif
#define KS8695_FLASH_SIZE	    0x00400000

/*i/o control registers offset definitions*/
#define KS8695_IO_CTRL0		    0x4000
#define KS8695_IO_CTRL1		    0x4004
#define KS8695_IO_CTRL2		    0x4008
#define KS8695_IO_CTRL3		    0x400C

/*memory control registers offset definitions*/
#define KS8695_MEM_CTRL0	    0x4010
#define KS8695_MEM_CTRL1	    0x4014
#define KS8695_MEM_CTRL2	    0x4018
#define KS8695_MEM_CTRL3	    0x401C
#define KS8695_MEM_GENERAL	    0x4020
#define KS8695_SDRAM_CTRL0	    0x4030
#define KS8695_SDRAM_CTRL1	    0x4034
#define KS8695_SDRAM_GENERAL	    0x4038
#define KS8695_SDRAM_BUFFER	    0x403C
#define KS8695_SDRAM_REFRESH	    0x4040

/*WAN control registers offset definitions*/
#define KS8695_WAN_DMA_TX	    0x6000
#define KS8695_WAN_DMA_RX	    0x6004
#define KS8695_WAN_DMA_TX_START	    0x6008
#define KS8695_WAN_DMA_RX_START	    0x600C
#define KS8695_WAN_TX_LIST	    0x6010
#define KS8695_WAN_RX_LIST	    0x6014
#define KS8695_WAN_MAC_LOW	    0x6018
#define KS8695_WAN_MAC_HIGH	    0x601C
#define KS8695_WAN_MAC_ELOW	    0x6080
#define KS8695_WAN_MAC_EHIGH	    0x6084

/*LAN control registers offset definitions*/
#define KS8695_LAN_DMA_TX	    0x8000
#define KS8695_LAN_DMA_RX	    0x8004
#define KS8695_LAN_DMA_TX_START	    0x8008
#define KS8695_LAN_DMA_RX_START	    0x800C
#define KS8695_LAN_TX_LIST	    0x8010
#define KS8695_LAN_RX_LIST	    0x8014
#define KS8695_LAN_MAC_LOW	    0x8018
#define KS8695_LAN_MAC_HIGH	    0x801C
#define KS8695_LAN_MAC_ELOW	    0X8080
#define KS8695_LAN_MAC_EHIGH	    0X8084

/*HPNA control registers offset definitions*/
#define KS8695_HPNA_DMA_TX	    0xA000
#define KS8695_HPNA_DMA_RX	    0xA004
#define KS8695_HPNA_DMA_TX_START    0xA008
#define KS8695_HPNA_DMA_RX_START    0xA00C
#define KS8695_HPNA_TX_LIST	    0xA010
#define KS8695_HPNA_RX_LIST	    0xA014
#define KS8695_HPNA_MAC_LOW	    0xA018
#define KS8695_HPNA_MAC_HIGH	    0xA01C
#define KS8695_HPNA_MAC_ELOW	    0xA080
#define KS8695_HPNA_MAC_EHIGH	    0xA084

/*UART control registers offset definitions*/
#define KS8695_UART_RX_BUFFER	    0xE000
#define KS8695_UART_TX_HOLDING	    0xE004

#define KS8695_UART_FIFO_CTRL	    0xE008
#define KS8695_UART_FIFO_TRIG01	    0x00
#define KS8695_UART_FIFO_TRIG04	    0x80
#define KS8695_UART_FIFO_TXRST	    0x04
#define KS8695_UART_FIFO_RXRST	    0x02
#define KS8695_UART_FIFO_FEN	    0x01

#define KS8695_UART_LINE_CTRL	    0xE00C
#define KS8695_UART_LINEC_BRK	    0x40
#define KS8695_UART_LINEC_EPS	    0x10
#define KS8695_UART_LINEC_PEN	    0x08
#define KS8695_UART_LINEC_STP2	    0x04
#define KS8695_UART_LINEC_WLEN8	    0x03
#define KS8695_UART_LINEC_WLEN7	    0x02
#define KS8695_UART_LINEC_WLEN6	    0x01
#define KS8695_UART_LINEC_WLEN5	    0x00

#define KS8695_UART_MODEM_CTRL	    0xE010
#define KS8695_UART_MODEMC_RTS	    0x02
#define KS8695_UART_MODEMC_DTR	    0x01

#define KS8695_UART_LINE_STATUS	    0xE014
#define KS8695_UART_LINES_TXFE	    0x20
#define KS8695_UART_LINES_BE	    0x10
#define KS8695_UART_LINES_FE	    0x08
#define KS8695_UART_LINES_PE	    0x04
#define KS8695_UART_LINES_OE	    0x02
#define KS8695_UART_LINES_RXFE	    0x01
#define KS8695_UART_LINES_ANY	    (KS8695_UART_LINES_OE|KS8695_UART_LINES_BE|KS8695_UART_LINES_PE|KS8695_UART_LINES_FE)

#define KS8695_UART_MODEM_STATUS    0xE018
#define KS8695_UART_MODEM_DCD	    0x80
#define KS8695_UART_MODEM_DSR	    0x20
#define KS8695_UART_MODEM_CTS	    0x10
#define KS8695_UART_MODEM_DDCD	    0x08
#define KS8695_UART_MODEM_DDSR	    0x02
#define KS8695_UART_MODEM_DCTS	    0x01
#define UART8695_MODEM_ANY	    0xFF

#define KS8695_UART_DIVISOR	    0xE01C
#define KS8695_UART_STATUS	    0xE020

/*Interrupt controller registers offset definitions*/
#define KS8695_INT_CONTL	    0xE200
#define KS8695_INT_ENABLE	    0xE204
#define KS8695_INT_ENABLE_MODEM	    0x0800
#define KS8695_INT_ENABLE_ERR	    0x0400
#define KS8695_INT_ENABLE_RX	    0x0200
#define KS8695_INT_ENABLE_TX	    0x0100

#define KS8695_INT_STATUS	    0xE208
#define KS8695_INT_WAN_PRIORITY	    0xE20C
#define KS8695_INT_HPNA_PRIORITY    0xE210
#define KS8695_INT_LAN_PRIORITY	    0xE214
#define KS8695_INT_TIMER_PRIORITY   0xE218
#define KS8695_INT_UART_PRIORITY    0xE21C
#define KS8695_INT_EXT_PRIORITY	    0xE220
#define KS8695_INT_CHAN_PRIORITY    0xE224
#define KS8695_INT_BUSERROR_PRO	    0xE228
#define KS8695_INT_MASK_STATUS	    0xE22C
#define KS8695_FIQ_PEND_PRIORITY    0xE230
#define KS8695_IRQ_PEND_PRIORITY    0xE234

/*timer registers offset definitions*/
#define KS8695_TIMER_CTRL	    0xE400
#define KS8695_TIMER1		    0xE404
#define KS8695_TIMER0		    0xE408
#define KS8695_TIMER1_PCOUNT	    0xE40C
#define KS8695_TIMER0_PCOUNT	    0xE410

/*GPIO registers offset definitions*/
#define KS8695_GPIO_MODE	    0xE600
#define KS8695_GPIO_CTRL	    0xE604
#define KS8695_GPIO_DATA	    0xE608

/*SWITCH registers offset definitions*/
#define KS8695_SWITCH_CTRL0	    0xE800
#define KS8695_SWITCH_CTRL1	    0xE804
#define KS8695_SWITCH_PORT1	    0xE808
#define KS8695_SWITCH_PORT2	    0xE80C
#define KS8695_SWITCH_PORT3	    0xE810
#define KS8695_SWITCH_PORT4	    0xE814
#define KS8695_SWITCH_PORT5	    0xE818
#define KS8695_SWITCH_LUE_CTRL	    0xE824
#define KS8695_SWITCH_LUE_HIGH	    0xE828
#define KS8695_SWITCH_LUE_LOW	    0xE82C
#define KS8695_SWITCH_ADVANCED	    0xE830


/*host communication registers definitions*/
#define KS8695_DSCP_HIGH	    0xE834
#define KS8695_DSCP_LOW		    0xE838
#define KS8695_SWITCH_MAC_HIGH	    0xE83C
#define KS8695_SWITCH_MAC_LOW	    0xE840

/*miscellaneous registers definitions*/
#define KS8695_MANAGE_COUNTER	    0xE844
#define KS8695_MANAGE_DATA	    0xE848
#define KS8695_LAN12_POWERMAGR	    0xE84C
#define KS8695_LAN34_POWERMAGR	    0xE850

#if defined(CONFIG_KS8695P)
#define KS8695_SWITCH_AUTO0	    0xE848
#define KS8695_SWITCH_AUTO1	    0xE84C
#define KS8695_SWITCH_LPPM12	    0xE874
#define KS8695_SWITCH_LPPM34	    0xE878
#else /* CONFIG_KS8695X */
#define KS8695_SWITCH_AUTO0	    0xE81C
#define KS8695_SWITCH_AUTO1	    0xE820
#define KS8695_SWITCH_LPPM12	    0xE84C
#define KS8695_SWITCH_LPPM34	    0xE850
#endif

#define KS8695_DEVICE_ID	    0xEA00
#define KS8695_REVISION_ID	    0xEA04

#define KS8695_MISC_CONTROL	    0xEA08
#define KS8695_WAN_CONTROL	    0xEA0C
#define KS8695_WAN_POWERMAGR	    0xEA10
#define KS8695_WAN_PHY_CONTROL	    0xEA14
#define KS8695_WAN_PHY_STATUS	    0xEA18

/* bus clock definitions*/
#define KS8695_BUS_CLOCK_125MHZ	    0x0
#define KS8695_BUS_CLOCK_100MHZ	    0x1
#define KS8695_BUS_CLOCK_62MHZ	    0x2
#define KS8695_BUS_CLOCK_50MHZ	    0x3
#define KS8695_BUS_CLOCK_41MHZ	    0x4
#define KS8695_BUS_CLOCK_33MHZ	    0x5
#define KS8695_BUS_CLOCK_31MHZ	    0x6
#define KS8695_BUS_CLOCK_25MHZ	    0x7

/* -------------------------------------------------------------------------------
 *  definations for IRQ
 * -------------------------------------------------------------------------------*/

#define KS8695_INT_EXT_INT0		       2
#define KS8695_INT_EXT_INT1		       3
#define KS8695_INT_EXT_INT2		       4
#define KS8695_INT_EXT_INT3		       5
#define KS8695_INT_TIMERINT0		       6
#define KS8695_INT_TIMERINT1		       7
#define KS8695_INT_UART_TX		       8
#define KS8695_INT_UART_RX		       9
#define KS8695_INT_UART_LINE_ERR	       10
#define KS8695_INT_UART_MODEMS		       11
#define KS8695_INT_LAN_STOP_RX		       12
#define KS8695_INT_LAN_STOP_TX		       13
#define KS8695_INT_LAN_BUF_RX_STATUS	       14
#define KS8695_INT_LAN_BUF_TX_STATUS	       15
#define KS8695_INT_LAN_RX_STATUS	       16
#define KS8695_INT_LAN_TX_STATUS	       17
#define KS8695_INT_HPAN_STOP_RX		       18
#define KS8695_INT_HPNA_STOP_TX		       19
#define KS8695_INT_HPNA_BUF_RX_STATUS	       20
#define KS8695_INT_HPNA_BUF_TX_STATUS	       21
#define KS8695_INT_HPNA_RX_STATUS	       22
#define KS8695_INT_HPNA_TX_STATUS	       23
#define KS8695_INT_BUS_ERROR		       24
#define KS8695_INT_WAN_STOP_RX		       25
#define KS8695_INT_WAN_STOP_TX		       26
#define KS8695_INT_WAN_BUF_RX_STATUS	       27
#define KS8695_INT_WAN_BUF_TX_STATUS	       28
#define KS8695_INT_WAN_RX_STATUS	       29
#define KS8695_INT_WAN_TX_STATUS	       30

#define KS8695_INT_UART			       KS8695_INT_UART_TX

/* -------------------------------------------------------------------------------
 *  Interrupt bit positions
 *
 * -------------------------------------------------------------------------------
 */

#define KS8695_INTMASK_EXT_INT0		       ( 1 << KS8695_INT_EXT_INT0 )
#define KS8695_INTMASK_EXT_INT1		       ( 1 << KS8695_INT_EXT_INT1 )
#define KS8695_INTMASK_EXT_INT2		       ( 1 << KS8695_INT_EXT_INT2 )
#define KS8695_INTMASK_EXT_INT3		       ( 1 << KS8695_INT_EXT_INT3 )
#define KS8695_INTMASK_TIMERINT0	       ( 1 << KS8695_INT_TIMERINT0 )
#define KS8695_INTMASK_TIMERINT1	       ( 1 << KS8695_INT_TIMERINT1 )
#define KS8695_INTMASK_UART_TX		       ( 1 << KS8695_INT_UART_TX  )
#define KS8695_INTMASK_UART_RX		       ( 1 << KS8695_INT_UART_RX  )
#define KS8695_INTMASK_UART_LINE_ERR	       ( 1 << KS8695_INT_UART_LINE_ERR )
#define KS8695_INTMASK_UART_MODEMS	       ( 1 << KS8695_INT_UART_MODEMS )
#define KS8695_INTMASK_LAN_STOP_RX	       ( 1 << KS8695_INT_LAN_STOP_RX )
#define KS8695_INTMASK_LAN_STOP_TX	       ( 1 << KS8695_INT_LAN_STOP_TX )
#define KS8695_INTMASK_LAN_BUF_RX_STATUS       ( 1 << KS8695_INT_LAN_BUF_RX_STATUS )
#define KS8695_INTMASK_LAN_BUF_TX_STATUS       ( 1 << KS8695_INT_LAN_BUF_TX_STATUS )
#define KS8695_INTMASK_LAN_RX_STATUS	       ( 1 << KS8695_INT_LAN_RX_STATUS )
#define KS8695_INTMASK_LAN_TX_STATUS	       ( 1 << KS8695_INT_LAN_RX_STATUS )
#define KS8695_INTMASK_HPAN_STOP_RX	       ( 1 << KS8695_INT_HPAN_STOP_RX )
#define KS8695_INTMASK_HPNA_STOP_TX	       ( 1 << KS8695_INT_HPNA_STOP_TX )
#define KS8695_INTMASK_HPNA_BUF_RX_STATUS      ( 1 << KS8695_INT_HPNA_BUF_RX_STATUS )
#define KS8695_INTMAKS_HPNA_BUF_TX_STATUS      ( 1 << KS8695_INT_HPNA_BUF_TX_STATUS
#define KS8695_INTMASK_HPNA_RX_STATUS	       ( 1 << KS8695_INT_HPNA_RX_STATUS )
#define KS8695_INTMASK_HPNA_TX_STATUS	       ( 1 << KS8695_INT_HPNA_TX_STATUS )
#define KS8695_INTMASK_BUS_ERROR	       ( 1 << KS8695_INT_BUS_ERROR )
#define KS8695_INTMASK_WAN_STOP_RX	       ( 1 << KS8695_INT_WAN_STOP_RX )
#define KS8695_INTMASK_WAN_STOP_TX	       ( 1 << KS8695_INT_WAN_STOP_TX )
#define KS8695_INTMASK_WAN_BUF_RX_STATUS       ( 1 << KS8695_INT_WAN_BUF_RX_STATUS )
#define KS8695_INTMASK_WAN_BUF_TX_STATUS       ( 1 << KS8695_INT_WAN_BUF_TX_STATUS )
#define KS8695_INTMASK_WAN_RX_STATUS	       ( 1 << KS8695_INT_WAN_RX_STATUS )
#define KS8695_INTMASK_WAN_TX_STATUS	       ( 1 << KS8695_INT_WAN_TX_STATUS )

#define KS8695_SC_VALID_INT		       0xFFFFFFFF
#define MAXIRQNUM			       31

/*
 *  Timer definitions
 *
 *  Use timer 1 & 2
 *  (both run at 25MHz).
 *
 */
#define TICKS_PER_uSEC			25
#define mSEC_1				1000
#define mSEC_10				(mSEC_1 * 10)

/* From KS8695.S */
/*---------------------------------------------
; 
;  Followings are two examples of memory map
;  set up which are tested on our demo boards.
;
;  A. remappped memory map for board with SRAM
;  SRAM size maximum 512K, SDRAM maximun 32MB
;  FLASH memory maximum 8MB
; |------------------------------| 0x04000000
; |  Base IO bank (0x03ff0000)   | 
; |------------------------------| 0x03FF0000
; |------------------------------| 0x03E00000
; | External I/O bank 2          |
; |------------------------------| 0x03A00000 
; | External I/O bank 1          |
; |------------------------------| 0x03600000 
; | External I/O bank 0          |
; |------------------------------| 0x03200000 
; | FLASH                        |
; |------------------------------| 0x02800000 
; | SPACE                        |
; |                              |
; |------------------------------| 0x01480000
; | SPACE                        |
; |------------------------------| 0x01400000
; | SPACE                        |
; |                              |  
; |------------------------------| 0x01080000
; | SDRAM BANK 1                 |
; |------------------------------| 0x00880000 
; | SDRAM BANK 0                 |
; |------------------------------| 0x00080000 
; | SRAM                         |
; |------------------------------| 0x00000000 
;
; Figure 1. Memmry Map With SRAM 
;
; B. remappped memory map for new board without 
;  SRAM, SDRAM maximun 32MB, FLASH maximum 8MB
; |------------------------------| 0x04000000
; |  Base IO bank (0x03ff0000)   | 
; |------------------------------| 0x03FF0000
; |------------------------------| 0x03E00000
; | External I/O bank 2          |
; |------------------------------| 0x03A00000 
; | External I/O bank 1          |
; |------------------------------| 0x03600000 
; | External I/O bank 0          |
; |------------------------------| 0x03200000 
; | FLASH                        |
; |------------------------------| 0x02800000 
; | SPACE                        |
; |                              |
; |------------------------------| 0x01480000
; | SPACE                        |
; |------------------------------| 0x01400000
; | SPACE                        |
; |                              |  
; |------------------------------| 0x01000000
; | SDRAM BANK 1                 |
; |------------------------------| 0x00800000 
; | SDRAM BANK 0                 |
; |------------------------------| 0x00000000 
; Figure 2. Memory Map Without SRAM
*********************************************/

/* clock indices */
#define SYSTEN_BUS_CLOCK_125        0x0 
#define SYSTEN_BUS_CLOCK_100        0x1
#define SYSTEN_BUS_CLOCK_625        0x2
#define SYSTEN_BUS_CLOCK_050        0x3
#define SYSTEN_BUS_CLOCK_417        0x4
#define SYSTEN_BUS_CLOCK_333        0x5
#define SYSTEN_BUS_CLOCK_313        0x6
#define SYSTEN_BUS_CLOCK_025        0x7

/* cpu parameters */
#define MODE_USR                    0x10
#define MODE_FIQ                    0x11
#define MODE_IRQ                    0x12
#define MODE_SVC                    0x13
#define MODE_ABT                    0x17
#define MODE_UNDEF                  0x1B	
#define MODE_SYS                    0x1F  /* available on ARM Arch 4 and later */
#define I_BIT                       0x80  /* when I bit is set, IRQ is disabled */
#define F_BIT                       0x40  /* when F bit is set, FIQ is disabled */
   
/* other parameters to set up FLASH/ROM/SRAM configuration registers */
#define ROM_TIME_MULTIPLER_0        0x0
#define ROM_TIME_MULTIPLER_1        (0x1 << 28)
#define ROM_TIME_MULTIPLER_2        (0x2 << 28)
#define ROM_TIME_MULTIPLER_3        (0x3 << 28)

#define ROM_BANK_ACCTM2             0x0
#define ROM_BANK_ACCTM3             (0x1 << 4)
#define ROM_BANK_ACCTM4             (0x2 << 4)
#define ROM_BANK_ACCTM5             (0x3 << 4)
#define ROM_BANK_ACCTM6             (0x4 << 4)
#define ROM_BANK_ACCTM7             (0x5 << 4)
#define ROM_BANK_ACCTM8             (0x6 << 4)
#define ROM_BANK_ACCTM9             (0x7 << 4)
#define ROM_BANK_ACCTM3_1           0x0
#define ROM_BANK_ACCTM5_1           (0x1 << 4)
#define ROM_BANK_ACCTM7_1           (0x2 << 4)
#define ROM_BANK_ACCTM9_1           (0x3 << 4)
#define ROM_BANK_ACCTM11_1          (0x4 << 4)
#define ROM_BANK_ACCTM13_1          (0x5 << 4)
#define ROM_BANK_ACCTM15_1          (0x6 << 4)
#define ROM_BANK_ACCTM17_1          (0x7 << 4)
#define ROM_BANK_PACTM2             0x0
#define ROM_BANK_PACTM3             (0x1 << 2)
#define ROM_BANK_PACTM4             (0x2 << 2)
#define ROM_BANK_PACTM5             (0x3 << 2)
#define ROM_BANK_PACTM3_1           0x0
#define ROM_BANK_PACTM5_1           (0x1 << 2)
#define ROM_BANK_PACTM7_1           (0x2 << 2)
#define ROM_BANK_PACTM9_1           (0x3 << 2)
#define ROM_BANK_PMOD0              0x0
#define ROM_BANK_PMOD1              0x1
#define ROM_BANK_PMOD2              0x2
#define ROM_BANK_PMOD3              0x3

/* SDRAM banks */
#define BOOT_START                  0x00400000   /*linux bootloader C code start address*/
#define DIAG_START                  0x00080000   /*diagnostic program C code start address*/
#define LEVEL1TABLE                 0x00040000   /*where the MMU table is stored */

#define SDRAM_NOP_COMD              0x30000
#define SDRAM_PRECHARGE_CMD         0x10000
#if defined(CONFIG_ARCH_KS8695L) || defined(CONFIG_ARCH_KS8695V) || defined(CONFIG_KS8695M)
#define SDRAM_REFRESH_TIMER         360                               
#else
#define SDRAM_REFRESH_TIMER         390                               
#endif
#define SDRAM_MODE_COMD             0x20033    
#define SDRAM_RASCAS                0x0000000A

#ifdef USE_SRAM
 #define ROM_GENERAL_SETTING        0x0000000D   
#else
 #if defined(CONFIG_ARCH_KS8695) || defined(CONFIG_ARCH_KS8695X)
    #define ROM_GENERAL_SETTING     0x00000001 /*0x1 for 8 bit flash, 2 for 16 bit and 3 for 32 bit*/
 #elif defined( CONFIG_ARCH_KS8695M )
    #define ROM_GENERAL_SETTING     (ROM_TIME_MULTIPLER_1|0x0000000A)
 #elif defined( CONFIG_ARCH_KS8695P )
    #define ROM_GENERAL_SETTING     (ROM_TIME_MULTIPLER_1|0x00000001)
 #elif defined(CONFIG_ARCH_KS8695PM) || defined(CONFIG_ARCH_KS8695MB)
    #define ROM_GENERAL_SETTING     (ROM_TIME_MULTIPLER_1|0x0003000F)
 #elif defined( CONFIG_ARCH_KS8695V )
  #if defined( CONFIG_KS8695V1 )
    #define ROM_GENERAL_SETTING     (ROM_TIME_MULTIPLER_1|0x00030003)
  #else
    #define ROM_GENERAL_SETTING     (ROM_TIME_MULTIPLER_1|0x00030002)
  #endif
 #elif defined(CONFIG_ARCH_KS8695L)
    #define ROM_GENERAL_SETTING     (ROM_TIME_MULTIPLER_1|0x00000002)
 #endif
#endif

#if !defined(CONFIG_ARCH_KS8695L)
#define FLASH_BANK_SIZE		    0x00800000  
#else
#define FLASH_BANK_SIZE		    0x00400000  
#endif

#if defined(CONFIG_KS8695M)
 #define FLASH_BANK_SIZE_1          0x00800000
#else
 #define FLASH_BANK_SIZE_1          0x00000000
#endif

#define SRAM_BANK_SIZE		    0x00080000

/* memory configuration */
#define FLASH_BANK		0
#define REMAPPED_FLASH_BANK	PHYS_FLASH_1

#ifdef USE_SRAM
 #define SRAM_BANK		    FLASH_BANK_SIZE
 #define REMAPPED_SRAM_BANK         0x00000000   	
 #define SDRAM_BANK_0		    (SRAM_BANK + SRAM_BANK_SIZE)           
 #define REMAPPED_SDRAM_BANK_0      (REMAPPED_SRAM_BANK + SRAM_BANK_SIZE)       
#else
 #define SDRAM_BANK_0		FLASH_BANK_SIZE
 #define REMAPPED_SDRAM_BANK_0	PHYS_SDRAM_1
#endif

#ifdef PHYS_FLASH_1_SIZE
#define FLASH_BANK0_SIZE	PHYS_FLASH_1_SIZE
#else
#define FLASH_BANK0_SIZE	0x00400000
#endif
#ifdef PHYS_FLASH_2_SIZE
#define FLASH_BANK1_SIZE	PHYS_FLASH_2_SIZE
#else
#define FLASH_BANK1_SIZE	0
#endif

#define REMAPPED_FLASH_BANK_1	(REMAPPED_FLASH_BANK + FLASH_BANK0_SIZE)

#define SDRAM_BANK0_SIZE	PHYS_SDRAM_1_SIZE
#define SDRAM_BANK1_SIZE	PHYS_SDRAM_2_SIZE

#define SDRAM_BANK_1		(SDRAM_BANK_0 + SDRAM_BANK0_SIZE)
#define SDRAM_BANK_END		(SDRAM_BANK_1 + SDRAM_BANK1_SIZE)

#define REMAPPED_SDRAM_BANK_1	(REMAPPED_SDRAM_BANK_0 + SDRAM_BANK0_SIZE)
#define REMAPPED_SDRAM_BANK_END	(REMAPPED_SDRAM_BANK_1 + SDRAM_BANK1_SIZE)
		
#define SDRAM_BANK_COLAB8	0x0
#define SDRAM_BANK_COLAB9	(0x1 << 8)
#define SDRAM_BANK_COLAB10	(0x2 << 8)
#define SDRAM_BANK_COLAB11	(0x3 << 8)
#define SDRAM_UNM_BANKS2	0x0
#define SDRAM_UNM_BANKS4	(0x1 << 3)
#define SDRAM_BANKS_DBW0	0x0
#define SDRAM_BANKS_DBW8	(0x1 << 1)
#define SDRAM_BANKS_DBW16	(0x2 << 1)
#define SDRAM_BANKS_DBW32	(0x3 << 1)

/* External I/O banks defintions */
#ifdef CONFIG_ARCH_KS8695MB
  #define EXT_IO_BANK_SIZE          0x00100000
  #define EXT_IO_BANK_0             0x03C00000
#elif defined( CONFIG_ARCH_KS8695PM )
  #define EXT_IO_BANK_SIZE          0x00200000
  #define EXT_IO_BANK_0             0x03400000
#else
  #define EXT_IO_BANK_SIZE          0x00200000
  #define EXT_IO_BANK_0             0x03400000
#endif

#define EXT_IO_BANK_1		    (EXT_IO_BANK_0 + EXT_IO_BANK_SIZE)  
#define EXT_IO_BANK_2		    (EXT_IO_BANK_1 + EXT_IO_BANK_SIZE)   
#define EXT_IOBANK_CLOCK0           0x0
#define EXT_IOBANK_CLOCK1           0x1
#define EXT_IOBANK_CLOCK2           0x2
#define EXT_IOBANK_CLOCK3           0x3
#define EXT_IOBANK_CLOCK4           0x4
#define EXT_IOBANK_CLOCK5           0x5
#define EXT_IOBANK_CLOCK6           0x6
#define EXT_IOBANK_CLOCK7           0x7
	
/* --- System memory locations */
#ifdef ROM_RAM_REMAP
 #define RAM_LIMIT                  REMAPPED_SDRAM_BANK_END  
#else
 #define RAM_LIMIT                  SDRAM_BANK_END  
#endif  

#define ABT_STACK                   RAM_LIMIT 
#define UNDEF_STACK                 ABT_STACK - 1024 
#define SVC_STACK                   UNDEF_STACK - 1024    
#define IRQ_STACK                   SVC_STACK - 2048      
#define FIQ_STACK                   IRQ_STACK - 4096
#define SYS_STACK                   FIQ_STACK - 4096
#define USR_STACK                   SYS_STACK - 4096
#define RAM_LIMIT_TMP               SDRAM_BANK_END - 2048
#define FLASH_ROM_START             REMAPPED_FLASH_BANK   
#define SDRAM_START                 SDRAM_BANK_0 

#if !defined(CONFIG_ARCH_KS8695L) && !defined( CONFIG_ARCH_KS8695V )
    #if defined( CONFIG_KS8695M )
	#define ROM_BANK_ACCESSTIME	ROM_BANK_ACCTM11_1
    #elif defined( CONFIG_ARCH_KS8695P )
	#define ROM_BANK_ACCESSTIME	ROM_BANK_ACCTM9_1
    #else
	#define ROM_BANK_ACCESSTIME	ROM_BANK_ACCTM9
    #endif
	#define SDRAM_BANKS_WIDTH	SDRAM_BANKS_DBW32
	#define REM_FLASH_REG1		0
#else
    #if defined( CONFIG_ARCH_KS8695V )
	#define ROM_BANK_ACCESSTIME	ROM_BANK_ACCTM11_1
    #else
	#define ROM_BANK_ACCESSTIME	ROM_BANK_ACCTM9_1
    #endif
    #if defined( CONFIG_KS8695V1 )
	#define SDRAM_BANKS_WIDTH	SDRAM_BANKS_DBW32
    #else
	#define SDRAM_BANKS_WIDTH	SDRAM_BANKS_DBW16
    #endif
	#define REM_FLASH_REG1		0
#endif

/*
 *  calculating all the memory bank configuration register value which used to take me a lot of 
 *  my time and often ends up with errors and now it will be done automatically.
 */	

#define FLASH_REG_VAL( start, size )  \
	(((((start)+(size)-1)>>16)<<22)|(((start)>>16)<<12)|ROM_BANK_PMOD0|ROM_BANK_ACCESSTIME)

#if (PHYS_SDRAM_1_SIZE == 0x02000000)
#define SDRAM_REG_VAL( start, size )  \
	(((((start)+(size)-1)>>16)<<22)|(((start)>>16)<<12)|SDRAM_BANK_COLAB9|SDRAM_UNM_BANKS4|SDRAM_BANKS_WIDTH)
#else
#define SDRAM_REG_VAL( start, size )  \
	(((((start)+(size)-1)>>16)<<22)|(((start)>>16)<<12)|SDRAM_UNM_BANKS4|SDRAM_BANKS_WIDTH)
#endif

#define TMP_FLASH_REG0	FLASH_REG_VAL( FLASH_BANK, FLASH_BANK0_SIZE )
#define REM_FLASH_REG0	FLASH_REG_VAL( REMAPPED_FLASH_BANK, FLASH_BANK0_SIZE )

#define TMP_SDRAM_REG0	SDRAM_REG_VAL( SDRAM_BANK_0, SDRAM_BANK0_SIZE )
#define REM_SDRAM_REG0	SDRAM_REG_VAL( REMAPPED_SDRAM_BANK_0, SDRAM_BANK0_SIZE )


#ifdef USE_SRAM
 #define SRAM_REG       (((SRAM_BANK+SRAM_BANK_SIZE-1)>>16)<<22)|((SRAM_BANK>>16)<<12)|ROM_BANK_PMOD0|ROM_BANK_ACCTM5
 #define REM_SRAM_REG   (((REMAPPED_SRAM_BANK+SRAM_BANK_SIZE-1)>>16)<<22)|((REMAPPED_SRAM_BANK>>16)<<12)|ROM_BANK_PMOD0|ROM_BANK_ACCTM5
#endif
 
#if SDRAM_BANK1_SIZE == 0
 #define TMP_SDRAM_REG1    0
 #define SDRAM_REG1        0
 #define REM_SDRAM_REG1    0	
#else  
#define TMP_SDRAM_REG1	SDRAM_REG_VAL( SDRAM_BANK_1, SDRAM_BANK1_SIZE )
#define REM_SDRAM_REG1	SDRAM_REG_VAL( REMAPPED_SDRAM_BANK_1, SDRAM_BANK1_SIZE )

#endif

#if defined(CONFIG_KS8695M)
#ifdef REM_FLASH_REG1
#undef REM_FLASH_REG1
#endif
#define REM_FLASH_REG1	FLASH_REG_VAL( REMAPPED_FLASH_BANK_1, FLASH_BANK1_SIZE )
#endif

#define EXTIO_REG0         (((EXT_IO_BANK_0+EXT_IO_BANK_SIZE-1)>>16)<<22)|((EXT_IO_BANK_0>>16)<<12)|(EXT_IOBANK_CLOCK6<<9)
#define EXTIO_REG1         (((EXT_IO_BANK_1+EXT_IO_BANK_SIZE-1)>>16)<<22)|((EXT_IO_BANK_1>>16)<<12)|(EXT_IOBANK_CLOCK6<<9)
#define EXTIO_REG2         (((EXT_IO_BANK_2+EXT_IO_BANK_SIZE-1)>>16)<<22)|((EXT_IO_BANK_2>>16)<<12)|(EXT_IOBANK_CLOCK6<<9)

#define HIGH_FLASH_REG_VAL( start, size )  \
	(((((start)+(size)-1)>>16)<<22)|(((start)>>16)<<12)|ROM_BANK_PMOD0|ROM_BANK_ACCTM11_1)

#define HIGH_FLASH_VAL	HIGH_FLASH_REG_VAL( 0, PHYS_FLASH_1 + 0x01000000 )

#endif

/* Registers for PCI Bridge (AHB Acess) */

#define REG_PCI_CONFID         0x2000
#define REG_PCI_CMD            0x2004
#define REG_PCI_REV            0x2008
#define REG_PCI_LTYTIMER       0x200C
#define REG_PCI_BASEMEM        0x2010
#define REG_PCI_BASEFST        0x2014
#define REG_PCI_BASELST        0x2028
#define REG_PCI_SYSID          0x202C
#define REG_PCI_INT            0x203C
#define REG_PCI_CNFADD         0x2100
#define REG_PCI_CNGDATA        0x2104
#define REG_PCI_BMODE          0x2200
#define REG_PCI_CONTROL        0x2204
#define REG_PCI_MEMBASE        0x2208
#define REG_PCI_MEMBCTRL       0x220C
#define REG_PCI_MBMARSK        0x2210
#define REG_PCI_MBTRANS        0x2214
#define REG_PCI_IOBASE         0x2218
#define REG_PCI_IOBCTRL        0x221C
#define REG_PCI_IOBMARSK       0x2220
#define REG_PCI_IOBTRANS       0x2224

/* Definition for PCI Bridge Registers */

#define PCI_CPU_MEM_BASE       0x10000000   
//#define PCI_CPU_IO_BASE      0x02000000   
#define PCI_CPU_IO_BASE        0x08000000   
#define PCI_MEMBASE_MASK       0xF8000000   
#define PCI_IOBASE_MASK        0xFF800000 

#define PCI_MEM_PHYS           PCI_CPU_MEM_BASE   
#define PCI_IO_PHYS            PCI_CPU_IO_BASE   
#define PCI_MEM_SIZE	       0x20000000   /* 512MB */
#define PCI_IO_SIZE	       0x00800000   /* 8MB */

#define PCI_BMEM_PREFETCH      0x8
#define PCI_BMEM_PREFLMIT4     0x00000000 
#define PCI_BMEM_PREFLMIT8     0x20000000 
#define PCI_BMEM_PREFLMIT16    0x40000000  	
#define PCI_CONF_DISEXT        0x10000000

#define PCI_PCI_MODE           0x00000000
#define PCI_MINIPCI_MODE       0x20000000
#define PCI_CARDBUS_MODE       0x40000000
#define PCI_HOST_BRIDGE        0x80000000

#define PCI_LATENCY_TIMER_MASK 0x0000FF00           /* latency timer, 1 byte */
#define PCI_CACHE_LINESZ_MASK  0x000000FF           /* cache line size, 1 byte */
#define PCI_LATENCY_TIMER_DEF  0x00000020           /* default latency timer  */
#define PCI_CACHE_LINESZ                8           /* default cache line size - 8 (8-DWORD) */

#define PCI_STAT_MASK          0xFFFF0000           /* status register, 2 bytes */
#define PCI_COMM_MASK          0x0000FFFF           /* command register, 2 bytes */
#define	PCI_COMM_IO  	       0x00000001	       /* memory access enable */
#define	PCI_COMM_MEM  	       0x00000002	       /* memory access enable */
#define	PCI_COMM_MASTER	       0x00000004	       /* master enable */
#define	PCI_COMM_PERRSP	       0x00000040           /* parity error response */
#define	PCI_COMM_SYSERREN      0x00000100           /* system error enable */
#define PCI_COMM_SETTING       (PCI_COMM_MEM | PCI_COMM_IO | PCI_COMM_MASTER | PCI_COMM_PERRSP | PCI_COMM_SYSERREN)

#define PCI_ENABLE_ADDTRAN     0x80000000
#define PCI_NOEXIST            0xFFFF 

/*
 * TO access KS8695 device.
 */

#define	ks8695_read(a)	        *((volatile unsigned long *) (KS8695_IO_BASE+(a)))
#define	ks8695_write(a,b)       *((volatile unsigned long *) (KS8695_IO_BASE+(a))) = (b)

/*	END */
