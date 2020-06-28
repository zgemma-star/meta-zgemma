DESCRIPTION = "CiPlus-helper"
LICENSE = "CLOSED"
PR = "${SRCDATE}"
PACKAGE_ARCH = "${MACHINE_ARCH}"

SRC_URI = "http://www.zgemma.org/downloads/ciplushelper-${HICHIPSET}-${SRCDATE}.zip \
	file://ciplushelper.sh \
	"

S = "${WORKDIR}"

INITSCRIPT_NAME = "ciplushelper"
INITSCRIPT_PARAMS = "defaults 50"

FILES_${PN} += "${bindir} ${sysconfdir}"

inherit update-rc.d

do_install() {
	install -d ${D}${bindir}
	install -m 0755 ciplushelper ${D}${bindir}
	install -d ${D}${sysconfdir}/init.d
	install -m 0755 ciplushelper.sh ${D}${sysconfdir}/init.d/ciplushelper
}

do_package_qa() {
}

INSANE_SKIP_${PN} += "ldflags already-stripped"
