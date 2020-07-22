KV = "4.4.35"
SRCDATE = "20200720"

PROVIDES = "virtual/blindscan-dvbc virtual/blindscan-dvbs"

require zgemma-dvb-modules.inc

SRC_URI[arm.md5sum] = "8d57ff67bd460460c77afbec44c28e7d"
SRC_URI[arm.sha256sum] = "af65bc6ee3cc5e9189a292a6e0868edd32b5eac060cc557beb253340dba0928a"

COMPATIBLE_MACHINE = "h10"

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
