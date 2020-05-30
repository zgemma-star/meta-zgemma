SUMMARY = "Hardware drivers for TNTFS"
SECTION = "base"
PRIORITY = "required"
LICENSE = "CLOSED"
require conf/license/license-close.inc

VER ?= "${@bb.utils.contains('TARGET_ARCH', 'aarch64', '_64bit' , '', d)}"
KV = "4.4.35"

COMPATIBLE_MACHINE = "^h9$|^h9combo$|^h10$|^i55plus$|^hzero$"

SRC_URI = "file://tntfs_${HICHIPSET}_4.4.y${VER}.ko"

S = "${WORKDIR}"

INHIBIT_PACKAGE_STRIP = "1"

do_compile() {
}
do_populate_sysroot() {
}

do_install() {
    install -d ${D}${base_libdir}/modules/${KV}/extra
    install -d ${D}/${sysconfdir}/modules-load.d
    install -m 0755 ${S}/tntfs_${HICHIPSET}_4.4.y${VER}.ko ${D}${base_libdir}/modules/${KV}/extra/tntfs.ko
    echo tntfs >> ${D}/${sysconfdir}/modules-load.d/tntfs.conf
}

FILES_${PN} += "${sysconfdir}/modules-load.d/tntfs.conf /lib/modules/${KV}/extra"