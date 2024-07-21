#include <stdlib.h>
#include <string.h>

#include <mruby.h>
#include <mruby/string.h>
#include <mruby/irep.h>
#include <mruby/version.h>

#if KS8695
#include "ks8695/ks8695.h"
#elif RT1310
#include "rt1310/rt1310.h"
#endif

#include "xprintf.h"

void pchar(unsigned char);

extern char version[];

extern IRQ_STACK_START;

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

unsigned int mmu_small ( unsigned int vadd, unsigned int padd, unsigned int flags, unsigned int mmubase )
{
    unsigned int ra;
    unsigned int rb;
    unsigned int rc;

    ra=vadd>>20;
    rb=MMUTABLEBASE|(ra<<2);
    rc=(mmubase&0xFFFFFC00)/*|(domain<<5)*/|1;
    //hexstrings(rb); hexstring(rc);
    PUT32(rb,rc); //first level descriptor
    ra=(vadd>>12)&0xFF;
    rb=(mmubase&0xFFFFFC00)|(ra<<2);
    rc=(padd&0xFFFFF000)|(0xFF0)|flags|2;
    //hexstrings(rb); hexstring(rc);
    PUT32(rb,rc); //second level descriptor
    return(0);
}

int main(void)
{
unsigned char *sizep;
int vmsize;
unsigned char *mrbp;
int mrbsize;
unsigned char *mrbbuf;
int bootsize;
unsigned int ra;
unsigned char hash[32];
int i;

	xfunc_out=pchar;

	IRQ_STACK_START = 0x10000;

	xprintf(version, MRUBY_RELEASE_MAJOR, MRUBY_RELEASE_MINOR,
	    MRUBY_RELEASE_TEENY);

	for(ra=0;;ra+=0x00100000)
	{
		if (ra >= PYMEMSTART && ra < PYMEMEND - 0x100000)
			mmu_section(ra,ra,0x0000 | BUFFERABLE | CACHEABLE);
		else
			mmu_section(ra,ra,0x0000);
		if(ra==0xFFF00000) break;
	}
	/* last 1MByte use DMA buffer */
	for(ra=PYMEMEND & 0xfff00000;;ra+=0x00001000) {
		if (ra > PYMEMEND) break;
		mmu_small(ra,ra,0,0x00000400);
	}

	start_mmu(MMUTABLEBASE,0x00000001|0x1000|0x0004);

	start_l1cache();

	mt19937ar_init();

	irq_init();

	bootsize = BOOT_SIZE;

	sizep = FLASH_ADDR + bootsize + 0xc;
	vmsize = *sizep << 24 | *(sizep + 1) << 16 |
	    *(sizep + 2) << 8 | *(sizep + 3);
	vmsize += 64;
	mrbp = FLASH_ADDR + bootsize + vmsize;
	if (*(mrbp + 0) == 0x52 && *(mrbp + 1) == 0x49 &&
	    *(mrbp + 2) == 0x54 && *(mrbp + 3) == 0x45) {
		mrbsize = *(mrbp + 0x8) << 24 | *(mrbp + 0x9) << 16 |
		    *(mrbp + 0xa) << 8 | *(mrbp + 0xb);
		mrbbuf = malloc(mrbsize);
		memcpy(mrbbuf, mrbp, mrbsize);
                xprintf("MRB SIZE %d\n", mrbsize);
		mksha256(mrbbuf, mrbsize, hash);
		xprintf("MRB SHA256 ");
		for (i = 0; i < 32; ++i)
			xprintf("%02x", hash[i]);
		xprintf("\n");

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
