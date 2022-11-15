obj-m   := timer.o

KDIR    := /lib/modules/$(shell uname -r)/build
PWD     := $(shell pwd)

default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean

run: timer.ko
	sudo dmesg -C
	sudo insmod ./timer.ko count=4 delay=1
	sleep 6
	sudo rmmod timer
	sudo dmesg
