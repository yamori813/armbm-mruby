/*
 * Copyright (c) 2019 Hiroki Mori. All rights reserved.
 */

#include "platform.h"

unsigned long gpio_getctl()
{
unsigned long *lptr;

	lptr = (unsigned long *)(KS8695_IO_BASE + KS8695_GPIO_CTRL);

	return *lptr;
}

void gpio_setctl(unsigned long val)
{
unsigned long *lptr;

	lptr = (unsigned long *)(KS8695_IO_BASE + KS8695_GPIO_CTRL);

	*lptr = val;
}

unsigned long gpio_getdir()
{
unsigned long *lptr;

	lptr = (unsigned long *)(KS8695_IO_BASE + KS8695_GPIO_MODE);

	return *lptr;
}

void gpio_setdir(unsigned long val)
{
unsigned long *lptr;

	lptr = (unsigned long *)(KS8695_IO_BASE + KS8695_GPIO_MODE);

	*lptr = val;
}

unsigned long gpio_getdat()
{
unsigned long *lptr;

	lptr = (unsigned long *)(KS8695_IO_BASE + KS8695_GPIO_DATA);

	return *lptr;
}

void gpio_setdat(unsigned long val)
{
unsigned long *lptr;

	lptr = (unsigned long *)(KS8695_IO_BASE + KS8695_GPIO_DATA);

	*lptr = val;
}
