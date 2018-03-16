DESCRIPTION = "Hardware drivers for ${MACHINE}"
SECTION = "base"
PRIORITY = "required"
LICENSE = "CLOSED"
VER ?= "${@bb.utils.contains('TARGET_ARCH', 'aarch64', '64' , '', d)}"

PV = "${KV}-${SRCDATE}"

SRC_URI = "http://www.zgemma.org/downloads/${MACHINE}-drivers${VER}-${PV}.zip;name=${ARCH}"

S = "${WORKDIR}"

INHIBIT_PACKAGE_STRIP = "1"

inherit module

FILES_${PN} += "${sysconfdir}/modules-load.d/_${MACHINE}.conf"

do_compile() {
}

do_install() {
	install -d ${D}/lib/modules/${KV}/extra
	install -d ${D}${sysconfdir}/modules-load.d
	install -m 0755 ${S}/*.ko ${D}${base_libdir}/modules/${KV}/extra
	for i in ${MACHINE}_1 ${MACHINE}_2 ${MACHINE}_3 ${MACHINE}_4; do
		echo $i >> ${D}${sysconfdir}/modules-load.d/_${MACHINE}.conf
	done
}

pkg_prerm_${PN}() {
	if [ "x$D" == "x" ]; then
		if [ -f /lib/modules/${KV}/extra/hi_play.ko ] ; then
			rm -f /lib/modules/${KV}/extra/hi_play.ko;
		fi
	fi
}