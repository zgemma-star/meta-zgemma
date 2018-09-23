KV = "4.4.35"
SRCDATE = "20180922"

PROVIDES = "virtual/blindscan-dvbc virtual/blindscan-dvbs"

require zgemma-dvb-modules.inc

SRC_URI[arm.md5sum] = "b74aba697b27cc890f98ee7e0116adc6"
SRC_URI[arm.sha256sum] = "f7fca80cd8e1409f86cf3d5295882ab8c015ea2f6a64cfc91def53c1f65f4eb5"

COMPATIBLE_MACHINE = "i55plus"

INITSCRIPT_NAME = "suspend"
INITSCRIPT_PARAMS = "start 89 0 ."
inherit update-rc.d

do_configure[noexec] = "1"

# Generate a simplistic standard init script
do_compile_append () {
	cat > suspend << EOF
#!/bin/sh

if [ "x" == "stopx" ]
then
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
