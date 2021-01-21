sudo rm /boot/overlays/sd109-hwmon.dtbo

sudo sed -i -e "/sd109/d" /boot/config.txt

sudo rm /lib/modules/$(uname -r)/kernel/drivers/hwmon/sd109-hwmon.ko
