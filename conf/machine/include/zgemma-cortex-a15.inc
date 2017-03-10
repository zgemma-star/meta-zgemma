PREFERRED_VERSION_linux-zgemma = "4.1.35"

IMAGE_CLASSES += "zgemma-emmc_image_multi"
IMAGE_FSTYPES += "zgemma-emmc"
IMAGE_ROOTFS_SIZE ?= "294912"

TARGET_ARCH = "arm"
DEFAULTTUNE = "cortexa15hf-neon-vfpv4"

require conf/machine/include/tune-cortexa15.inc
require conf/machine/include/zgemma.inc