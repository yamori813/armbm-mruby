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
CROSS_CFLAGS += -Imruby/include

OBJS = main.o startup.o xprintf.o mt19937ar.o net.o bear.o syscalls.o net_ether.o i2c.o

TARGET = KS8695

include $(TARGET).mk

RBSCRIPT = samples/hello.rb

main.bin: $(OBJS)
	./ver.sh
	$(CROSS_CC) $(CROSS_CFLAGS) -c ver.c
	sed s/LOADADDR/${LOADADDR}/g main.ld > main.ld.tmp
	$(CROSS_LD) -T main.ld.tmp -Map=main.map $(OBJS) ver.o -o main.elf $(CROSS_LIBS)
	$(CROSS_OBJCOPY) -O binary main.elf main.bin

image :
	./mruby/build/host/bin/mrbc -ohoge.mrb $(RBSCRIPT)
	cat main.bin.uboot hoge.mrb > main.uimg 

startup.o: startup.s
	$(CROSS_AS) -o startup.o startup.s

.c.o:
	$(CROSS_CC) $(CROSS_CFLAGS) -o $@ -c $<

clean:
	rm -rf *.o */*.o main.map main.elf main.bin* main.uimg main.uboot hoge.mrb ver.c main.ld.tmp
