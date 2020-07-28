/*
 * Copyright (C) 2008 The Android Open Source Project
 * Copyright (C) 2019 FIH Group.
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

#define LOG_TAG "VolbtnService"

#include <utils/misc.h>
#include <utils/Log.h>
#include <map>
#include <stdio.h>
#include <hardware/voldown.h>

int main()
{
	int err;
	struct vol_module_t *module;
	struct vol_device_t *dev = NULL;
	int status;

	printf("[Tung] debug 1\n");

	err = hw_get_module(VOL_HARDWARE_MODULE_ID, (struct hw_module_t const**)&module);
	if (err) {
		printf("hw_get_module() failed (%s)\n", strerror(-err));
	} else {
		printf("[Tung] debug 2\n");
		if (module->common.methods->open((struct hw_module_t *)module, "", ((hw_device_t **)&dev)) != 0) {
		printf("[Tung] debug 3n");
			return 0;
		}
	}

	status = dev->read_status(dev);
	printf("status of button is %d\n", status);

	return 0;
}
