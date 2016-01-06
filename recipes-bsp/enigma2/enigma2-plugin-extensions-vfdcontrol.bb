DESCRIPTION = "VFD Control"
LICENSE = "GPLv2"

require conf/license/openpli-gplv2.inc
COMPATIBLE_MACHINE = "(sh1|h3|h4|h5|lc)"

SRC_URI = "file://__init__.py \
	file://plugin.py \
	file://Makefile.am \
	file://configure.ac \
"

S = "${WORKDIR}"
DEST = "${D}/usr/lib/enigma2/python/Plugins/Extensions/VfdControl"

PR = "r0"

FILES_${PN} = "/usr/lib/enigma2/python/Plugins/Extensions/VfdControl"

inherit autotools pkgconfig

do_compile () {
	oe_runmake
}

do_post_install() {
	install -d ${DEST}
	find ${DEST} -name '*.py' -exec rm {} \;
}

addtask post_install after do_install before do_package

# Fixup for missing "foreign" and "subdir-objects" in automake
do_configure_prepend() {
	sed -i 's/AM_INIT_AUTOMAKE.*$/AM_INIT_AUTOMAKE([foreign subdir-objects])/' ${S}/configure.ac ${S}/configure.ac
}