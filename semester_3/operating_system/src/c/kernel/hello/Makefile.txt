obj-m   := hello.o

KDIR    := /lib/modules/$(shell uname -r)/build
PWD     := $(shell pwd)

default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean

run: hello.ko
	sudo dmesg -C
	sudo insmod ./hello.ko msg='"Bonjour Jacobs University Bremen"'
	sudo rmmod hello
	sudo dmesg
