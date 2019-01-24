KERNEL_MODULE_AUTOLOAD += "xfs"

# We know about rtc
MACHINE_FEATURES_BACKFILL_CONSIDERED = "rtc"

PREFERRED_VERSION_linux-zgemma = "4.4.35"

#Provider
PREFERRED_PROVIDER_virtual/kernel ?= "linux-zgemma"
PREFERRED_PROVIDER_virtual/egl ?= "zgemma-mali-3798mv200"
PREFERRED_PROVIDER_virtual/libgles1 ?= "zgemma-mali-3798mv200"
PREFERRED_PROVIDER_virtual/libgles2 ?= "zgemma-mali-3798mv200"
PREFERRED_PROVIDER_virtual/libgbm ?= "zgemma-mali-3798mv200"
PREFERRED_PROVIDER_virtual/libgl ?= "mesa"
PREFERRED_PROVIDER_virtual/mesa ?= "mesa"
PREFERRED_PROVIDER_virtual/blindscan-dvbc ?= "zgemma-dvb-modules-${MACHINE}"
PREFERRED_PROVIDER_virtual/blindscan-dvbs ?= "zgemma-dvb-modules-${MACHINE}"
PREFERRED_PROVIDER_virtual/gstreamer1.0-dvbmediasink ?= "gstreamer1.0-plugin-dvbmediasink"
PREFERRED_PROVIDER_virtual/enigma2-mediaservice ?= "enigma2-plugin-systemplugins-servicehisilicon"

# require conf/machine/include/arm/arch-armv8.inc
require conf/machine/include/tune-cortexa15.inc
require conf/machine/include/zgemma-essential.inc

# Gstreamer DVB mediasink
DVBMEDIASINK_CONFIG = "--with-h265 --with-vb8 --with-vb9 --with-wma --with-wmv --with-pcm --with-eac3 --with-amr"

# E2 OSD settings
EXTRA_OECONF_append_pn-enigma2 += " --with-alphablendingacceleration=always --with-blitaccelerationthreshold=250 --with-fillaccelerationthreshold=190000"

# Qt
PACKAGECONFIG_GL_pn-qtbase = " "
PACKAGECONFIG_append_pn-qtbase += " no-opengl linuxfb"

# Kodi
EXTRA_OECONF_append_pn-kodi += " --with-gpu=mali --enable-player=hiplayer"

MACHINE_EXTRA_RRECOMMENDS = " \
	ffmpeg \
	ntfs-3g \
	"

MACHINE_FEATURES += " alsa usbhost wlan 3dtv switchoff osdposition hdmicec"

IMAGEVERSION := "${DISTRO_NAME}-${DISTRO_VERSION}-${DATE}"
IMAGEVERSION[vardepsexclude] = "DATE"
IMAGEDIR ?= "zgemma"
IMGDEPLOYDIR ?= "${DEPLOY_DIR_IMAGE}"

IMAGE_CMD_ubi_append = " \
	mkdir -p ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}; \
	cp ${IMGDEPLOYDIR}/${IMAGE_NAME}${IMAGE_NAME_SUFFIX}.ubi ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}/rootfs.ubi; \
	cp ${DEPLOY_DIR_IMAGE}/uImage ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}/uImage; \
	cp ${DEPLOY_DIR_IMAGE}/zgemma-partitions-${MACHINE}/fastboot.bin ${IMGDEPLOYDIR}/${IMAGEDIR}/fastboot.bin; \
	cp ${DEPLOY_DIR_IMAGE}/zgemma-partitions-${MACHINE}/update_bootargs_${MACHINE}.bin ${IMGDEPLOYDIR}/${IMAGEDIR}/bootargs.bin; \
	cp ${DEPLOY_DIR_IMAGE}/zgemma-partitions-${MACHINE}/${MACHINE}/fastboot.bin ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}/fastboot.bin; \
	cp ${DEPLOY_DIR_IMAGE}/zgemma-partitions-${MACHINE}/${MACHINE}/bootargs.bin ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}/bootargs.bin; \
	cp ${DEPLOY_DIR_IMAGE}/zgemma-partitions-${MACHINE}/${MACHINE}/pq_param.bin ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}/pq_param.bin; \
	cp ${DEPLOY_DIR_IMAGE}/zgemma-partitions-${MACHINE}/${MACHINE}/baseparam.img ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}/baseparam.img; \
	cp ${DEPLOY_DIR_IMAGE}/zgemma-partitions-${MACHINE}/${MACHINE}/logo.img ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}/logo.img; \
	echo "${IMAGEVERSION}" > ${IMGDEPLOYDIR}/${IMAGEDIR}/imageversion; \
	cd ${IMGDEPLOYDIR}/${IMAGEDIR}; \
	zip -r ../${DISTRO_NAME}-${DISTRO_VERSION}-${MACHINE}_usb.zip *; \
	cd ..; \
	rm -Rf ${IMAGEDIR}; \
	"

IMAGE_CMD_zgemmafastboot8gb_append = " \
	mkdir -p ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}; \
	cp ${IMGDEPLOYDIR}/${IMAGE_NAME}${IMAGE_NAME_SUFFIX}.zgemmafastboot8gb.gz ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}/rootfs.fastboot.gz; \
	cp ${IMGDEPLOYDIR}/bootoptions.img ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}/bootoptions.img; \
	cp ${DEPLOY_DIR_IMAGE}/uImage ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}/uImage; \
	cp ${DEPLOY_DIR_IMAGE}/zgemma-partitions-${MACHINE}/fastboot.bin ${IMGDEPLOYDIR}/${IMAGEDIR}/fastboot.bin; \
	cp ${DEPLOY_DIR_IMAGE}/zgemma-partitions-${MACHINE}/bootargs.bin ${IMGDEPLOYDIR}/${IMAGEDIR}/bootargs.bin; \
	cp ${DEPLOY_DIR_IMAGE}/zgemma-partitions-${MACHINE}/update_bootargs_${MACHINE}.bin ${IMGDEPLOYDIR}/${IMAGEDIR}/update_bootargs_${MACHINE}.bin; \
	cp ${DEPLOY_DIR_IMAGE}/zgemma-partitions-${MACHINE}/${MACHINE}/fastboot.bin ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}/fastboot.bin; \
	cp ${DEPLOY_DIR_IMAGE}/zgemma-partitions-${MACHINE}/${MACHINE}/bootargs.bin ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}/bootargs.bin; \
	cp ${DEPLOY_DIR_IMAGE}/zgemma-partitions-${MACHINE}/${MACHINE}/pq_param.bin ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}/pq_param.bin; \
	cp ${DEPLOY_DIR_IMAGE}/zgemma-partitions-${MACHINE}/${MACHINE}/baseparam.img ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}/baseparam.img; \
	cp ${DEPLOY_DIR_IMAGE}/zgemma-partitions-${MACHINE}/${MACHINE}/logo.img ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}/logo.img; \
	echo "${IMAGEVERSION}" > ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}/imageversion; \
	cd ${IMGDEPLOYDIR}/${IMAGEDIR}; \
	zip -r ../${DISTRO_NAME}-${DISTRO_VERSION}-${MACHINE}_emmc.zip *; \
	cd ..; \
	rm -Rf ${IMAGEDIR}; \
	"
