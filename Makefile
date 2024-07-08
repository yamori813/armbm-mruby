#
#
#

NEWLIBDIR=newlib-3.0.0.20180831
LWIPDIR=lwip-2.1.2
BARESSLDIR=bearssl-0.6

PREFIX = arm-none-eabi

CROSS_CC = $(PREFIX)-gcc
CROSS_AS = $(PREFIX)-as
CROSS_LD = $(PREFIX)-ld
CROSS_OBJCOPY = $(PREFIX)-objcopy

CROSS_LIBS = -Lbuild/work/$(NEWLIBDIR)/$(PREFIX)/newlib
CROSS_LIBS += -Lmruby/build/kendin/lib
CROSS_LIBS += -L/usr/local/lib/gcc/arm-none-eabi/4.9.2/
CROSS_LIBS += -Lbuild/work/$(LWIPDIR)/kendin
CROSS_LIBS += -Lbuild/work/$(BARESSLDIR)/build/
CROSS_LIBS += -lmruby -llwip -lbearssl
CROSS_LIBS += -lc -lgcc

CROSS_CFLAGS = -Ibuild/work/$(NEWLIBDIR)/newlib/libc/include/
CROSS_CFLAGS += -Ibuild/work/$(LWIPDIR)/src/include -Ibuild/work/$(LWIPDIR)/kendin/include
CROSS_CFLAGS += -Ibuild/work/$(BARESSLDIR)/inc
CROSS_CFLAGS += -mcpu=arm922t
CROSS_CFLAGS += -Imruby/include

OBJS = main.o startup.o xprintf.o mt19937ar.o net.o bear.o syscalls.o net_ether.o i2c.o
OBJS += ks8695/ks_uart.o ks8695/ks_irq.o ks8695/ks_timer.o ks8695/ks_gpio.o ks8695/ks_ether.o ks8695/ks8695eth.o

RBSCRIPT = samples/hello.rb

main.bin.gz.uboot: $(OBJS)
	./ver.sh
	$(CROSS_CC) $(CROSS_CFLAGS) -c ver.c
	$(CROSS_LD) -T main.ld -Map=main.map $(OBJS) ver.o -o main.elf $(CROSS_LIBS)
	$(CROSS_OBJCOPY) -O binary main.elf main.bin
	gzip -f main.bin
	mkimage -A arm -C gzip -O linux -T kernel -n 'mruby on YABM' -d main.bin.gz -a 0x00010000 -e 0x00010000 main.bin.gz.uboot

image :
	./mruby/build/host/bin/mrbc -ohoge.mrb $(RBSCRIPT)
	cat main.bin.gz.uboot hoge.mrb > main.uimg 


startup.o: startup.s
	$(CROSS_AS) -o startup.o startup.s

.c.o:
	$(CROSS_CC) $(CROSS_CFLAGS) -o $@ -c $<

clean:
	rm -rf *.o */*.o main.map main.elf main.bin* main.uimg main.uboot hoge.mrb ver.c
