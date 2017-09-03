MACHINE_KERNEL_PR = "r1"

KERNEL_MODULE_AUTOLOAD += "xfs"

# We know about rtc
MACHINE_FEATURES_BACKFILL_CONSIDERED = "rtc"

#Provider
PREFERRED_PROVIDER_virtual/egl = "zgemma-v3ddriver-${MACHINE}"
PREFERRED_PROVIDER_virtual/libgles2 = "zgemma-v3ddriver-${MACHINE}"
PREFERRED_PROVIDER_virtual/kernel = "linux-zgemma"

MACHINE_FEATURES += "alsa usbhost wlan 3dtv switchoff osdposition hdmicec"

MACHINE_EXTRA_RRECOMMENDS = " \
	gst-plugin-dvbmediasink \
	ntfs-3g \
	"

DVBMEDIASINK_CONFIG_arm = "--with-h265 --with-vb8 --with-vb9 --with-opus --with-wma --with-wmv --with-pcm --with-dts --with-eac3"
DVBMEDIASINK_CONFIG_mipsel = "--with-wma --with-wmv --with-pcm --with-dts --with-eac3 \
	${@bb.utils.contains('MACHINE_FEATURES', 'h265', '--with-h265 --with-vb6 --with-vb8 --with-spark' , '', d)} \
	"

IMAGEVERSION := "${DISTRO_NAME}-${DISTRO_VERSION}-${DATE}"
IMAGEVERSION[vardepsexclude] = "DATE"
IMAGEDIR ?= "zgemma/${MACHINE}"
IMGDEPLOYDIR ?= "${DEPLOY_DIR_IMAGE}"

IMAGE_CMD_zgemma-emmc_append_arm = "\
	mkdir -p ${IMGDEPLOYDIR}/${IMAGEDIR}; \
	cp ${IMGDEPLOYDIR}/${IMAGE_NAME}.emmc.img ${IMGDEPLOYDIR}/${IMAGEDIR}/disk.img; \
	echo "${IMAGEVERSION}" > ${IMGDEPLOYDIR}/${IMAGEDIR}/imageversion; \
	cd ${IMAGE_ROOTFS}; \
	tar -cvf ${IMGDEPLOYDIR}/${IMAGEDIR}/rootfs.tar -C ${IMAGE_ROOTFS} .; \
	bzip2 -f ${IMGDEPLOYDIR}/${IMAGEDIR}/rootfs.tar; \
	cp ${DEPLOY_DIR_IMAGE}/zImage ${IMGDEPLOYDIR}/${IMAGEDIR}/kernel.bin; \
	cd ${IMGDEPLOYDIR}; \
	zip ${DISTRO_NAME}-${DISTRO_VERSION}-${MACHINE}_usb.zip ${IMAGEDIR}/disk.img ${IMAGEDIR}/imageversion; \
	zip ${DISTRO_NAME}-${DISTRO_VERSION}-${MACHINE}_multiboot_ofgwrite.zip ${IMAGEDIR}/imageversion ${IMAGEDIR}/kernel.bin ${IMAGEDIR}/rootfs.tar.bz2; \
	rm -Rf ${IMAGEDIR}; \
	"

IMAGE_CMD_ubi_append_mipsel = " \
	mkdir -p ${IMGDEPLOYDIR}/${IMAGEDIR}; \
	cp ${IMGDEPLOYDIR}/${IMAGE_NAME}.rootfs.ubi ${IMGDEPLOYDIR}/${IMAGEDIR}/rootfs.bin; \
	cp ${DEPLOY_DIR_IMAGE}/vmlinux.gz-${MACHINE}.bin ${IMGDEPLOYDIR}/${IMAGEDIR}/kernel.bin; \
	echo "${IMAGEVERSION}" > ${IMGDEPLOYDIR}/${IMAGEDIR}/imageversion; \
	echo "rename this file to 'force' to force an update without confirmation" > ${IMGDEPLOYDIR}/${IMAGEDIR}/noforce; \
	cd ${IMGDEPLOYDIR}; \
	zip ${DISTRO_NAME}-${DISTRO_VERSION}-${MACHINE}_usb.zip ${IMAGEDIR}/*; \
	rm -Rf ${IMAGEDIR}; \
	"

require conf/machine/include/zgemma-essential.inc
