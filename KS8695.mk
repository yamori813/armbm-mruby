#

CROSS_CFLAGS += -mcpu=arm922t

OBJS += ks8695/ks_uart.o ks8695/ks_irq.o ks8695/ks_timer.o ks8695/ks_gpio.o ks8695/ks_ether.o ks8695/ks8695eth.o

LOADADDR = 0x00010000
