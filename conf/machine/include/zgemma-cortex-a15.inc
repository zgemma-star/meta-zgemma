KERNEL_MODULE_AUTOLOAD += "xfs"

# We know about rtc
MACHINE_FEATURES_BACKFILL_CONSIDERED = "rtc"

PREFERRED_VERSION_linux-zgemma = "4.10.12"

#Provider
PREFERRED_PROVIDER_virtual/kernel ?= "linux-zgemma"
PREFERRED_PROVIDER_virtual/egl ?= "zgemma-v3ddriver-${MACHINE}"
PREFERRED_PROVIDER_virtual/libgles2 ?= "zgemma-v3ddriver-${MACHINE}"

require conf/machine/include/tune-cortexa15.inc
require conf/machine/include/zgemma-essential.inc

# Qt
QT_PACKAGES_ARCH = "${MACHINE_ARCH}"
PACKAGECONFIG_GL_pn-qtbase = "no-opengl linuxfb"

# Kodi
EXTRA_OECONF_append_pn-kodi = " --with-gpu=v3d"

MACHINE_EXTRA_RRECOMMENDS = " \
	gst-plugin-dvbmediasink \
	ntfs-3g \
	"

DVBMEDIASINK_CONFIG = "--with-h265 --with-vb8 --with-vb9 --with-opus --with-wma --with-wmv --with-pcm --with-dts --with-eac3"

MACHINE_FEATURES += "alsa usbhost wlan 3dtv switchoff osdposition hdmicec"

IMAGEVERSION := "${DISTRO_NAME}-${DISTRO_VERSION}-${DATE}"
IMAGEVERSION[vardepsexclude] = "DATE"
IMAGEDIR ?= "zgemma/${MACHINE}"
IMGDEPLOYDIR ?= "${DEPLOY_DIR_IMAGE}"

IMAGE_CMD_zgemmc_append = "\
	mkdir -p ${IMGDEPLOYDIR}/${IMAGEDIR}; \
	cp ${IMGDEPLOYDIR}/${IMAGE_NAME}.emmc.img ${IMGDEPLOYDIR}/${IMAGEDIR}/disk.img; \
	echo "${IMAGEVERSION}" > ${IMGDEPLOYDIR}/${IMAGEDIR}/imageversion; \
	cp ${DEPLOY_DIR_IMAGE}/zImage ${IMGDEPLOYDIR}/${IMAGEDIR}/kernel.bin; \
	cp ${IMGDEPLOYDIR}/${IMAGE_NAME}.rootfs.tar.bz2 ${IMGDEPLOYDIR}/${IMAGEDIR}/rootfs.tar.bz2; \
	cd ${IMGDEPLOYDIR}; \
	zip ${DISTRO_NAME}-${DISTRO_VERSION}-${MACHINE}_usb.zip ${IMAGEDIR}/disk.img ${IMAGEDIR}/imageversion; \
	zip ${DISTRO_NAME}-${DISTRO_VERSION}-${MACHINE}_multiboot_ofgwrite.zip ${IMAGEDIR}/imageversion ${IMAGEDIR}/kernel.bin ${IMAGEDIR}/rootfs.tar.bz2; \
	rm -Rf ${IMAGEDIR}; \
	"