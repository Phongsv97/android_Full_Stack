/*
 * Copyright (C) 2008 The Android Open Source Project
 * Copyright 2009-2016 Freescale Semiconductor, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <hardware/gpio_hal.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <cutils/log.h>
#include <cutils/atomic.h>
#include <cutils/properties.h>
#include <string.h>
#include <malloc.h>
#include <stdint.h>
#include <time.h>

#define VAL_NAME	"/sys/gpio_udoo/value"
#define DIR_NAME	"/sys/gpio_udoo/direction"

static int led_open(const struct hw_module_t *module, const char *name,
			struct hw_device_t **device);

static struct hw_module_methods_t led_module_method = {
	.open = led_open,
};

struct led_module_t HAL_MODULE_INFO_SYM = {
	.common = {
		.tag = HARDWARE_MODULE_TAG,
		.version_major = 1,
		.version_minor = 0,
		.id = LED_HARDWARE_MODULE_ID,
		.name = "led_module",
		.author = "tung",
		.methods = &led_module_method,
	},
};

static int dev_write_val(struct led_device_t *dev, int val)
{
	int fd;

	fd = open(VAL_NAME, O_RDWR);
	if (fd < 0) {
		ALOGE("Can not open file %s\n", VAL_NAME);
		return -1;
	}

	if (write(fd, &val, sizeof(val)) < 0) {
		ALOGE("Can not write %s\n", VAL_NAME);
		return -1;
	}

	return 0;
}

static int dev_write_dir(struct led_device_t *dev, int val)
{
	int fd;

	fd = open(DIR_NAME, O_RDWR);
	if (fd < 0) {
		ALOGE("Can not open file %s\n", DIR_NAME);
		return -1;
	}

	if (write(fd, &val, sizeof(val)) < 0) {
		ALOGE("Can not write %s\n", DIR_NAME);
		return -1;
	}

	return 0;
}

static int dev_close(struct hw_device_t * device)
{
	struct led_device_t* dev = (struct led_device_t *) device;
	if (dev)
		free(dev);

 	return 0;
}

static int led_open(const struct hw_module_t* module, const char *name,
		struct hw_device_t **device)
{
	struct led_device_t *led_dev;
	int (*led_config)(struct led_device_t *dev, int val);

	if (!strncmp(LED_SET_OUTPUT, name, 7))
		led_config = dev_write_dir;
	else if (!strncmp(LED_SET_VAL, name, 7))
		led_config = dev_write_val;
	else
		return -EINVAL;

	led_dev = calloc(1, sizeof(struct led_device_t));
	if (!led_dev) {
		return -ENOMEM;
	}

	led_dev.common.tag = HARDWARE_DEVICE_TAG;
	led_dev.common.version = 1;
	led_dev.common.module = (struct hw_moudle_t *) module;
	led_dev.common.close = dev_close;

	led_dev->config_led = led_config;

	*device = &led_dev->common;

	return 0;
}
