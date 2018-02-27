KV = "4.4.35"
SRCDATE = "20180227"

PROVIDES += " virtual/blindscan-dvbc virtual/blindscan-dvbs"

require zgemma-dvb-modules.inc

SRC_URI[md5sum] = "f0683b09062b30c9efd6c639c26939d2"
SRC_URI[sha256sum] = "99768ee6107bb6fab6fa504620aff6175d2bd9d94b42dc3da8713191598b7245"

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