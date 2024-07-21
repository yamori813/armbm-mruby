# WZR2-G300N

CROSS_CFLAGS += -DRT1310=1 -mcpu=arm922t

OBJS += rt1310/rt1310_uart.o rt1310/rt1310_intc.o rt1310/rt1310_timer.o rt1310/rt1310_gpio.o rt1310/rt1310_ether.o

LOADADDR = 0x40010000
ASDEF = --defsym rt1310=1
VMOBJ = main_wzr2

# This target not support gzip compression

main.bin.uboot: main.bin
	mkimage -A arm -C none -O linux -T kernel -n 'mruby on YABM' -d main.bin -a $(LOADADDR) -e $(LOADADDR) $(VMOBJ).uboot
