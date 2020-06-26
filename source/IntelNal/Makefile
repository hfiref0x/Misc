iqvandroid-objs := \
	src/linuxnaldriver.o \
	src/linuxdriverpci_i.o \
	src/linuxdriveros_i.o \
	src/linuxdriverdevice_i.o \
	src/nalioctldrv.o

EXTRA_CFLAGS := \
	-DNAL_LINUX -DNAL_LINUX_ANDROID -DNAL_DRIVER -DLINUX -D__KERNEL__ -DMODULE \
	-Idrivers/external_drivers/drivers/misc/iqvandroid/inc/ \
	-Idrivers/external_drivers/drivers/misc/iqvandroid/inc/linux \

obj-$(CONFIG_INTEL_IQVANDROID) = iqvandroid.o
