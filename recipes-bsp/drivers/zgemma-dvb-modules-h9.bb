KV = "4.4.35"
SRCDATE = "20180123"

require zgemma-dvb-modules.inc

SRC_URI[md5sum] = "1bb2b0d07c6cd54515187642eb6b9fdb"
SRC_URI[sha256sum] = "f8c33eeb1f6f27ee3ea3957fef66ed5ccdb6b616ef7d51aacfb9a9c932387b56"

COMPATIBLE_MACHINE = "h9"

INITSCRIPT_NAME = "suspend"
INITSCRIPT_PARAMS = "start 89 0 ."
inherit update-rc.d

do_configure[noexec] = "1"

# Generate a simplistic standard init script
do_compile_append () {
	cat > suspend << EOF
#!/bin/sh

mount -t sysfs sys /sys

/usr/bin/turnoff_power
EOF
}

do_install_append() {
	install -d ${D}${sysconfdir}/init.d
	install -d ${D}${bindir}
	install -m 0755 ${S}/suspend ${D}${sysconfdir}/init.d
	install -m 0755 ${S}/turnoff_power ${D}${bindir}
}

do_package_qa() {
}

FILES_${PN} += " ${bindir} ${sysconfdir}/init.d"

INSANE_SKIP_${PN} += "already-stripped"