/*
 * Copyright (c) 2024 Hiroki Mori. All rights reserved.
 */

#include "rt1310_reg.h"

void pchar(unsigned char c)
{
	// Line status register.
	volatile char* lsr = (volatile char*)(RT_UART0_BASE + 0x14);
	// Transmitter holding register.
	volatile char* thr = (volatile char*)(RT_UART0_BASE);
 
	while(((*lsr) & 0x20) == 0) ; // Wait until THR is empty.
 
	*thr = c;
}
 
print(char *ptr)
{
	while(*ptr) {
		pchar(*ptr++);
	}
}

