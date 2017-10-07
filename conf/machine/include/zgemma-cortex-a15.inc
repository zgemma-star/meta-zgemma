IMAGE_CLASSES += "zgemma-emmc_image_multi"
IMAGE_FSTYPES += "zgemma-emmc tar.bz2"
IMAGE_ROOTFS_SIZE ?= "294912"

TARGET_ARCH = "arm"
DEFAULTTUNE = "cortexa15hf-neon-vfpv4"

require conf/machine/include/tune-cortexa15.inc
require conf/machine/include/zgemma.inc