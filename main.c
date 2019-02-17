#include <stdlib.h>
#include <string.h>

#include <mruby.h>
#include <mruby/string.h>
#include <mruby/irep.h>

#include "xprintf.h"

#include "platform.h"

extern IRQ_STACK_START;

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

#define FLASH_ADDR	0x02000000
#define BOOT_SIZE	0x30000
 
int main(void)
{
unsigned char *sizep;
int vmsize;
unsigned char *mrbp;
int mrbsize;
unsigned char *mrbbuf;
int bootsize;

	xfunc_out=pchar;

	IRQ_STACK_START = 0x10000;

//	print(version);

	irq_init();

	bootsize = BOOT_SIZE;

	sizep = FLASH_ADDR + bootsize + 0xc;
	vmsize = *sizep << 24 | *(sizep + 1) << 16 |
	    *(sizep + 2) << 8 | *(sizep + 3);
	vmsize += 64;
	mrbp = FLASH_ADDR + bootsize + vmsize;
	if (*(mrbp + 0) == 0x52 && *(mrbp + 1) == 0x49 &&
	    *(mrbp + 2) == 0x54 && *(mrbp + 3) == 0x45) {
		mrbsize = *(mrbp + 0xa) << 24 | *(mrbp + 0xb) << 16 |
		    *(mrbp + 0xc) << 8 | *(mrbp + 0xd);
		mrbbuf = malloc(mrbsize);
		memcpy(mrbbuf, mrbp, mrbsize);

		mrb_state *mrb;
		mrb = mrb_open();
		mrb_load_irep( mrb, mrbbuf);
		if (mrb->exc) {
			mrb_value exc = mrb_obj_value(mrb->exc);
			mrb_value inspect = mrb_inspect(mrb, exc);
			print(mrb_str_to_cstr(mrb, inspect));
		}
		mrb_close(mrb);
	} else {
		print("can't find mrb code on flash\n");
	}

	return 0;
}


cli()
{
}

sti()
{
}

int getarch()
{
	return 0;
}
