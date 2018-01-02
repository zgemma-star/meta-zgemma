DESCRIPTION = "Mali OpenGL"
SECTION = "base"
PRIORITY = "required"
LICENSE = "CLOSED"
PACKAGE_ARCH = "${MACHINE_ARCH}"

PROVIDES += " virtual/libgles2 virtual/libgles1 virtual/egl virtual/libopencl"
DEPENDS = "zgemma-mali-headers"

SRCDATE = "20171106"

COMPATIBLE_MACHINE = "h9"

SRC_URI = "http://www.zgemma.org/downloads/${MACHINE}-mali-${SRCDATE}.zip"

SRC_URI[md5sum] = "01234564789abcdef01234564789abcdef"
SRC_URI[sha256sum] = "01234564789abcdef01234564789abcdef01234564789abcdef1234564789abcdef"

S = "${WORKDIR}"

# The driver is a set of binary libraries to install
# there's nothing to configure or compile
do_configure[noexec] = "1"

# Generate a mali rules script
do_compile_append () {
	cat > 50-mali.rules << EOF
KERNEL=="mali0", MODE="0660", GROUP="video"
EOF
}

do_install_append() {
	install -d ${D}${libdir}
	install -d ${D}${sysconfdir}/udev/rules.d
	install -m 0755 ${S}/libMali.so ${D}${libdir}
	ln -s libMali.so ${D}${libdir}/libmali.so
	ln -s libMali.so ${D}${libdir}/libEGL.so
	ln -s libMali.so ${D}${libdir}/libGLESv1_CM.so
	ln -s libMali.so ${D}${libdir}/libGLESv2.so
	install -m 0644 ${S}/50-mali.rules ${D}${sysconfdir}/udev/rules.d/50-mali.rules
}

FILES_${PN} = "/usr/lib/* /etc/udev/rules.d/50-mali.rules"
FILES_${PN}-dev = "/usr/include/*"

INSANE_SKIP_${PN} += "already-stripped dev-so ldflags"