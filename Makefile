CC = gcc
obj-m += kudo_mod.o

KDIR = /lib/modules/$(shell uname -r)/build

.PHONY: all
all: kudo_mod.ko kudo

.PHONY: install
install: install_module

.PHONY: install_module
install_module: kudo_mod.ko uninstall_module
	sudo insmod kudo_mod.ko

.PHONY: uninstall_module
uninstall_module:
	-sudo rmmod -v kudo_mod

kudo_mod.ko: kudo_mod.c
	make -C $(KDIR) M=$(shell pwd) modules

kudo: kudo.c
	$(CC) kudo.c -o kudo

.PHONY: clean
clean:
	make -C $(KDIR) M=$(shell pwd) clean
	-rm -v kudo
