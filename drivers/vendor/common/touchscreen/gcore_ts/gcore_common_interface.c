/************************************************************************
*
* File Name: himax_common_interface.c
*
*  *   Version: v1.0
*
************************************************************************/
#include "gcore_drv_common.h"

#define MAX_FILE_NAME_LEN       64
#define MAX_FILE_PATH_LEN  64
#define MAX_NAME_LEN_20  20

char gcore_vendor_name[MAX_NAME_LEN_20] = { 0 };
char gcore_firmware_name[MAX_FILE_NAME_LEN] = {0};
char gcore_default_firmware_name[MAX_FILE_NAME_LEN] = {0};
char gcore_firmware_mp_name[MAX_FILE_NAME_LEN] = {0};
int gcore_vendor_id = 0;

extern int gcore_flashdownload_fspi_proc(void *fw_buf);

struct tpvendor_t gcore_vendor_l[] = {
	{GTP_VENDOR_ID_0, GTP_VENDOR_0_NAME},
	{GTP_VENDOR_ID_1, GTP_VENDOR_1_NAME},
	{GTP_VENDOR_ID_2, GTP_VENDOR_2_NAME},
	{GTP_VENDOR_ID_3, GTP_VENDOR_3_NAME},
	{VENDOR_END, "Unknown"},
};


int gcore_get_fw(void)
{
	int i = 0;
	int ret = 0;
	const char *panel_name = NULL;

	panel_name = get_lcd_panel_name();
	for (i = 0; i < ARRAY_SIZE(gcore_vendor_l); i++) {
		if (strnstr(panel_name, gcore_vendor_l[i].vendor_name, strlen(panel_name))) {
			gcore_vendor_id = gcore_vendor_l[i].vendor_id;
			strlcpy(gcore_vendor_name, gcore_vendor_l[i].vendor_name,
				sizeof(gcore_vendor_name));
			ret = 0;
			goto out;
		}
	}
	strlcpy(gcore_vendor_name, "Unknown", sizeof(gcore_vendor_name));
	ret = -EIO;
out:
	snprintf(gcore_firmware_name, sizeof(gcore_firmware_name),
			"gcore_firmware_%s.bin", gcore_vendor_name);
	return ret;
}

const struct ts_firmware *gcore_tp_requeset_firmware(char *file_name)
{
	struct file *file = NULL;
	char file_path[128] = { 0 };
	struct ts_firmware *firmware = NULL;
	int ret = 0;
	loff_t pos = 0;
	loff_t file_len = 0;

	snprintf(file_path, sizeof(file_path), "%s%s", "/sdcard/", file_name);
	file = filp_open(file_path, O_RDONLY, 0);
	if (IS_ERR(file)) {
		GTP_ERROR("open %s file fail, try open /vendor/firmware/", file_path);
		snprintf(file_path, sizeof(file_path), "%s%s", "/vendor/firmware/", file_name);
		file = filp_open(file_path, O_RDONLY, 0);
		if (IS_ERR(file)) {
			GTP_ERROR("open %s file fail", file_path);
			return NULL;
		}
	}

	firmware = kzalloc(sizeof(struct ts_firmware), GFP_KERNEL);
	if (firmware == NULL) {
		GTP_ERROR("Request from file alloc struct firmware failed");
		goto err_close_file;
	}
	file_len = file_inode(file)->i_size;
	firmware->size = (int)file_len;
	GTP_INFO("open %s file ,firmware->size:%d", file_path, firmware->size);
	firmware->data = vmalloc(firmware->size);
	if (firmware->data == NULL) {
		GTP_ERROR("alloc firmware data failed");
		goto err_free_firmware;
	}

	pos = 0;
#if (KERNEL_VERSION(4, 14, 0) <= LINUX_VERSION_CODE)
	ret = kernel_read(file, firmware->data, file_len, &pos);
#else
	ret = kernel_read(file, 0, firmware->data, file_len);
#endif
	if (ret < 0) {
		GTP_ERROR("Request from fs read whole file failed %d", ret);
		goto err_free_firmware_data;
	}
	filp_close(file, NULL);
	return firmware;
err_free_firmware_data:
	vfree(firmware->data);
err_free_firmware:
	kfree(firmware);
err_close_file:
	filp_close(file, NULL);

	return NULL;
}

static int gcore_tp_fw_upgrade(struct tpd_classdev_t *cdev, char *fw_name, int fwname_len)
{
	char fileName[128] = {0};
	const struct ts_firmware *firmware = NULL;

	memset(fileName, 0, sizeof(fileName));
	snprintf(fileName, sizeof(fileName), "%s", fw_name);
	fileName[fwname_len - 1] = '\0';
	GTP_INFO("%s: upgrade from file(%s) start!\n", __func__, fileName);
	firmware = gcore_tp_requeset_firmware(fileName);
	if (firmware == NULL) {
		GTP_ERROR("Request from file '%s' failed", fileName);
		goto error_fw_upgrade;
	}
#if defined(CONFIG_ENABLE_CHIP_TYPE_GC7202)
	if (gcore_flashdownload_fspi_proc(firmware->data)) {
		GTP_ERROR("flashdownload fspi proc fail");
		goto fw_upgrade_fail;
	}
#endif
	vfree(firmware->data);
	kfree(firmware);
	return 0;
fw_upgrade_fail:
	vfree(firmware->data);
	kfree(firmware);
error_fw_upgrade:
	return -EIO;
}


static int tpd_init_tpinfo(struct tpd_classdev_t *cdev)
{
	u8 read_data[4] = { 0 };

	gcore_read_fw_version(read_data, sizeof(read_data));
	strlcpy(cdev->ic_tpinfo.tp_name, "gcore_ts", sizeof(cdev->ic_tpinfo.tp_name));
	strlcpy(cdev->ic_tpinfo.vendor_name, gcore_vendor_name, sizeof(cdev->ic_tpinfo.vendor_name));
	cdev->ic_tpinfo.chip_model_id = TS_CHIP_GCORE;
	cdev->ic_tpinfo.firmware_ver = read_data[1] << 24 | read_data[0] << 16 | read_data[3] << 8 | read_data[2];
	cdev->ic_tpinfo.module_id = gcore_vendor_id;
	cdev->ic_tpinfo.i2c_type = 1;
	return 0;
}

int gcore_register_fw_class(void)
{
	tpd_fw_cdev.get_tpinfo = tpd_init_tpinfo;
	tpd_fw_cdev.tp_fw_upgrade = gcore_tp_fw_upgrade;
	gcore_get_fw();
	return 0;
}




