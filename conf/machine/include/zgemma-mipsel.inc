IMAGE_FSTYPES += "ubi"
UBI_VOLNAME = "rootfs"

TARGET_ARCH = "mipsel"
DEFAULTTUNE ?= "mips32el"

require conf/machine/include/tune-mips32.inc
require conf/machine/include/zgemma.inc
