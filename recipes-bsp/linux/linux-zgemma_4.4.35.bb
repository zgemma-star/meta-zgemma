DESCRIPTION = "Linux kernel for ${MACHINE}"
SECTION = "kernel"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://COPYING;md5=d7810fab7487fb0aad327b76f1be7cd7"

KERNEL_RELEASE = "4.4.35"
COMPATIBLE_MACHINE = "(h9|h10)"

inherit kernel machine_kernel_pr

SRC_URI[arm.md5sum] = "ea9854b98b10b6d1a6c82dd4bb32fd62"
SRC_URI[arm.sha256sum] = "f56276a3cd8c844741b74d4dea3853cf06bfd4520d6c9d7f9a384673cb6a0d32"

SRC_URI += "http://www.zgemma.org/downloads/linux-${PV}-${ARCH}.tar.gz;name=${ARCH} \
	file://defconfig \
"

SRC_URI_append += " \
	http://www.zgemma.org/downloads/${MACHINE}-uImage_20180119.tar.gz;name=uImage \
	http://www.zgemma.org/downloads/${MACHINE}-partitions_20180120.zip;name=part \
"

SRC_URI[uImage.md5sum] = "656dfe73a0f185b25e73a7fac5aa95cf"
SRC_URI[uImage.sha256sum] = "821ff62f2f5fc97e659ff628c72a60ea2271f2d9ea3101bbe02707605294876e"
SRC_URI[part.md5sum] = "850782d98b18406fed30a7b592a45a21"
SRC_URI[part.sha256sum] = "2e632ce9817eab5c7977f8a259bf5b854045ff189ebef3a6641968c946ba83cc"

S = "${WORKDIR}/linux-${PV}"

export OS = "Linux"
KERNEL_OBJECT_SUFFIX = "ko"
KERNEL_IMAGEDEST = "tmp"
KERNEL_IMAGETYPE = "uImage"
KERNEL_OUTPUT = "arch/${ARCH}/boot/${KERNEL_IMAGETYPE}"

FILES_kernel-image = "/${KERNEL_IMAGEDEST}/${KERNEL_IMAGETYPE}"

# kernel_do_install() {
#	install -d ${D}${KERNEL_IMAGEDEST}
#	install -m 0755 ${KERNEL_OUTPUT} ${D}${KERNEL_IMAGEDEST}
#}

kernel_do_install_append() {
	install -d ${D}${KERNEL_IMAGEDEST}
	install -d ${DEPLOY_DIR_IMAGE}
	install -m 0755 ${WORKDIR}/uImage ${D}${KERNEL_IMAGEDEST}
	install -m 0755 ${WORKDIR}/fastboot.bin ${DEPLOY_DIR_IMAGE}
	install -m 0755 ${WORKDIR}/pq_param.bin ${DEPLOY_DIR_IMAGE}
	install -m 0755 ${WORKDIR}/bootargs.bin ${DEPLOY_DIR_IMAGE}
	install -m 0755 ${WORKDIR}/bootargs_flash.bin ${DEPLOY_DIR_IMAGE}
	install -m 0755 ${WORKDIR}/baseparam.img ${DEPLOY_DIR_IMAGE}
	install -m 0755 ${WORKDIR}/logo.img ${DEPLOY_DIR_IMAGE}
}

pkg_postinst_kernel-image() {
	if [ "x$D" == "x" ]; then
		if [ -f /${KERNEL_IMAGEDEST}/${KERNEL_IMAGETYPE} ] ; then
			flash_eraseall /dev/mtd7
			nandwrite -p /dev/mtd7 /${KERNEL_IMAGEDEST}/${KERNEL_IMAGETYPE}
		fi
	fi
	true
}