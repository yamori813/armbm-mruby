#

CROSS_CFLAGS += -DRT1310=1 -mcpu=arm922t

OBJS += rt1310/rt1310_uart.o rt1310/rt1310_intc.o rt1310/rt1310_timer.o
# still dummy
OBJS += ks8695/ks_gpio.o ks8695/ks_ether.o ks8695/ks8695eth.o

LOADADDR = 0x40010000

# This target not support gzip compression

main.bin.uboot: main.bin
	mkimage -A arm -C none -O linux -T kernel -n 'mruby on YABM' -d main.bin -a $(LOADADDR) -e $(LOADADDR) main.bin.uboot
