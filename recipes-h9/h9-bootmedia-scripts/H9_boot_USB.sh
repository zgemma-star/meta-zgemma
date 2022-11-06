#!/bin/sh
opkg update
opkg install rsync
umount /dev/sda1
dd if=/dev/zero of=/dev/sda1 bs=1M count=150
mkfs.ext4 -L "H9-ROOTFS" /dev/sda1
mkdir /tmp/mmc
mount /dev/sda1 /tmp/mmc
mkdir /tmp/root
mount --bind / /tmp/root
rsync -aAXv /tmp/root/ /tmp/mmc/
umount /tmp/root
umount /tmp/mmc
rmdir /tmp/root
rmdir /tmp/mmc

sync
sync
sync

dd if=/usr/script/bootargs-usb.bin of=/dev/mtdblock1

sync
sync
sync
echo "****************************************"
echo "*  Transfer to USB done, please reboot *"
echo "****************************************"
sleep 5
