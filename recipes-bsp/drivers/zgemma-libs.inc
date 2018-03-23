DESCRIPTION = "${MACHINE} libraries"
SECTION = "base"
PRIORITY = "required"
LICENSE = "CLOSED"
PACKAGE_ARCH = "${MACHINE_ARCH}"
VER ?= "${@bb.utils.contains('TARGET_ARCH', 'aarch64', '64' , '', d)}"

DEPENDS = "zlib libpng freetype curl libxml2 libjpeg-turbo harfbuzz"

SRC_URI = "http://www.zgemma.org/downloads/zgemma-libs${VER}-${MACHINE}-${SRCDATE}.zip"

S = "${WORKDIR}"

INHIBIT_PACKAGE_STRIP = "1"

# The driver is a set of binary libraries to install
# there's nothing to configure or compile
do_configure[noexec] = "1"
do_compile[noexec] = "1"

do_install() {
	install -d ${D}${libdir}/hisilicon
	install -m 0755 ${S}/hisilicon/* ${D}${libdir}/hisilicon
}

do_package_qa() {
}

FILES_${PN} = "${libdir}/hisilicon/*"

INSANE_SKIP_${PN} += "ldflags already-stripped dev-so"