
/************************************************************************
*
* File Name: tlsc6x_config.h
*
*  Abstract: global configurations
*
*   Version: v1.0
*
************************************************************************/
#ifndef _LINUX_TLSC6X_CONFIG_H_
#define _LINUX_TLSC6X_CONFIG_H_

#define TLSC_APK_DEBUG		/* apk debugger, close:undef */
#define TLSC_AUTO_UPGRADE
#define TLSC_ESD_HELPER_EN	/* esd helper, close:undef */
/* #define TLSC_GESTRUE */
#define TLSC_TP_PROC_SELF_TEST

/* #define TLSC_BUILDIN_BOOT */
/* #define TLSC_CHIP_NAME "chsc6440" */
#define TLSC_REPORT_BY_ZTE_ALGO
#ifdef TLSC_REPORT_BY_ZTE_ALGO
#define tlsc_left_edge_limit_v		6
#define tlsc_right_edge_limit_v		6
#define tlsc_left_edge_limit_h		6
#define tlsc_right_edge_limit_h		6
#define tlsc_left_edge_long_pess_v		20
#define tlsc_right_edge_long_pess_v	20
#define tlsc_left_edge_long_pess_h		40
#define tlsc_right_edge_long_pess_h	20
#define tlsc_long_press_max_count		60
#define tlsc_edge_long_press_check 1
#endif
#endif /* _LINUX_TLSC6X_CONFIG_H_ */
