DESCRIPTION = "libgles mali headers"
LICENSE = "CLOSED"

PR = "r0"

SRC_URI = "file://libgles-headers.zip"

DEPENDS += "libomxil"

S = "${WORKDIR}"

do_compile() {
}

do_install_append() {
	install -d ${D}/${includedir}
	for d in EGL GLES GLES2 GLES3 KHR; do
		install -d ${D}${includedir}/$d
		for f in ${S}/$d/*.h; do
			install -m 0644 $f ${D}${includedir}/$d/
		done
	done
}

FILES_${PN}-dev = "/usr/include/*"