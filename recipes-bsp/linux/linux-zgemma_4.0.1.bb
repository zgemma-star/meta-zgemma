DESCRIPTION = "Linux kernel for ${MACHINE}"
SECTION = "kernel"
LICENSE = "GPLv2"

KERNEL_RELEASE = "4.0.1"
COMPATIBLE_MACHINE = "(sh1|h3|h4|h5|h6|lc|i55)"

inherit kernel machine_kernel_pr

MACHINE_KERNEL_PR_append = ".2"

SRC_URI[mips.md5sum] = "c274792d088cd7bbfe7fe5a76bd798d8"
SRC_URI[mips.sha256sum] = "6fd63aedd69b3b3b28554cabf71a9efcf05f10758db3d5b99cfb0580e3cde24c"

LIC_FILES_CHKSUM = "file://${WORKDIR}/linux-${PV}/COPYING;md5=d7810fab7487fb0aad327b76f1be7cd7"

SRC_URI += "http://www.zgemma.org/downloads/linux-${PV}.tar.gz \
	file://defconfig \
	"

SRC_URI_append_mipsel = " \
	file://add-dmx-source-timecode.patch \
	file://iosched-slice_idle-1.patch \
	file://0001-bcmgenet.patch \
	file://0002-add-brcm-chips.patch \
	file://0003-nand-ecc-strength-and-bitflip.patch \
	file://0001-3.17-fix-cpu-probe-disable-RIXIEX-check-on-BCM7584.patch \
	file://kernel-gcc6.patch \
	file://sdio-pinmux.patch \
	"

S = "${WORKDIR}/linux-${PV}"

export OS = "Linux"
KERNEL_OBJECT_SUFFIX = "ko"

# MIPSEL

FILES_kernel-image = "${KERNEL_IMAGEDEST}/${KERNEL_IMAGETYPE}*"

KERNEL_IMAGETYPE_mipsel = "vmlinux.gz"
KERNEL_OUTPUT_mipsel = "vmlinux.gz"
KERNEL_OUTPUT_DIR_mipsel = "."
KERNEL_IMAGEDEST_mipsel = "/tmp"
KERNEL_CONSOLE_mipsel = "null"
SERIAL_CONSOLE_mipsel ?= ""

FILES_kernel-image = "${KERNEL_IMAGEDEST}/${KERNEL_IMAGETYPE}*"

pkg_postinst_kernel-image_mipsel() {
	if [ "x$D" == "x" ]; then
		if [ -f /${KERNEL_IMAGEDEST}/${KERNEL_IMAGETYPE} ] ; then
			flash_eraseall /dev/mtd1
			nandwrite -p /dev/mtd1 /${KERNEL_IMAGEDEST}/${KERNEL_IMAGETYPE}.gz
		fi
	fi
	true
}
