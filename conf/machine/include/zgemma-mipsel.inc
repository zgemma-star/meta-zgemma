KERNEL_MODULE_AUTOLOAD += "xfs"

# We know about rtc
MACHINE_FEATURES_BACKFILL_CONSIDERED = "rtc"

PREFERRED_VERSION_linux-zgemma = "4.10.12"

#Provider
PREFERRED_PROVIDER_virtual/kernel ?= "linux-zgemma"
PREFERRED_PROVIDER_virtual/egl ?= "zgemma-v3ddriver-${MACHINE}"
PREFERRED_PROVIDER_virtual/libgles1 ?= "zgemma-v3ddriver-${MACHINE}"
PREFERRED_PROVIDER_virtual/libgles2 ?= "zgemma-v3ddriver-${MACHINE}"
PREFERRED_PROVIDER_virtual/libgbm ?= "zgemma-v3ddriver-${MACHINE}"
PREFERRED_PROVIDER_virtual/libgl ?= "mesa"
PREFERRED_PROVIDER_virtual/mesa ?= "mesa"

IMAGE_FSTYPES += "ubi"
UBI_VOLNAME = "rootfs"

TARGET_ARCH = "mipsel"
DEFAULTTUNE ?= "mips32el"

require conf/machine/include/tune-mips32.inc
require conf/machine/include/zgemma-essential.inc

PACKAGECONFIG_GL_pn-qtbase = " gles2 linuxfb"
EXTRA_OECONF_append_pn-kodi = " --with-gpu=v3d"

MACHINE_EXTRA_RRECOMMENDS = " \
	gst-plugin-dvbmediasink \
	ntfs-3g \
	"

DVBMEDIASINK_CONFIG = "--with-wma --with-wmv --with-pcm --with-dts --with-eac3 \
	${@bb.utils.contains('MACHINE_FEATURES', 'h265', '--with-h265 --with-vb6 --with-vb8 --with-spark' , '', d)} \
	"

MACHINE_FEATURES += "alsa usbhost wlan 3dtv switchoff osdposition hdmicec HDMI"

IMAGEVERSION := "${DISTRO_NAME}-${DISTRO_VERSION}-${DATE}"
IMAGEVERSION[vardepsexclude] = "DATE"
IMAGEDIR ?= "zgemma/${MACHINE}"
IMGDEPLOYDIR ?= "${DEPLOY_DIR_IMAGE}"

IMAGE_CMD_ubifs_prepend = " \
	rm -Rf ${IMAGE_ROOTFS}/boot/*; \
	rm -Rf ${IMAGE_ROOTFS}/tmp/*; \
	"

IMAGE_CMD_ubi_append = " \
	mkdir -p ${IMGDEPLOYDIR}/${IMAGEDIR}; \
	cp ${IMGDEPLOYDIR}/${IMAGE_NAME}.rootfs.ubi ${IMGDEPLOYDIR}/${IMAGEDIR}/rootfs.bin; \
	cp ${DEPLOY_DIR_IMAGE}/vmlinux.gz-${MACHINE}.bin ${IMGDEPLOYDIR}/${IMAGEDIR}/kernel.bin; \
	echo "${IMAGEVERSION}" > ${IMGDEPLOYDIR}/${IMAGEDIR}/imageversion; \
	if [ "${FORCE}" = "yes" ]; then \
		echo "rename this file to 'noforce' to force an update with confirmation" > ${IMGDEPLOYDIR}/${IMAGEDIR}/force; \
	else \
		echo "rename this file to 'force' to force an update without confirmation" > ${IMGDEPLOYDIR}/${IMAGEDIR}/noforce; \
	fi; \
	cd ${IMGDEPLOYDIR}; \
	zip ${DISTRO_NAME}-${DISTRO_VERSION}-${MACHINE}_usb.zip ${IMAGEDIR}/*; \
	rm -Rf ${IMAGEDIR}; \
	"

MTD_KERNEL = "mtd1"
MTD_ROOTFS = "mtd2"
KERNEL_FILE = "kernel.bin"
ROOTFS_FILE = "rootfs.bin"
