#include <stdlib.h>
#include <string.h>

#include <mruby.h>
#include <mruby/string.h>
#include <mruby/irep.h>

#include "xprintf.h"

#include "platform.h"

extern char version[];

extern IRQ_STACK_START;

#define MMUTABLEBASE 0x00004000

#define CACHEABLE 0x08
#define BUFFERABLE 0x04

//-------------------------------------------------------------------
unsigned int mmu_section ( unsigned int vadd, unsigned int padd, unsigned int flags )
{
    unsigned int ra;
    unsigned int rb;
    unsigned int rc;

    ra=vadd>>20;
    rb=MMUTABLEBASE|(ra<<2);
    rc=(padd&0xFFF00000)|0xC00|flags|2;
    //hexstrings(rb); hexstring(rc);
    PUT32(rb,rc);
    return(0);
}

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
unsigned int ra;

	xfunc_out=pchar;

	IRQ_STACK_START = 0x10000;

	print(version);

	for(ra=0;;ra+=0x00100000)
	{
		if (ra < 0x700000)   /* SDRAM. Last section use MAC DMA */
			mmu_section(ra,ra,0x0000 | BUFFERABLE | CACHEABLE);
		else
			mmu_section(ra,ra,0x0000);
		if(ra==0xFFF00000) break;
	}

	start_mmu(MMUTABLEBASE,0x00000001|0x1000|0x0004);

	start_l1cache();

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
	disableInterrupt();
}

sti()
{
	enableInterrupt();
}

#define	MODULE_KS8695			9

int getarch()
{
	return MODULE_KS8695;
}
