// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2018 Spreadtrum Communications Inc.
 * Copyright (C) 2018 Linaro Ltd.
 *  linux/drivers/gpio/gpio-nmcard.c
 * GPIO driver for the nmcard board
 *
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/of_gpio.h>

MODULE_AUTHOR("fengguo");
MODULE_LICENSE("GPL");

static int majorNumber = 0;

static const char *CLASS_NAME = "nm_class";

static const char *DEVICE_NAME = "nm";

static int basic_open(struct inode *node, struct file *file);
static ssize_t basic_read(struct file *file, char *buf, size_t len, loff_t *offset);
static ssize_t basic_write(struct file *file, const char *buf, size_t len, loff_t *offset);
static int basic_release(struct inode *node, struct file *file);


static char msg[50] = "OK";
static char recv_msg[50];

static struct class *basic_class = NULL;
static struct device *basic_device = NULL;
static char ret_msg[50] = "OK";

static struct file_operations file_oprts = {
	.open = basic_open,
	.read = basic_read,
	.write = basic_write,
	.release = basic_release,
};


static int __init basic_init(void)
{
	printk(KERN_ALERT "Driver init\r\n");

	majorNumber = register_chrdev(0, DEVICE_NAME, &file_oprts);
	if (majorNumber < 0) {
	printk(KERN_ALERT "Register failed!!\r\n");
	return majorNumber;
	}
	printk(KERN_ALERT "Registe success,major number is %d\r\n", majorNumber);

	basic_class = class_create(THIS_MODULE, CLASS_NAME);
	if (IS_ERR(basic_class)) {
		unregister_chrdev(majorNumber, DEVICE_NAME);
		return PTR_ERR(basic_class);
	}

	basic_device = device_create(basic_class, NULL, MKDEV(majorNumber, 0), NULL, DEVICE_NAME);
	if (IS_ERR(basic_device)) {
		class_destroy(basic_class);
		unregister_chrdev(majorNumber, DEVICE_NAME);
		return PTR_ERR(basic_device);
	}
	printk(KERN_ALERT "Basic device init success!!\r\n");

	return 0;
}

static int basic_open(struct inode *node, struct file *file)
{
	printk(KERN_ALERT "Open file\r\n");
	return 0;
}


static ssize_t basic_read(struct file *file, char *buf, size_t len, loff_t *offset)
{
	int cnt = 0;

	if (strcmp(recv_msg, "nm handshake")) {
		strcpy(msg, ret_msg);
	}

	cnt = copy_to_user(buf, msg, sizeof(msg));
	if (cnt == 0) {
		printk(KERN_INFO "Send file!!");
		return 0;
	}

	printk(KERN_ALERT "ERROR occur when reading!!");
	return -EFAULT;
	/*return sizeof(msg);*/
}

static ssize_t basic_write(struct file *file, const char *buf, size_t len, loff_t *offset)
{
	int cnt;

	memset(recv_msg, 0, sizeof(recv_msg));
	cnt = copy_from_user(recv_msg, buf, len);
	if (cnt != 0) {
		printk(KERN_ALERT "ERROR occur when writing!!");
		return -EFAULT;
	}

	printk(KERN_INFO "Recive data ,len = %s", recv_msg);
	if (!strcmp(recv_msg, "nm handshake")) {
		strcpy(ret_msg, "OK");
	} else if (!strcmp(recv_msg, "nm reset fail")) {
	// strcpy(ret_msg, "nm reset fail");
		printk(KERN_EMERG "gpio-nmcard nm reset fail");
	} else if (!strcmp(recv_msg, "nm hot plug out")) {
		gpio_request(128+39, "GPIOID");
		gpio_request(128+88, "GPIOID");
		printk(KERN_EMERG "gpio-nmcard set nm card mode");
		gpio_set_value(128+39, 1);
		gpio_set_value(128+88, 0);
		gpio_free(128+39);
		gpio_free(128+88);
	} else {
		printk(KERN_INFO "gpio-nmcard: wrong command!"); }
	return len;
}

static int basic_release(struct inode *node, struct file *file)
{
	printk(KERN_INFO "Release!!");
	return 0;
}

static void __exit basic_exit(void)
{
	device_destroy(basic_class, MKDEV(majorNumber, 0));
	class_unregister(basic_class);
	class_destroy(basic_class);
	unregister_chrdev(majorNumber, DEVICE_NAME);
}

module_init(basic_init);
module_exit(basic_exit);
