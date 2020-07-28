/*
 * Copyright (C) 2012 Opersys inc.
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

#define LOG_TAG "GpioService"

#include <inttypes.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/cdefs.h>
#include <sys/types.h>

#include <utils/misc.h>
#include <utils/Log.h>
#include <map>
#include <hardware/gpio_hal.h>

int main(int argc, char *argv[])
{
        int err;
        hw_module_t *module;
        led_device_t *dev = NULL;

	if (argc == 3) {
        	err = hw_get_module(LED_HARDWARE_MODULE_ID, (hw_module_t const **)&module);
        	if (err == 0) {
                	if (module->methods->open(module, argv[1], ((hw_device_t **)&dev)) != 0)
                        	return 0;
		}

	} else 
		printf("need parameter: %s <1> <2>\n", __FILE__);

	dev->config_led(dev, argv[2]);

        return 0;
}
