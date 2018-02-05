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
EXTRA_OECONF_append_pn-enigma2 += " --with-fbdev=/dev/fb0 --with-lcddev=/dev/null"

MACHINE_EXTRA_RRECOMMENDS = " \
	gst-plugin-dvbmediasink \
	ntfs-3g \
	"

DVBMEDIASINK_CONFIG += " --with-h265 --with-vb8 --with-vb9 --with-wma --with-wmv --with-pcm --with-dts --with-eac3"

MACHINE_FEATURES += " alsa usbhost wlan 3dtv switchoff osdposition hdmicec"

IMAGEVERSION := "${DISTRO_NAME}-${DISTRO_VERSION}-${DATE}"
IMAGEVERSION[vardepsexclude] = "DATE"
IMAGEDIR ?= "zgemma/${MACHINE}"
IMGDEPLOYDIR ?= "${DEPLOY_DIR_IMAGE}"

IMAGE_CMD_ubi_append = " \
	mkdir -p ${IMGDEPLOYDIR}/${IMAGEDIR}; \
	cp ${IMGDEPLOYDIR}/${IMAGE_NAME}.rootfs.ubi ${IMGDEPLOYDIR}/${IMAGEDIR}/rootfs.ubi; \
	cp ${DEPLOY_DIR_IMAGE}/uImage ${IMGDEPLOYDIR}/${IMAGEDIR}/uImage; \
	cp ${DEPLOY_DIR_IMAGE}/fastboot.bin ${IMGDEPLOYDIR}/${IMAGEDIR}/fastboot.bin; \
	cp ${DEPLOY_DIR_IMAGE}/pq_param.bin ${IMGDEPLOYDIR}/${IMAGEDIR}/pq_param.bin; \
	cp ${DEPLOY_DIR_IMAGE}/bootargs.bin ${IMGDEPLOYDIR}/${IMAGEDIR}/bootargs.bin; \
	cp ${DEPLOY_DIR_IMAGE}/bootargs_flash.bin ${IMGDEPLOYDIR}/${IMAGEDIR}/bootargs_flash.bin; \
	cp ${DEPLOY_DIR_IMAGE}/baseparam.img ${IMGDEPLOYDIR}/${IMAGEDIR}/baseparam.img; \
	cp ${DEPLOY_DIR_IMAGE}/logo.img ${IMGDEPLOYDIR}/${IMAGEDIR}/logo.img; \
	echo "${IMAGEVERSION}" > ${IMGDEPLOYDIR}/${IMAGEDIR}/imageversion; \
	if [ "${FORCE}" = "yes" ]; then \
		echo "rename this file to 'noforce' to force an update with confirmation" > ${IMGDEPLOYDIR}/${IMAGEDIR}/force; \
	else \
		echo "rename this file to 'force' to force an update without confirmation" > ${IMGDEPLOYDIR}/${IMAGEDIR}/noforce; \
	fi; \
	cd ${IMGDEPLOYDIR}; \
	zip -j ${DISTRO_NAME}-${DISTRO_VERSION}-${MACHINE}_usb.zip ${IMAGEDIR}/*; \
	rm -Rf ${IMAGEDIR}; \
	"