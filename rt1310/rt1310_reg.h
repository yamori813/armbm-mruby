/*
 * Copyright (c) 2024 Hiroki Mori. All rights reserved.
 */

#ifndef	_RT1310_REG_H
#define	_RT1310_REG_H

#define	RT_INTC_BASE			0x19C40000
#define	RT_MAC0_BASE			0x19C80000
#define	RT_TIMER0_BASE			0x1E800000
#define	RT_UART0_BASE			0x1E840000
#define	RT_GPIO_BASE			0x1E8A0000
#define	RT_WDT_BASE			0x1E8C0000

/*
 * Interrupt controller
 */

#define	RT_INTC_SCR0			0x00	/* Intr Source Control Reg. 0 */
#define	RT_INTC_SVR0			0x80	/* Intr Vector Reg. 0  */
#define	RT_INTC_ISR			0x104	/* Intr Status Reg.  */
#define	RT_INTC_IPR			0x108	/* Intr Pending Reg.*/
#define	RT_INTC_IMR			0x10c	/* Intr Mask Reg. */
#define	RT_INTC_IECR			0x114	/* Intr Enable Command Reg. */
#define	RT_INTC_ICCR			0x118	/* Intr Clear Command Reg. */

#define	RT_INTC_TRIG_LOW_LVL		(0)
#define	RT_INTC_TRIG_HIGH_LVL		(1)
#define	RT_INTC_TRIG_NEG_EDGE		(2)
#define	RT_INTC_TRIG_POS_EDGE		(3)

#define	RT_INTC_TRIG_SHIF		6

#define	RT_INTC_TIMER0INT		3
#define	RT_INTC_MAC0INT			7

/*
 * Timer 0|1|2|3.
 */

#define	RT_TIMER_LOAD			0x00
#define	RT_TIMER_VALUE			0x04
#define	RT_TIMER_CONTROL		0x08

#define	RT_TIMER_CTRL_INTCTL		(1 << 1)
#define	RT_TIMER_CTRL_INTCLR		(1 << 2)
#define	RT_TIMER_CTRL_INTMASK		(1 << 3)
#define	RT_TIMER_CTRL_DIV4		(1 << 4)
#define	RT_TIMER_CTRL_DIV8		(2 << 4)
#define	RT_TIMER_CTRL_DIV16		(3 << 4)
#define	RT_TIMER_CTRL_DIV32		(4 << 4)
#define	RT_TIMER_CTRL_DIV64		(5 << 4)
#define	RT_TIMER_CTRL_DIV128		(6 << 4)
#define	RT_TIMER_CTRL_DIV256		(7 << 4)
#define	RT_TIMER_CTRL_PERIODCAL		(1 << 7)
#define	RT_TIMER_CTRL_ENABLE		(1 << 8)

#define	RT_TIMER_INTERVAL		(5000*150)

/*
 * GPIO
 */

#define	RT_GPIO_PORTA			(0)
#define	RT_GPIO_PORTB			(1)

#define	RT_GPIO_OFF_PADR		(0x0)
#define	RT_GPIO_OFF_PADIR		(0x4)
#define	RT_GPIO_OFF_PBDR		(0x8)
#define	RT_GPIO_OFF_PBDIR		(0xC)


/*
 * WDT
 */

#define WTDOG_OFF_LR			(0x0)
#define WTDOG_OFF_CVR			(0x4)
#define WTDOG_OFF_CON			(0x8)

#define RT_WTDOG_MAX_LR			(0xffffffff) /* 32-bit load register */
#define MAX_PRESCALE_SHIFT		(8) /* Max. prescale 1/256 */
#define RT_WTDOG_DISALLOWED_PRESCALE	(1)

/*
 * uPlatform WATCHDOG CON register definition
 */
#define WTDOG_ENABLE			(1<<3)
#define WTDOG_RESET_ENABLE		(1<<4)
#define WTDOG_PRESCALE_FACTOR_MSK	0x00000007
#define WTDOG_PRESCALE_FACTOR(x)	((x) & WTDOG_PRESCALE_FACTOR_MSK)

/*
 * Misc
 */

#define	RT_APB_FREQ			75000000
#define	RT_BASE_BAUD			6758400

/*
 * TO access RT1310 device.
 */

#define	rt1310_read(a)			*((volatile unsigned long *) (a))
#define	rt1310_write(a,b)		*((volatile unsigned long *) (a)) = (b)

#endif	/* _RT1310_REG_H */
