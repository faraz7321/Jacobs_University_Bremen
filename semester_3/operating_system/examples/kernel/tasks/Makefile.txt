obj-m   := tasks.o

KDIR    := /lib/modules/$(shell uname -r)/build
PWD     := $(shell pwd)

default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean

run: tasks.ko
	sudo dmesg -C
	sudo insmod ./tasks.ko
	sleep 1
	sudo rmmod tasks
	sudo dmesg
