sd109-hwmon-objs := sd109.o

obj-m += sd109-hwmon.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

install:
	sudo cp sd109-hwmon.ko /lib/modules/$(shell uname -r)/kernel/drivers/hwmon
	sudo depmod -a

load:
	sudo insmod sd109-hwmon.ko

reload:
	sudo rmmod sd109-hwmon.ko
	sudo insmod sd109-hwmon.ko
