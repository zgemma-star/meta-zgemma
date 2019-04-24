MACHINE_ESSENTIAL_EXTRA_RDEPENDS = "\
	zgemma-dvb-modules-${MACHINE} \
	${@bb.utils.contains('MACHINE_FEATURES', 'hisil-3798mv200', 'zgemma-libs-3798mv200 zgemma-param-3798mv200 zgemma-bootargs-3798mv200 zgemma-bootlogo-3798mv200 zgemma-fastboot-3798mv200' , '', d)} \
	${@bb.utils.contains('MACHINE_FEATURES', 'hisil-recovery', 'zgemma-recovery-3798mv200' , '', d)} \
	"

MACHINE_ESSENTIAL_EXTRA_RRECOMMENDS = "\
	kernel-module-cdfs \
	\
	${@bb.utils.contains('MACHINE_FEATURES', 'v3d-nxpl', 'zgemma-v3ddriver-${MACHINE}' , '', d)} \
	${@bb.utils.contains('MACHINE_FEATURES', 'hisil-3798mv200', 'kernel-module-mali-3798mv200 zgemma-mali-3798mv200' , '', d)} \
	${@bb.utils.contains('MACHINE_FEATURES', 'wol', 'zgemma-ethwol' , '', d)} \
	${@bb.utils.contains('MACHINE_FEATURES', 'emmc', 'resizerootfs partitions-by-name' , '', d)} \
	\
	firmware-carl9170 \
	firmware-htc7010 \
	firmware-htc9271 \
	firmware-mt7601u \
	firmware-rt2870 \
	firmware-rt73 \
	firmware-rtl8712u \
	firmware-rtl8188eu \
	firmware-rtl8192eu \
	firmware-rtl8192cu \
	firmware-rtl8xxxu \
	firmware-zd1211 \
	\
	rtl8192eu \
	\
	kernel-module-ath9k-htc \
	kernel-module-carl9170 \
	kernel-module-mt7601u \
	kernel-module-r8712u \
	kernel-module-r8723au \
	kernel-module-r8188eu \
	kernel-module-rt2500usb \
	kernel-module-rt2800usb \
	kernel-module-rt73usb \
	kernel-module-rtl8187 \
	kernel-module-rtl8192cu \
	kernel-module-rtl8xxxu \
	kernel-module-zd1211rw \
	"
