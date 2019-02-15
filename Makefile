#
#
#

NEWLIBDIR=newlib-3.0.0.20180831

PREFIX = arm-none-eabi

CROSS_CC = $(PREFIX)-gcc
CROSS_AS = $(PREFIX)-as
CROSS_LD = $(PREFIX)-ld
CROSS_OBJCOPY = $(PREFIX)-objcopy

CROSS_LIBS = -L./$(NEWLIBDIR)/$(PREFIX)/newlib
CROSS_LIBS += -Lmruby/build/kendin/lib
CROSS_LIBS += -L/usr/local/lib/gcc/arm-none-eabi/4.9.2/
CROSS_LIBS += -lmruby
CROSS_LIBS += -lc -lgcc

CROSS_CFLAGS = -I./$(NEWLIBDIR)/newlib/libc/include/
CROSS_CFLAGS += -mcpu=arm922t
CROSS_CFLAGS += -Imruby/include

OBJS = main.o startup.o

all:
	mruby/build/host/bin/mrbc -Bbytecode hoge.rb
	$(CROSS_CC) $(CROSS_CFLAGS) -c main.c -o main.o
	$(CROSS_AS) startup.s -o startup.o
	$(CROSS_LD) -T main.ld -Map=main.map $(OBJS) -o main.elf $(CROSS_LIBS)
	$(CROSS_OBJCOPY) -O binary main.elf main.bin
	mkimage -A arm -C none -O linux -T kernel -d main.bin -a 0x00100000 -e 0x00100000 main.uimg

clean:
	rm -rf *.o main.map main.elf hoge.c
