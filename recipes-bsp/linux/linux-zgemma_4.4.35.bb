DESCRIPTION = "Linux kernel for ${MACHINE}"
SECTION = "kernel"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://COPYING;md5=d7810fab7487fb0aad327b76f1be7cd7"

KERNEL_RELEASE = "4.4.35"
COMPATIBLE_MACHINE = "(h9|h10)"

inherit kernel machine_kernel_pr

SRC_URI[arm.md5sum] = "01234564789abcdef01234564789abcdef"
SRC_URI[arm.sha256sum] = "01234564789abcdef01234564789abcdef01234564789abcdef1234564789abcdef"

SRC_URI += "http://www.zgemma.org/downloads/linux-${PV}-${ARCH}.tar.gz;name=${ARCH} \
	file://defconfig \
	"

SRC_URI_append = " \
	file://fastboot.bin \
	file://pq_param.bin \
	file://bootargs.bin \
	file://bootargs-usb.bin \
	file://baseparam.img \
	file://logo.img \
	"

S = "${WORKDIR}/linux-${PV}"

export OS = "Linux"
KERNEL_OBJECT_SUFFIX = "ko"
KERNEL_IMAGEDEST = "tmp"
KERNEL_IMAGETYPE = "uImage"
KERNEL_OUTPUT = "arch/${ARCH}/boot/${KERNEL_IMAGETYPE}"

FILES_kernel-image = "/${KERNEL_IMAGEDEST}/${KERNEL_IMAGETYPE}"

kernel_do_install_append() {
        install -d ${D}${KERNEL_IMAGEDEST}
        install -d ${DEPLOY_DIR_IMAGE}
        install -m 0755 ${KERNEL_OUTPUT} ${D}${KERNEL_IMAGEDEST}
        install -m 0755 ${WORKDIR}/fastboot.bin ${DEPLOY_DIR_IMAGE}
        install -m 0755 ${WORKDIR}/pq_param.bin ${DEPLOY_DIR_IMAGE}
        install -m 0755 ${WORKDIR}/bootargs.bin ${DEPLOY_DIR_IMAGE}
        install -m 0755 ${WORKDIR}/bootargs-usb.bin ${DEPLOY_DIR_IMAGE}
        install -m 0755 ${WORKDIR}/baseparam.img ${DEPLOY_DIR_IMAGE}
        install -m 0755 ${WORKDIR}/logo.img ${DEPLOY_DIR_IMAGE}
}

pkg_postinst_kernel-image() {
	if [ "x$D" == "x" ]; then
		if [ -f /${KERNEL_IMAGEDEST}/${KERNEL_IMAGETYPE} ] ; then
			flash_eraseall /dev/mtd10
			nandwrite -p /dev/mtd10 /${KERNEL_IMAGEDEST}/${KERNEL_IMAGETYPE}
		fi
	fi
	true
}