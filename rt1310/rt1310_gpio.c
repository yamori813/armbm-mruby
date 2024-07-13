/*
 * Copyright (c) 2024 Hiroki Mori. All rights reserved.
 */

#include "rt1310_reg.h"

unsigned long gpio_getctl()
{
	return 0;
}

void gpio_setctl(unsigned long val)
{
}

unsigned long gpio_getdir()
{
unsigned long *lptra;
unsigned long *lptrb;

	lptra = (unsigned long *)(RT_GPIO_BASE + RT_GPIO_OFF_PADIR);
	lptrb = (unsigned long *)(RT_GPIO_BASE + RT_GPIO_OFF_PBDIR);

	return (*lptra & 0xff) | ((*lptrb & 0xf) << 8);
}

void gpio_setdir(unsigned long val)
{
unsigned long *lptra;
unsigned long *lptrb;

	lptra = (unsigned long *)(RT_GPIO_BASE + RT_GPIO_OFF_PADIR);
	lptrb = (unsigned long *)(RT_GPIO_BASE + RT_GPIO_OFF_PBDIR);

	*lptra = val & 0xff;
	*lptrb = (val >> 8) & 0xf;
}

unsigned long gpio_getdat()
{
unsigned long *lptra;
unsigned long *lptrb;

	lptra = (unsigned long *)(RT_GPIO_BASE + RT_GPIO_OFF_PADR);
	lptrb = (unsigned long *)(RT_GPIO_BASE + RT_GPIO_OFF_PBDR);

	return (*lptra & 0xff) | ((*lptrb & 0xf) << 8);
}

void gpio_setdat(unsigned long val)
{
unsigned long *lptra;
unsigned long *lptrb;

	lptra = (unsigned long *)(RT_GPIO_BASE + RT_GPIO_OFF_PADR);
	lptrb = (unsigned long *)(RT_GPIO_BASE + RT_GPIO_OFF_PBDR);

	*lptra = val & 0xff;
	*lptrb = (val & 0xf) >> 8;
}
