SUMMARY = "${MACHINE} partitions files"
SECTION = "base"
PRIORITY = "required"
LICENSE = "CLOSED"
PACKAGE_ARCH = "${MACHINE_ARCH}"

inherit deploy

PR = "${SRCDATE}"

SRC_URI = "http://www.zgemma.org/downloads/${MACHINE}-partitions_${SRCDATE}.zip"

S = "${WORKDIR}"

ALLOW_EMPTY_${PN} = "1"

do_deploy() {
    install -d ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions/${MACHINE}
    install -m 0755 ${WORKDIR}/bootargs.bin ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions
    install -m 0755 ${WORKDIR}/fastboot.bin ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions
    install -m 0755 ${WORKDIR}/${MACHINE}/fastboot.bin ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions/${MACHINE}
    install -m 0755 ${WORKDIR}/${MACHINE}/pq_param.bin ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions/${MACHINE}
    install -m 0755 ${WORKDIR}/${MACHINE}/bootargs.bin ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions/${MACHINE}
    install -m 0755 ${WORKDIR}/${MACHINE}/baseparam.img ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions/${MACHINE}
    install -m 0755 ${WORKDIR}/${MACHINE}/logo.img ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions/${MACHINE}
}

addtask deploy before do_build after do_install

INSANE_SKIP_${PN} += "already-stripped"