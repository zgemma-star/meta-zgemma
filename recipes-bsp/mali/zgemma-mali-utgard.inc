DESCRIPTION = "Mali OpenGL"
SECTION = "base"
PRIORITY = "required"
LICENSE = "CLOSED"
PACKAGE_ARCH = "${MACHINE_ARCH}"
PR = "${SRCDATE}"
VER ?= "${@bb.utils.contains('TARGET_ARCH', 'aarch64', '64' , '', d)}"
DEPENDS = "zgemma-mali-utgard-headers"

PROVIDES = "virtual/libgles2 virtual/libgles1 virtual/egl virtual/libopencl"
RPROVIDES_${PN} = "libmali.so libEGL.so libGLESv1_CM.so libGLESv2.so"

SRC_URI = "http://www.zgemma.org/downloads/${MACHINE}-mali${VER}-${SRCDATE}.zip"

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
	ln -sf libMali.so ${D}${libdir}/libmali.so
	ln -sf libMali.so ${D}${libdir}/libEGL.so
	ln -sf libMali.so ${D}${libdir}/libGLESv1_CM.so
	ln -sf libMali.so ${D}${libdir}/libGLESv2.so
	install -m 0644 ${S}/50-mali.rules ${D}${sysconfdir}/udev/rules.d/50-mali.rules
}

do_package_qa() {
}

FILES_${PN} = "${libdir} /etc/udev/rules.d/50-mali.rules"
FILES_${PN}-dev = "${incdir}"

INSANE_SKIP_${PN} += "already-stripped dev-so ldflags"