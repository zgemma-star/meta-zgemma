DESCRIPTION = "Linux kernel for ${MACHINE}"
SECTION = "kernel"
LICENSE = "GPLv2"

KERNEL_RELEASE = "4.10.12"
COMPATIBLE_MACHINE = "(sh1|h3|h4|h5|h6|h7|lc|i55)"

inherit kernel machine_kernel_pr

MACHINE_KERNEL_PR_append = ".3"

SRC_URI[mips.md5sum] = "3c42df14db9d12041802f4c8fec88e17"
SRC_URI[mips.sha256sum] = "738896d2682211d2079eeaa1c7b8bdd0fe75eb90cd12dff2fc5aeb3cc02562bc"
SRC_URI[arm.md5sum] = "bda1c09ed92a805cedc6770c0dd40e81"
SRC_URI[arm.sha256sum] = "67a3ac98727595a399d5c399d3b66a7fadbe8136ac517e08decba5ea6964674a"

LIC_FILES_CHKSUM = "file://${WORKDIR}/linux-${PV}/COPYING;md5=d7810fab7487fb0aad327b76f1be7cd7"

# By default, kernel.bbclass modifies package names to allow multiple kernels
# to be installed in parallel. We revert this change and rprovide the versioned
# package names instead, to allow only one kernel to be installed.
PKG_${KERNEL_PACKAGE_NAME}-base = "${KERNEL_PACKAGE_NAME}-base"
PKG_${KERNEL_PACKAGE_NAME}-image = "${KERNEL_PACKAGE_NAME}-image"
RPROVIDES_${KERNEL_PACKAGE_NAME}-base = "${KERNEL_PACKAGE_NAME}-${KERNEL_VERSION}"
RPROVIDES_${KERNEL_PACKAGE_NAME}-image = "${KERNEL_PACKAGE_NAME}-image-${KERNEL_VERSION}"

SRC_URI += "http://www.zgemma.org/downloads/linux-${PV}-${ARCH}.tar.gz;name=${ARCH} \
	file://defconfig \
	"

SRC_URI_append_mipsel = " \
	file://0001-add-dmx-source-timecode.patch \
	file://0002-nand-ecc-strength-and-bitflip.patch \
	file://sdio-pinmux.patch \
	"

SRC_URI_append_arm = " \
	file://export_pmpoweroffprepare.patch \
	file://findkerneldevice.py \
	file://reserve_dvb_adapter_0.patch \
	file://blacklist_mmc0.patch \
	file://initramfs-subdirboot.cpio.gz;unpack=0 \
	"

S = "${WORKDIR}/linux-${PV}"

export OS = "Linux"
KERNEL_OBJECT_SUFFIX = "ko"
KERNEL_IMAGEDEST = "tmp"

FILES_${KERNEL_PACKAGE_NAME}-image = "${KERNEL_IMAGEDEST}/${KERNEL_IMAGETYPE}"

# MIPSEL

KERNEL_IMAGETYPE_mipsel = "vmlinux.gz"
KERNEL_OUTPUT_mipsel = "vmlinux.gz"
KERNEL_OUTPUT_DIR_mipsel = "."
KERNEL_CONSOLE_mipsel = "null"
SERIAL_CONSOLE_mipsel ?= ""

kernel_do_install_append_mipsel() {
        install -d ${D}${KERNEL_IMAGEDEST}
        install -m 0755 ${KERNEL_OUTPUT} ${D}${KERNEL_IMAGEDEST}
}

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

KERNEL_IMAGETYPE_arm = "zImage"
KERNEL_OUTPUT_arm = "arch/${ARCH}/boot/${KERNEL_IMAGETYPE}"

FILES_${KERNEL_PACKAGE_NAME}-image_arm = "${KERNEL_IMAGEDEST}/${KERNEL_IMAGETYPE} ${KERNEL_IMAGEDEST}/findkerneldevice.py"

kernel_do_configure_prepend_arm() {
	install -d ${B}/usr
	install -m 0644 ${WORKDIR}/initramfs-subdirboot.cpio.gz ${B}/
}

kernel_do_install_append_arm() {
        install -d ${D}${KERNEL_IMAGEDEST}
        install -m 0755 ${KERNEL_OUTPUT} ${D}${KERNEL_IMAGEDEST}
        install -m 0755 ${WORKDIR}/findkerneldevice.py ${D}${KERNEL_IMAGEDEST}
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
