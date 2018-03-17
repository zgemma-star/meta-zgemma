DESCRIPTION = "libgles v3ddriver headers"
LICENSE = "CLOSED"

PR = "r2"

SRC_URI = "file://libgles-headers.zip"

S = "${WORKDIR}"

do_compile() {
}

do_install_append() {
	install -d ${D}/${incdir}
	for d in EGL GLES GLES2 GLES3 KHR; do
		install -d ${D}${incdir}/$d
		for f in ${S}/$d/*.h; do
			install -m 0644 $f ${D}${incdir}/$d/
		done
	done
}

FILES_${PN}-dev = "${incdir}/*"