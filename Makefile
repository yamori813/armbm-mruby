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

CROSS_LIBS = -L./$(NEWLIBDIR)/$(PREFIX)/newlib
CROSS_LIBS += -Lmruby/build/kendin/lib
CROSS_LIBS += -L/usr/local/lib/gcc/arm-none-eabi/4.9.2/
CROSS_LIBS += -L$(LWIPDIR)/kendin
CROSS_LIBS += -L./$(BARESSLDIR)/build/
CROSS_LIBS += -lmruby -llwip -lbearssl
CROSS_LIBS += -lc -lgcc

CROSS_CFLAGS = -I./$(NEWLIBDIR)/newlib/libc/include/
CROSS_CFLAGS += -I./$(LWIPDIR)/src/include -I./$(LWIPDIR)/kendin/include
CROSS_CFLAGS += -I$(BARESSLDIR)/inc
CROSS_CFLAGS += -mcpu=arm922t
CROSS_CFLAGS += -Imruby/include

OBJS = main.o ks_irq.o ks_timer.o ks_gpio.o startup.o xprintf.o ks_ether.o ks8695eth.o mt19937ar.o net.o bear.o i2c.o

RBSCRIPT = samples/hello.rb

main.bin.gz.uboot: $(OBJS)
	./ver.sh
	$(CROSS_CC) $(CROSS_CFLAGS) -c ver.c
	$(CROSS_LD) -T main.ld -Map=main.map $(OBJS) ver.o -o main.elf $(CROSS_LIBS)
	$(CROSS_OBJCOPY) -O binary main.elf main.bin
	gzip -f main.bin
	mkimage -A arm -C gzip -O linux -T kernel -n 'mruby on Yet Another Bare Metal' -d main.bin.gz -a 0x00010000 -e 0x00010000 main.bin.gz.uboot

image :
	./mruby/build/host/bin/mrbc -ohoge.mrb $(RBSCRIPT)
	cat main.bin.gz.uboot hoge.mrb > main.uimg 


startup.o: startup.s
	$(CROSS_AS) -o startup.o startup.s

.c.o:
	$(CROSS_CC) $(CROSS_CFLAGS) -c $<

clean:
	rm -rf *.o main.map main.elf hoge.c main.bin* main.uimg main.uboot hoge.mrb
