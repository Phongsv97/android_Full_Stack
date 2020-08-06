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
#include <hardware/led_hal.h>

#define DEVICE_FILE 	"/dev/hello_hal"

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

	close(fd);

	return 0;
}

static int led_off()
{
	int fd;
	int ret;
	char ch = '0';

	fd = open(DEVICE_FILE, O_RDWR);
	if(fd < 0) {
		ALOGE("PHONGLT : cannot open device file %s\n", DEVICE_FILE);
		return -1;
	}

	ret = write(fd, &ch, sizeof(ch));
	if(ret < 0) {
		ALOGE("PHONGLT : cannot write device file %s, value : %c\n", DEVICE_FILE, ch);
		return -1;
	}

	close(fd);

	return 0;
}

static int get_status(const char *buff)
{
	int fd;
	int ret;

	fd = open(DEVICE_FILE, O_RDWR);
	if(fd < 0) {
		ALOGE("PHONGLT cannot open device file %s\n", DEVICE_FILE);
		return -1;
	}

	ret = read(fd, buff, sizeof(buff));
	if(ret < 0) {
		ALOGE("PHONGLT cannot read device file %s\n", DEVICE_FILE);
		return -1;
	}

	ALOGE("PHONGLT Led status : %s", buff);
	
	close(fd);

	return 0;
}

static int config_led(const char *name)
{
	if(!strncmp(name, "led_on", sizeof("led_on"))) {
		led_on();
		return 0;
	}
	else if(!strncmp(name, "led_off", sizeof("led_off"))) {
		led_off();
		return 0;
	}
	
	return -EINVAL;
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

	led_dev = (struct led_device_t *)calloc(1, sizeof(struct led_device_t));
	if(led_dev == NULL) {
		ALOGE("PHONGLT Unable to reserve memory for led_hal: %s, ID: %s\n", strerror(errno), name);
		return -ENOMEM;
	}

	/* Initialize common fields */
	led_dev->common.tag = HARDWARE_DEVICE_TAG;
	led_dev->common.version = 1;
	led_dev->common.module = (struct hw_module_t *) module;
	led_dev->common.close = dev_close;
	led_dev->config_led = config_led;
	led_dev->get_status = get_status;

	*device = (struct hw_device_t *)led_dev;

	ALOGE("PHONGLT Device is initialized\n");

	return 0;
}