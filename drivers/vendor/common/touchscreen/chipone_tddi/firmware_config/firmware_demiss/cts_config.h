#ifndef CTS_CONFIG_H
#define CTS_CONFIG_H

/** Driver version */
#define CFG_CTS_DRIVER_MAJOR_VERSION        1
#define CFG_CTS_DRIVER_MINOR_VERSION        2
#define CFG_CTS_DRIVER_PATCH_VERSION        2

#define CFG_CTS_DRIVER_VERSION              "v1.2.2"

/** Whether reset pin is used */
#define CFG_CTS_HAS_RESET_PIN
#define CONFIG_CTS_POINT_REPORT_CHECK
/** Whether force download firmware to chip */
/* #define CFG_CTS_FIRMWARE_FORCE_UPDATE */

/* #define CFG_CTS_FW_LOG_REDIRECT */
/** Use build in firmware or firmware file in fs*/
#define CFG_CTS_DRIVER_BUILTIN_FIRMWARE
#define CFG_CTS_FIRMWARE_IN_FS
#ifdef CFG_CTS_FIRMWARE_IN_FS
#define CFG_CTS_FIRMWARE_FILENAME       "ICNL9911.bin"
#define CFG_CTS_FIRMWARE_FILEPATH       "/vendor/firmware/ICNL9911.bin"
#endif /* CFG_CTS_FIRMWARE_IN_FS */

#define CFG_CTS_UPDATE_CRCCHECK
#ifdef CONFIG_PROC_FS
    /* Proc FS for backward compatibility for APK tool com.ICN85xx */
#define CONFIG_CTS_LEGACY_TOOL
#endif /* CONFIG_PROC_FS */

#ifdef CONFIG_SYSFS
    /* Sys FS for gesture report, debug feature etc. */
#define CONFIG_CTS_SYSFS
#endif /* CONFIG_SYSFS */

#define CFG_CTS_MAX_TOUCH_NUM               (10)

/* Virtual key support */
/* #define CONFIG_CTS_VIRTUALKEY */
#ifdef CONFIG_CTS_VIRTUALKEY
#define CFG_CTS_MAX_VKEY_NUM            (4)
#define CFG_CTS_NUM_VKEY                (3)
#define CFG_CTS_VKEY_KEYCODES           {KEY_BACK, KEY_HOME, KEY_MENU}
#endif /* CONFIG_CTS_VIRTUALKEY */

/* Gesture wakeup */
#define CONFIG_CTS_GESTURE
#ifdef CONFIG_CTS_GESTURE
#define GESTURE_UP                          0x11
#define GESTURE_C                           0x12
#define GESTURE_O                           0x13
#define GESTURE_M                           0x14
#define GESTURE_W                           0x15
#define GESTURE_E                           0x16
#define GESTURE_S                           0x17
#define GESTURE_Z                           0x1d
#define GESTURE_V                           0x1e
#define GESTURE_D_TAP                       0x50

#define CFG_CTS_NUM_GESTURE             (9u)
#define CFG_CTS_GESTURE_REPORT_KEY
#define CFG_CTS_GESTURE_KEYMAP  \
	{{GESTURE_C, KEY_C,}, \
	  {GESTURE_W, KEY_W,}, \
	  {GESTURE_V, KEY_V,}, \
	  {GESTURE_D_TAP, KEY_GESTURE_DOUBLEC,}, \
	  {GESTURE_Z, KEY_Z,}, \
	  {GESTURE_M, KEY_M,},  \
	  {GESTURE_O, KEY_O,},   \
	  {GESTURE_E, KEY_E,},  \
	  {GESTURE_S, KEY_S,},  \
	}
#define CFG_CTS_GESTURE_REPORT_TRACE    0
#endif /* CONFIG_CTS_GESTURE */

/* #define CONFIG_CTS_GLOVE */
#define CFG_CTS_ROTATION
#define CFG_CTS_EDGE_LIMIT
#define CTS_REPORT_BY_ZTE_ALGO
#define CFG_CTS_HEADSET_DETECT
#define CONFIG_CTS_CHARGER_DETECT
#define CONFIG_CTS_CHARGER_DETECT_FILE		"/sys/class/power_supply/battery/present"

#ifdef CTS_REPORT_BY_ZTE_ALGO
#define cts_left_edge_limit_v			6
#define cts_right_edge_limit_v			6
#define cts_left_edge_limit_h			15
#define cts_right_edge_limit_h		10
#define cts_left_edge_long_pess_v		20
#define cts_right_edge_long_pess_v	20
#define cts_left_edge_long_pess_h		40
#define cts_right_edge_long_pess_h	20
#define cts_long_press_max_count		80
#define cts_edge_long_press_check	1
#endif
/* ESD protection */
/* #define CONFIG_CTS_ESD_PROTECTION */
#ifdef CONFIG_CTS_ESD_PROTECTION
#define CFG_CTS_ESD_PROTECTION_CHECK_PERIOD         (2 * HZ)
#endif /* CONFIG_CTS_ESD_PROTECTION */

/* Use slot protocol (protocol B), comment it if use protocol A. */
#define CONFIG_CTS_SLOTPROTOCOL

/*
 * Report Pressure in multitouch
 * 1:enable(default),0:disable
*/
#define CFG_REPORT_PRESSURE_EN                  0

#ifdef CONFIG_CTS_LEGACY_TOOL
#define CFG_CTS_TOOL_PROC_FILENAME      "icn85xx_tool"
#endif /* CONFIG_CTS_LEGACY_TOOL */

/****************************************************************************
 * Platform configurations
 ****************************************************************************/

#include "cts_plat_config.h"
/****************************************************************************
 * firmware configurations
 ****************************************************************************/

#define VENDOR_ID1	0xb6
#define VENDOR_ID2	0xa5
#define VENDOR_ID3	0x99
#define VENDOR_ID4	0x00

#define CTS_VENDOR1_NAME		"lianchuang_newboe"
#define CTS_VENDOR2_NAME		"icnl9911c"
#define CTS_VENDOR3_NAME		"lianchuang"
#define CTS_VENDOR4_NAME		"unknown"
#endif /* CTS_CONFIG_H */
