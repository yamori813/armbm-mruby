/*
 * Copyright (c) 2019 Hiroki Mori. All rights reserved.
 */

#include "platform.h"

#include "time.h"

unsigned long starttime;
static volatile unsigned int jiffies = 0;

void watchdog_start(int sec)
{
unsigned long *lptr;
unsigned long reg;

	/* timer1 is 1msec */
	lptr = (unsigned long *)(KS8695_IO_BASE+KS8695_TIMER1);
	reg = *lptr;
	reg = (reg * 1000 * sec) | 0xff;
	lptr = (unsigned long *)(KS8695_IO_BASE+KS8695_TIMER0);
	*lptr = reg;

	lptr = (unsigned long *)(KS8695_IO_BASE+KS8695_TIMER_CTRL);
	reg = *lptr;
	*lptr = reg | 0x01;
}

void watchdog_reset()
{
unsigned long *lptr;
unsigned long reg;

	lptr = (unsigned long *)(KS8695_IO_BASE+KS8695_TIMER_CTRL);
	reg = *lptr;
	reg = reg & ~0x01;
	*lptr = reg;
	*lptr = reg | 0x01;
}

void watchdog_stop()
{
unsigned long *lptr;
unsigned long reg;

	lptr = (unsigned long *)(KS8695_IO_BASE+KS8695_TIMER_CTRL);
	reg = *lptr;
	reg = reg & ~0x01;
	*lptr = reg;
}

int timer_init()
{
unsigned long *lptr;

	lptr = (unsigned long *)(KS8695_IO_BASE+KS8695_TIMER1_PCOUNT);
	lptr = (unsigned long *)(KS8695_IO_BASE+KS8695_TIMER1);
	lptr = (unsigned long *)(KS8695_IO_BASE+KS8695_TIMER_CTRL);
}

int timer_intr()
{

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

