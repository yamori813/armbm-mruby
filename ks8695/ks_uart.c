/*
 * Copyright (c) 2019 Hiroki Mori. All rights reserved.
 */

#include "platform.h"

void pchar(unsigned char c)
{
	// Line status register.
	volatile char* lsr = (volatile char*)(KS8695_IO_BASE + KS8695_UART_LINE_STATUS);
	// Transmitter holding register.
	volatile char* thr = (volatile char*)(KS8695_IO_BASE + KS8695_UART_TX_HOLDING);
 
	while(((*lsr) & 0x20) == 0) ; // Wait until THR is empty.
 
	*thr = c;
}
 
print(char *ptr)
{
	while(*ptr) {
		pchar(*ptr++);
	}
}

