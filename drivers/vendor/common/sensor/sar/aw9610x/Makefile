#
# Copyright (C) 2015 MediaTek Inc.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License version 2 as
# published by the Free Software Foundation.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#

# In case the platform does NOT support this type of sensors

ifdef CONFIG_VENDOR_SOC_MTK_COMPILE
ifeq ($(subst ",,$(CONFIG_MTK_SENSOR_ARCHITECTURE)), 1.0)
ccflags-y += -D SENSOR_ARCH_1_0
ccflags-y += -I$(srctree)/drivers/misc/mediatek/sensors-1.0/situation/
ccflags-y += -I$(srctree)/drivers/misc/mediatek/sensors-1.0/hwmon/include
ccflags-y += -I$(srctree)/drivers/misc/mediatek/sensors-1.0/sensorHub/inc_v1
ccflags-y += -I$(srctree)/drivers/misc/mediatek/scp/$(CONFIG_MTK_PLATFORM)
endif
ifeq ($(subst ",,$(CONFIG_MTK_SENSOR_ARCHITECTURE)), 2.0)
ccflags-y += -I$(srctree)/drivers/misc/mediatek/sensor/2.0/core
ccflags-y += -D SENSOR_ARCH_2_0
endif
endif

obj-y += aw_bin_parse.o aw9610x.o