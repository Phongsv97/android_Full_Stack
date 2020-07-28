/*
 * Copyright (C) 2008 The Android Open Source Project
 * Copyright 2019 VN R&D software team.
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

#define  LOG_TAG  "voldown"

#include <errno.h>
#include <ctype.h>
#include <dirent.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include <utils/Log.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#include <hardware/hardware.h>
#include <hardware/voldown.h>

#define DEVICE_FILE		"/dev/vol_btn"

static int btn_open(const struct hw_module_t *module, const char *name,
			struct hw_device_t **device);

static struct hw_module_methods_t btn_module_method = {
	.open = btn_open,
};

struct vol_module_t HAL_MODULE_INFO_SYM = {
	.common = {
		.tag = HARDWARE_MODULE_TAG,
		.version_major = 1,
		.version_minor = 0,
		.id = VOL_HARDWARE_MODULE_ID,
		.name = "vol_module",
		.author = "tungnt",
		.methods = &btn_module_method,
	},
};

static int btn_stat_read(struct vol_device_t *dev)
{
	int fd;
	int ret;
	int status;

	fd = open(DEVICE_FILE, O_RDWR);
	if (fd < 0) {
		ALOGE("Can not open file %s\n", DEVICE_FILE);
		return -1;
	}

	ret = read(fd, &status, sizeof(status));
	if (ret < 0) {
		ALOGE("Can not read file %s\n", DEVICE_FILE);
		return ret;
	}
	ALOGE("jump to %s funtion\n", __func__);

	return status;
}

static int btn_close(struct hw_device_t *dev)
{
	struct vol_device_t *vol_dev = (struct vol_device_t *)dev;
	if (vol_dev)
		free(vol_dev);

	return 0;
}

static int btn_open(const struct hw_module_t *module, const char *name,
			struct hw_device_t **device)
{
	struct vol_device_t *vol_dev;

	vol_dev = malloc(sizeof(struct vol_device_t));
	if (!vol_dev)
		return -ENOMEM;

	vol_dev->common.tag = HARDWARE_DEVICE_TAG;
	vol_dev->common.version = 1;
	vol_dev->common.module = (struct hw_module_t *)module;
	vol_dev->common.close = btn_close;
	vol_dev->read_status = btn_stat_read;

	*device = (struct hw_device_t*)vol_dev;
	ALOGE("Device is initialized\n");

	return 0;
}
