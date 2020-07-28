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

#define LOG_TAG "LedService"

#include "jni.h"
#include "android_runtime/AndroidRuntime.h"
#include <android-base/chrono_utils.h>
#include "JNIHelp.h"
#include <utils/misc.h>
#include <utils/Log.h>
#include <map>
#include <stdio.h>
#include <hardware/gpio_hal.h>

namespace android {

static jint init_native(JNIEnv *env, jobject clazz, jbyteArray name)
{
	int err;
	struct led_module_t *module;
	struct led_device_t *dev = NULL;
	jbyte* real_byte_array;
	real_byte_array = env->GetByteArrayElements(name, NULL);

	err = hw_get_module(LED_HARDWARE_MODULE_ID, (hw_module_t const **)&module);
	if (err == 0) {
		if (module->common.methods->open((struct hw_module_t *)module, (char*)real_byte_array, ((hw_device_t **)&dev)) != 0)
			return 0;
	}
	env->ReleaseByteArrayElements(name, byte_array, 0);

	return (jint)dev;
}

static void config_native(JNIEnv *env, jobject clazz, int ptr, int val)
{
	led_device_t *dev = (led_device_t *)ptr;
	
	dev->config_led(dev, val);
	
}

static void final_native(JNIEnv *env, jobject clazz, int ptr)
{
	led_device_t *dev = (led_device_t *)ptr;

	dev->common.close((struct hw_device_t *)dev);
}

static JNINativeMethod method_table[] = {
	{ "init_native", "([B)I", (void *)init_native },
	{ "config_native", "(II)V", (void *)config_native },
	{ "final_native", "(I)V", (void *)final_native },
};

int register_android_server_GpioService(JNIEnv *env)
{
	return jniRegisterNativeMethods(env, "com/android/server/LedService",
					method_table, NELEM(method_table));
}

}
