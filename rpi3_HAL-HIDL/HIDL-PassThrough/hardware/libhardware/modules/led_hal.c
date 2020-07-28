/*
*
*/

#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <log/log.h>
#include <string.h>
#include <malloc.h>
#include <stdint.h>
#include <hardware/led_hal.h>

#define DEVICE_FILE 	"/dev/led_hal"

static int dev_open(const struct hw_module_t *module, const char *name, struct hw_device_t **device);

static struct hw_module_methods_t led_module_method = {
	.open = dev_open,
};

struct led_module_t HAL_MODULE_INFO_SYM = {
	.common = {
		.tag = HARDWARE_MODULE_TAG,
		.version_major = 1,
		.version_minor = 0,
		.id = LED_HARDWARE_MODULE_ID,
		.name = "led_hal",
		.author = "phonglt9",
		.methods = &led_module_method,
	},
};

static int led_on()
{
	int fd;
	int ret;
	char ch = '1';

	fd = open(DEVICE_FILE, O_RDWR);
	if(fd < 0) {
		ALOGE("Failed : cannot open device file %s\n", DEVICE_FILE);
		return -1;
	}
	
	ret = write(fd, &ch, sizeof(ch));
	if(ret < 0) {
		ALOGE("Failed : cannot write device file %s, value : %c\n", DEVICE_FILE, ch);
		return -1;
	}

	return 0;
}

static int led_off()
{
	int fd;
	int ret;
	char ch = '0';

	fd = open(DEVICE_FILE, O_RDWR);
	if(fd < 0) {
		ALOGE("Failed : cannot open device file %s\n", DEVICE_FILE);
		return -1;
	}

	ret = write(fd, &ch, sizeof(ch));
	if(ret < 0) {
		ALOGE("Failed : cannot write device file %s, value : %c\n", DEVICE_FILE, ch);
		return -1;
	}

	return 0;
}

static int led_status()
{
	int fd;
	int ret;
	char *buff = (char *)calloc(10, sizeof(char));

	fd = open(DEVICE_FILE, O_RDWR);
	if(fd < 0) {
		ALOGE("Failed : cannot open device file %s\n", DEVICE_FILE);
		return -1;
	}

	ret = read(fd, buff, sizeof(buff));
	if(ret < 0) {
		ALOGE("Failed : cannot read device file %s\n", DEVICE_FILE);
		return -1;
	}

	ALOGE("Led status : %s", buff);

	return 0;
}

static int dev_close(struct hw_device_t *device)
{
	if(device) 
		free(device);
	return 0;
}

static int dev_open(const struct hw_module_t *module, const char *name, struct hw_device_t **device) 
{
	struct led_device_t *led_dev;
	int (*config_led)(void);

	led_dev = (struct led_device_t *)calloc(1, sizeof(struct led_device_t));
	if(led_dev == NULL) {
		ALOGE("Unable to reserve memory for led_hal: %s\n", strerror(errno));
		return -ENOMEM;
	}

	if(!strncmp(name, "led_on", sizeof("led_on")))
		config_led = led_on;
	else if(!strncmp(name, "led_off", sizeof("led_off")))
		config_led = led_off;
	else
		return -EINVAL;

	/* Initialize common fields */
	led_dev->common.tag = HARDWARE_DEVICE_TAG;
	led_dev->common.version = 1;
	led_dev->common.module = (struct hw_module_t *) module;
	led_dev->common.close = dev_close;
	led_dev->config_led = config_led;
	led_dev->get_status = led_status;

	*device = (struct hw_device_t *)led_dev;

	ALOGE("Device is initialized\n");

	return 0;
}