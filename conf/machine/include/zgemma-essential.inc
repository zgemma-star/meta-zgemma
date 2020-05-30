MACHINE_ESSENTIAL_EXTRA_RDEPENDS = "\
	zgemma-dvb-modules-${MACHINE} \
	${@bb.utils.contains('MACHINE_FEATURES', 'hisil-3798mv200', 'zgemma-libs-3798mv200 zgemma-param-3798mv200 zgemma-bootargs-3798mv200 zgemma-bootlogo-3798mv200 zgemma-fastboot-3798mv200 tntfs' , '', d)} \
	${@bb.utils.contains('MACHINE_FEATURES', 'hisil-3798mv200 emmc', 'zgemma-recovery-3798mv200' , '', d)} \
	\
	${@bb.utils.contains('MACHINE_FEATURES', 'hisil-3716mv430', 'zgemma-libs-3716mv430 zgemma-param-3716mv430 zgemma-bootargs-3716mv430 zgemma-bootlogo-3716mv430 zgemma-fastboot-3716mv430 tntfs' , '', d)} \
	"

MACHINE_ESSENTIAL_EXTRA_RRECOMMENDS = "\
	kernel-module-cdfs \
	\
	${@bb.utils.contains('MACHINE_FEATURES', 'v3d-nxpl', 'zgemma-v3ddriver-${MACHINE}' , '', d)} \
	${@bb.utils.contains('MACHINE_FEATURES', 'hisil-3798mv200', 'kernel-module-mali-3798mv200 zgemma-mali-3798mv200' , '', d)} \
	${@bb.utils.contains('MACHINE_FEATURES', 'wol', 'zgemma-ethwol' , '', d)} \
	${@bb.utils.contains('MACHINE_FEATURES', 'emmc', 'resizerootfs partitions-by-name' , '', d)} \
	${@bb.utils.contains('MACHINE_FEATURES', 'bluetooth', 'kernel-module-btusb bluez5' , '', d)} \
	\
	firmware-mt7601u \
	firmware-rtl8188eu \
	firmware-rtl8192eu \
	firmware-rtl8723bu \
	firmware-rtl8xxxu \
	\
	kernel-module-8192eu \
	kernel-module-8723bu \
	kernel-module-88x2bu \
	\
	kernel-module-mt7601u \
	kernel-module-r8723au \
	kernel-module-r8188eu \
	kernel-module-rtl8xxxu \
	"

OPTIONAL_EXTRA_DVBUSB_PACKAGES = "\
	enigma2-plugin-drivers-ct2-usb-xbox-one-tuner \
	"
