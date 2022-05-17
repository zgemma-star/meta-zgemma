KV = "4.4.35"
SRCDATE = "20201118"

require zgemma-dvb-himodules.inc

SRC_URI[arm.md5sum] = "c5273a14e751fe52125c86deed3436e1"
SRC_URI[arm.sha256sum] = "215f07119f8ddaeb7a992e41721c58d35a3bc73f4ffc5a07c3cfeb55556a8da9"


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
