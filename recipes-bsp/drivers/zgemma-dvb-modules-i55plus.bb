KV = "4.4.35"
SRCDATE = "20200720"

PROVIDES = "virtual/blindscan-dvbc virtual/blindscan-dvbs"

require zgemma-dvb-modules.inc

SRC_URI[arm.md5sum] = "6e9e3e266a0cd28809d6bbf2813a7743"
SRC_URI[arm.sha256sum] = "c0cd66021497542beae321744a72132ac3737de92ff31f4d07314bd553c9dbd4"

COMPATIBLE_MACHINE = "i55plus"

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
