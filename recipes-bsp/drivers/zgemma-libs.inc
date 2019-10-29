DESCRIPTION = "${MACHINE} libraries"
SECTION = "base"
PRIORITY = "required"
LICENSE = "CLOSED"
PACKAGE_ARCH = "${MACHINE_ARCH}"
PR = "${SRCDATE}"
VER ?= "${@bb.utils.contains('TARGET_ARCH', 'aarch64', '64' , '', d)}"

SRC_URI = "http://www.zgemma.org/downloads/zgemma-libs${VER}-${HICHIPSET}-${SRCDATE}.zip"

S = "${WORKDIR}"

INHIBIT_PACKAGE_STRIP = "1"

# Disable anything auto depending on zgemma-libs
EXCLUDE_FROM_SHLIBS = "1"

# The driver is a set of binary libraries to install
# there's nothing to configure or compile
do_configure[noexec] = "1"
do_compile[noexec] = "1"

do_install() {
	install -d ${D}${libdir}/hisilicon
	install -m 0755 ${S}/hisilicon/* ${D}${libdir}/hisilicon
	install -m 0755 ${S}/ffmpeg/* ${D}${libdir}/hisilicon
	if [ "${GLIBCVERSION}" = "2.25" ]; then
		install -m 0755 ${S}/glibc/* ${D}${libdir}/hisilicon
	else
		install -d ${D}/lib
		ln -sf /lib/ld-linux-armhf.so.3 ${D}${libdir}/hisilicon/ld-linux.so
	fi
}

do_package_qa() {
}

FILES_${PN} = "${libdir}/hisilicon/*"
FILES_${PN}-dev = ""

INSANE_SKIP_${PN} += "ldflags already-stripped dev-so"
