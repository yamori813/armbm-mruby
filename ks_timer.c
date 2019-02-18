/*
 * Copyright (c) 2019 Hiroki Mori. All rights reserved.
 */

#include "platform.h"

unsigned long starttime;
static volatile unsigned int jiffies = 0;

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

delay_ms(int msec)
{
int start;

	start = jiffies;

	while (jiffies > start + msec)
		;
}

reset_counter()
{
	 jiffies = 0;
}

