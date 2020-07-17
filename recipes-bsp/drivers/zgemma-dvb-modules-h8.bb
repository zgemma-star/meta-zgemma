KV = "4.4.35"
SRCDATE = "20200716"

require zgemma-dvb-modules.inc

SRC_URI[arm.md5sum] = "96a10a8ff9b82930a24cbe9a3811ef03"
SRC_URI[arm.sha256sum] = "52c2e3333993d813b5a82c230c71eef63a228222b575b2a322e7205f28a380b7"

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
