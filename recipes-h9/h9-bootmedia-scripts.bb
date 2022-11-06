DESCRIPTION = "PurE2 H9 boot from microSD, USB or NAND scripts"
PRIORITY = "optional"
LICENSE = "proprietary"

PR = "r1"

require conf/license/license-gplv2.inc

inherit allarch

SRC_URI = "file://*"


S = "${WORKDIR}"
INHIBIT_PACKAGE_STRIP = "1"

sysroot_stage_all() {
    :
}

do_install () {
    install -d ${D}/usr/script
    install -m 0755   ${WORKDIR}/*.sh    ${D}/usr/script/
    install -m 0755   ${WORKDIR}/*.bin    ${D}/usr/script/ 
}

FILES_${PN} = "/usr/script/*"
