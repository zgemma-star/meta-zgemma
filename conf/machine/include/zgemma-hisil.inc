KERNEL_MODULE_AUTOLOAD += "xfs"

# We know about rtc
MACHINE_FEATURES_BACKFILL_CONSIDERED = "rtc"

PREFERRED_VERSION_linux-zgemma = "4.4.35"

#Provider
PREFERRED_PROVIDER_virtual/kernel ?= "linux-zgemma"
PREFERRED_PROVIDER_virtual/egl ?= "zgemma-mali-${MACHINE}"
PREFERRED_PROVIDER_virtual/libgles1 ?= "zgemma-mali-${MACHINE}"
PREFERRED_PROVIDER_virtual/libgles2 ?= "zgemma-mali-${MACHINE}"
PREFERRED_PROVIDER_virtual/libopencl ?= "zgemma-mali-${MACHINE}"
PREFERRED_PROVIDER_virtual/blindscan-dvbc ?= "zgemma-dvb-modules-${MACHINE}"
PREFERRED_PROVIDER_virtual/blindscan-dvbs ?= "zgemma-dvb-modules-${MACHINE}"

require conf/machine/include/tune-cortexa15.inc
require conf/machine/include/zgemma-essential.inc

PACKAGECONFIG_GL_pn-qtbase += " gles2 eglfs linuxfb"
EXTRA_OECONF_append_pn-kodi += " --with-gpu=mali"

MACHINE_EXTRA_RRECOMMENDS = " \
	gst-plugin-dvbmediasink \
	ntfs-3g \
	"

DVBMEDIASINK_CONFIG += " --with-h265 --with-vb8 --with-vb9 --with-wma --with-wmv --with-pcm --with-dts --with-eac3"

MACHINE_FEATURES += " alsa usbhost wlan 3dtv switchoff osdposition hdmicec"

IMAGEVERSION := "${DISTRO_NAME}-${DISTRO_VERSION}-${DATE}"
IMAGEVERSION[vardepsexclude] = "DATE"
IMAGEDIR ?= "zgemma"
IMGDEPLOYDIR ?= "${DEPLOY_DIR_IMAGE}"

IMAGE_CMD_ubi_append = " \
	mkdir -p ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}; \
	cp ${IMGDEPLOYDIR}/${IMAGE_NAME}${IMAGE_NAME_SUFFIX}.ubi ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}/rootfs.ubi; \
	cp ${DEPLOY_DIR_IMAGE}/uImage ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}/uImage; \
	cp ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions/fastboot.bin ${IMGDEPLOYDIR}/${IMAGEDIR}; \
	cp ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions/bootargs.bin ${IMGDEPLOYDIR}/${IMAGEDIR}; \
	cp ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions/${MACHINE}/fastboot.bin ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}; \
	cp ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions/${MACHINE}/bootargs.bin ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}; \
	cp ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions/${MACHINE}/pq_param.bin ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}; \
	cp ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions/${MACHINE}/baseparam.img ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}; \
	cp ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions/${MACHINE}/logo.img ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}; \
	echo "${IMAGEVERSION}" > ${IMGDEPLOYDIR}/${IMAGEDIR}/imageversion; \
	cd ${IMGDEPLOYDIR}/${IMAGEDIR}; \
	zip -r ../${DISTRO_NAME}-${DISTRO_VERSION}-${MACHINE}_usb.zip *; \
	cd ..; \
	rm -Rf ${IMAGEDIR}; \
	"

IMAGE_CMD_fastboot_append = " \
	mkdir -p ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}; \
	cp ${IMGDEPLOYDIR}/${IMAGE_NAME}${IMAGE_NAME_SUFFIX}.fastboot.gz ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}/rootfs.fastboot.gz; \
	cp ${DEPLOY_DIR_IMAGE}/uImage ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}/uImage; \
	cp ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions/fastboot.bin ${IMGDEPLOYDIR}/${IMAGEDIR}; \
	cp ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions/bootargs.bin ${IMGDEPLOYDIR}/${IMAGEDIR}; \
	cp ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions/${MACHINE}/fastboot.bin ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}; \
	cp ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions/${MACHINE}/bootargs.bin ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}; \
	cp ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions/${MACHINE}/pq_param.bin ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}; \
	cp ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions/${MACHINE}/baseparam.img ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}; \
	cp ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions/${MACHINE}/logo.img ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}; \
	echo "${IMAGEVERSION}" > ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}/imageversion; \
	cd ${IMGDEPLOYDIR}/${IMAGEDIR}; \
	zip -r ../${DISTRO_NAME}-${DISTRO_VERSION}-${MACHINE}_emmc.zip *; \
	cd ..; \
	rm -Rf ${IMAGEDIR}; \
	"