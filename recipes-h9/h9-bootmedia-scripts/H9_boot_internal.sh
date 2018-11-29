#!/bin/sh

dd if=/usr/script/bootargs-nand.bin of=/dev/mtdblock1
sync
sync
sync
echo "****************************************"
echo "* Default boot restored, please reboot *"
echo "****************************************"
sleep 5

