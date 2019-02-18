/*
 * Copyright (c) 2019 Hiroki Mori. All rights reserved.
 */

#include "platform.h"

int irq_init(void)
{
unsigned long *lptr;

	lptr = (unsigned long *)(KS8695_IO_BASE+KS8695_INT_STATUS);
	*lptr = *lptr;
	lptr = (unsigned long *)(KS8695_IO_BASE+KS8695_INT_ENABLE);
	*lptr = 1 << KS8695_INT_TIMERINT1;

	enable_irq();
}

int irq_enable(int irq)
{
unsigned long *lptr;

	lptr = (unsigned long *)(KS8695_IO_BASE+KS8695_INT_ENABLE);
	*lptr |= 1 << irq;
}

void irqch(void)
{
unsigned long *lptr;
unsigned long status;
unsigned long mask;

	lptr = (unsigned long *)(KS8695_IO_BASE+KS8695_INT_ENABLE);
	mask = *lptr;
	lptr = (unsigned long *)(KS8695_IO_BASE+KS8695_INT_STATUS);
	status = *lptr & mask;

	if (status & (1 << KS8695_INT_LAN_RX_STATUS)) {
		eth_rx();
	} else {
		timer_intr();
	}

	*lptr = status;
}
