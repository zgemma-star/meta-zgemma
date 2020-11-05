KV = "4.4.35"
SRCDATE = "20201104"

require zgemma-dvb-himodules.inc

SRC_URI[arm.md5sum] = "0e583118804b75dfbecaa74f68e56225"
SRC_URI[arm.sha256sum] = "b61d8930570acd6a668cb36fd8feb8a001fcb8b39ad056785c531b4805dde3c0"


COMPATIBLE_MACHINE = "hzero"

INITSCRIPT_NAME = "suspend"
INITSCRIPT_PARAMS = "start 89 0 ."
inherit update-rc.d

do_configure[noexec] = "1"

# Generate a simplistic standard init script
do_compile_append () {
	cat > suspend << EOF
#!/bin/sh

runlevel=runlevel | cut -d' ' -f2

if [ "\$runlevel" != "0" ] ; then
	exit 0
fi

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
