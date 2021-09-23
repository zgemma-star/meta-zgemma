KV = "4.4.35"
SRCDATE = "20201118"

require zgemma-dvb-modules.inc

SRC_URI[arm.md5sum] = "da99936ca67e851f754e580eb3703252"
SRC_URI[arm.sha256sum] = "766c97809e3ccfbd7d4f9e57c91797ee1b6c518ff4d9b0016049b6948d66fc1f"

COMPATIBLE_MACHINE = "h8"

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

mount -t proc proc /proc
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
