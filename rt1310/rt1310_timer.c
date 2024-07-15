/*
 * Copyright (c) 2024 Hiroki Mori. All rights reserved.
 */

#include "rt1310_reg.h"

#include "time.h"

unsigned long wdtcount;
unsigned long starttime;
static volatile unsigned int jiffies = 0;

void watchdog_start(int sec)
{
unsigned long *lptr;

	wdtcount =(RT_APB_FREQ / 256) * sec;
	lptr = (unsigned long *)(RT_WDT_BASE + WTDOG_OFF_LR);
	*lptr = wdtcount;
	lptr = (unsigned long *)(RT_WDT_BASE + WTDOG_OFF_CON);
	*lptr = WTDOG_ENABLE | WTDOG_RESET_ENABLE | 7;
}

void watchdog_reset()
{
unsigned long *lptr;

	lptr = (unsigned long *)(RT_WDT_BASE + WTDOG_OFF_LR);
	*lptr = wdtcount;
}

void watchdog_stop()
{
unsigned long *lptr;

	lptr = (unsigned long *)(RT_WDT_BASE + WTDOG_OFF_CON);
	*lptr = 0;
}

int timer_init()
{
unsigned long *lptr;

	lptr = (unsigned long *)(RT_TIMER0_BASE + RT_TIMER_CONTROL);
	*lptr = 0;
	lptr = (unsigned long *)(RT_TIMER0_BASE + RT_TIMER_LOAD);
	*lptr = RT_APB_FREQ / 1000;
	lptr = (unsigned long *)(RT_TIMER0_BASE + RT_TIMER_VALUE);
	*lptr = RT_APB_FREQ / 1000;
	lptr = (unsigned long *)(RT_TIMER0_BASE + RT_TIMER_CONTROL);
	*lptr = RT_TIMER_CTRL_PERIODCAL | RT_TIMER_CTRL_ENABLE |
	    RT_TIMER_CTRL_INTCTL;
}

int timer_intr()
{
unsigned long *lptr;

	lptr = (unsigned long *)(RT_TIMER0_BASE + RT_TIMER_CONTROL);
	*lptr = 0;
	lptr = (unsigned long *)(RT_TIMER0_BASE + RT_TIMER_VALUE);
	*lptr = RT_APB_FREQ / 1000;
	lptr = (unsigned long *)(RT_TIMER0_BASE + RT_TIMER_CONTROL);
	*lptr = RT_TIMER_CTRL_PERIODCAL | RT_TIMER_CTRL_ENABLE |
	    RT_TIMER_CTRL_INTCTL;

	++jiffies;
	if (jiffies % 10)
		net_poll();
}

udelay(int usec)
{
int start;

	start = jiffies;

	while (jiffies != start)
		;
}

sys_now()
{

	return jiffies;
}

time_t
time(time_t *t)
{

	return sys_now()/1000 + starttime;
}

delay_ms(int msec)
{
int start;

	start = jiffies;

	while (jiffies < start + msec)
		;
}

reset_counter()
{

	 jiffies = 0;
}

