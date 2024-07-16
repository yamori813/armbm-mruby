# MZK-W04N

CROSS_CFLAGS += -DRT1310=1 -mcpu=arm922t -DMZK=1

OBJS += rt1310/rt1310_uart.o rt1310/rt1310_intc.o rt1310/rt1310_timer.o rt1310/rt1310_gpio.o rt1310/rt1310_ether.o

LOADADDR = 0x40010000

# This target not support gzip compression

main.bin.uboot: main.bin
#	mkimage -A arm -C none -O linux -T kernel -n 'mruby on YABM' -d main.bin -a $(LOADADDR) -e $(LOADADDR) main.bin.uboot
	mkimage -A arm -C none -O linux -T kernel -n 'mruby on YABM' -d main.bin -a $(LOADADDR) -e $(LOADADDR) main.bin.tmp	
	dd if=/dev/zero of=pad.tmp bs=1 count=20
	cat pad.tmp main.bin.tmp > main.bin.uboot
