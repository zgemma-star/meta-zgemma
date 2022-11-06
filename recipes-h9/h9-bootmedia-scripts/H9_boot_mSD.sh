#!/bin/sh
opkg update
opkg install rsync
umount /dev/mmcblk0p1
dd if=/dev/zero of=/dev/mmcblk0p1 bs=1M count=150
mkfs.ext4 -L "H9-ROOTFS" /dev/mmcblk0p1
mkdir /tmp/mmc
mount /dev/mmcblk0p1 /tmp/mmc
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

dd if=/usr/script/bootargs-mmc.bin of=/dev/mtdblock1

sync
sync
sync
echo "****************************************"
echo "*  Transfer to mSD done, please reboot *"
echo "****************************************"
sleep 5
