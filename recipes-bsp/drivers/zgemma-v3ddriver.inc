DESCRIPTION = "V3DDRIVER for ${MACHINE}"
SECTION = "base"
PRIORITY = "required"
LICENSE = "CLOSED"
PACKAGE_ARCH = "${MACHINE_ARCH}"
DEPENDS = "zgemma-v3ddriver-headers"

PROVIDES = "virtual/libgles2 virtual/egl"
RPROVIDES_${PN} = "libnxpl.so libnexus.so libv3ddriver.so libGLESv2.so libEGL.so"

PV = "${SRCDATE}"
PR = "r0"

SRC_URI = "http://www.zgemma.org/downloads/${MACHINE}-v3ddriver-${SRCDATE}.zip"

S = "${WORKDIR}"

do_configure() {
}

do_compile() {
}

do_install_append() {
	install -d ${D}${libdir}
	install -m 0755 ${S}/libnxpl.so ${D}${libdir}/
	install -m 0755 ${S}/libnexus.so ${D}${libdir}/
	install -m 0755 ${S}/libv3ddriver.so ${D}${libdir}/
	ln -sf libv3ddriver.so ${D}${libdir}/libEGL.so
	ln -sf libv3ddriver.so ${D}${libdir}/libGLESv2.so
}

FILES_${PN} = "${libdir}"
FILES_${PN}-dev = "${incdir}"

INSANE_SKIP_${PN} += "already-stripped dev-so ldflags"