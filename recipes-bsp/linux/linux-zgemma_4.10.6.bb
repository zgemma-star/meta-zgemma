DESCRIPTION = "Linux kernel for ${MACHINE}"
SECTION = "kernel"
LICENSE = "GPLv2"

KERNEL_RELEASE = "4.10.6"
COMPATIBLE_MACHINE = "(sh1|h3|h4|h5|h6|h7|lc|i55)"

inherit kernel machine_kernel_pr

MACHINE_KERNEL_PR_append = ".0"

SRC_URI[mips.md5sum] = "e5d32dd03b742e6101fde917dcba837d"
SRC_URI[mips.sha256sum] = "2997b825996beabc25d2428d37d680f56e4fa971500eabd2033a6fc13cf5765e"
SRC_URI[arm.md5sum] = "c8d81a7efa0688f995c74dfd9bc52752"
SRC_URI[arm.sha256sum] = "ec9f9e86aaacd2add09591ff2f83ac7947bfe6265fcb6f24a45d9d4a75c3c037"

LIC_FILES_CHKSUM = "file://${WORKDIR}/linux-${PV}/COPYING;md5=d7810fab7487fb0aad327b76f1be7cd7"

SRC_URI += "http://www.zgemma.org/downloads/linux-${PV}-${ARCH}.tar.gz;name=${ARCH} \
	file://defconfig \
	"

SRC_URI_append_mipsel = " \
	file://0001-add-dmx-source-timecode.patch \
	file://0002-nand-ecc-strength-and-bitflip.patch \
	file://sdio-pinmux.patch \
	"

SRC_URI_append_arm = " \
	file://findkerneldevice.py \
	file://reserve_dvb_adapter_0.patch \
	file://blacklist_mmc0.patch \
	"

S = "${WORKDIR}/linux-${PV}"

export OS = "Linux"
KERNEL_OBJECT_SUFFIX = "ko"

FILES_kernel-image = "${KERNEL_IMAGEDEST}/${KERNEL_IMAGETYPE}"

# MIPSEL

KERNEL_IMAGETYPE_mipsel = "vmlinux.gz"
KERNEL_OUTPUT_mipsel = "vmlinux.gz"
KERNEL_OUTPUT_DIR_mipsel = "."
KERNEL_IMAGEDEST_mipsel = "/tmp"
KERNEL_CONSOLE_mipsel = "null"
SERIAL_CONSOLE_mipsel ?= ""

pkg_postinst_kernel-image_mipsel() {
	if [ "x$D" == "x" ]; then
		if [ -f /${KERNEL_IMAGEDEST}/${KERNEL_IMAGETYPE} ] ; then
			flash_eraseall /dev/mtd1
			nandwrite -p /dev/mtd1 /${KERNEL_IMAGEDEST}/${KERNEL_IMAGETYPE}
		fi
	fi
	true
}

# ARM

KERNEL_OUTPUT_arm = "arch/${ARCH}/boot/${KERNEL_IMAGETYPE}"
KERNEL_IMAGETYPE_arm = "zImage"
KERNEL_IMAGEDEST_arm = "tmp"

FILES_kernel-image_arm = "/${KERNEL_IMAGEDEST}/${KERNEL_IMAGETYPE} /${KERNEL_IMAGEDEST}/findkerneldevice.py"

kernel_do_install_append_arm() {
        install -d ${D}/${KERNEL_IMAGEDEST}
        install -m 0755 ${KERNEL_OUTPUT} ${D}/${KERNEL_IMAGEDEST}
	install -m 0755 ${WORKDIR}/findkerneldevice.py ${D}/${KERNEL_IMAGEDEST}
}

pkg_postinst_kernel-image_arm() {
	if [ "x$D" == "x" ]; then
		if [ -f /${KERNEL_IMAGEDEST}/${KERNEL_IMAGETYPE} ] ; then
			python /${KERNEL_IMAGEDEST}/findkerneldevice.py
			dd if=/${KERNEL_IMAGEDEST}/${KERNEL_IMAGETYPE} of=/dev/kernel
		fi
	fi
    true
}