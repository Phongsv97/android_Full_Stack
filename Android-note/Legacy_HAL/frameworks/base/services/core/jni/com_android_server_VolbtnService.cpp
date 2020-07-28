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

#define LOG_TAG "VolbtnService"

#include "jni.h"
#include "android_runtime/AndroidRuntime.h"
#include <android-base/chrono_utils.h>
#include <nativehelper/JNIHelp.h>
#include <utils/misc.h>
#include <utils/Log.h>
#include <map>
#include <stdio.h>
#include <hardware/voldown.h>

namespace android {

static jlong init_native(JNIEnv *env, jobject clazz)
{
	int err;
	struct vol_module_t *module;
	struct vol_device_t *dev = NULL;

	err = hw_get_module(VOL_HARDWARE_MODULE_ID, (struct hw_module_t const**)&module);
	if (err) {
		printf("hw_get_module() failed (%s)\n", strerror(-err));
	} else {
		if (module->common.methods->open((struct hw_module_t *)module, "", ((hw_device_t **)&dev)) != 0)
			return 0;
	}

	return (jlong)dev;
}

static int read_native(JNIEnv *env, jobject clazz, long ptr)
{
	int status;

	struct vol_device_t *dev = (struct vol_device_t *)ptr;
	status = dev->read_status(dev);

	return status;
}

static void final_native(JNIEnv *env, jobject clazz, long ptr)
{
	struct vol_device_t *dev = (struct vol_device_t *)ptr;

	dev->common.close((struct hw_device_t *)dev);
}

static JNINativeMethod method_table[] = {
	{ "init_native", "()J", (void *)init_native },
	{ "read_native", "(J)I", (void *)read_native },
	{ "final_native", "(J)V", (void *)final_native },
};

int register_android_server_VolbtnService(JNIEnv *env)
{
	return jniRegisterNativeMethods(env, "com/android/server/VolbtnService",
					method_table, NELEM(method_table));

}

};

