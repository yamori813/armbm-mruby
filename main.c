#include <mruby.h>
#include <mruby/string.h>
#include <mruby/irep.h>

#include "hoge.c"

#define KS8695_IO_BASE			0x03FF0000
#define KS8695_UART_LINE_STATUS		0xE014
#define KS8695_UART_TX_HOLDING		0xE004

void pchar(char c)
{
	// Line status register.
	volatile char* lsr = (volatile char*)(KS8695_IO_BASE + KS8695_UART_LINE_STATUS);
	// Transmitter holding register.
	volatile char* thr = (volatile char*)(KS8695_IO_BASE + KS8695_UART_TX_HOLDING);
 
	while(((*lsr) & 0x20) == 0) ; // Wait until THR is empty.
 
	*thr = c;
}
 
mrb_value myputs(mrb_state *mrb, mrb_value self){
        char *ptr;
        mrb_value val;
        mrb_get_args(mrb, "S", &val);
        for (ptr = RSTRING_PTR(val); *ptr != '\0'; ++ptr) {
                pchar(*ptr);
        }
        pchar('\r');
        pchar('\n');
        return mrb_nil_value();
}
 
int main(void)
{

        mrb_state *mrb;
        mrb = mrb_open();
        mrb_define_method(mrb, mrb->object_class,"myputs", myputs,
            MRB_ARGS_REQ(1));
        mrb_load_irep( mrb, bytecode);
        mrb_close(mrb);

	return 0;
}
