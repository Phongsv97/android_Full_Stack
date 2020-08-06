/*
*
*/

#define LOG_TAG "LedService"

#include "jni.h"
#include "android_runtime/AndroidRuntime.h"
#include <android-base/chrono_utils.h>
#include <nativehelper/JNIHelp.h>
#include <utils/misc.h>
#include <utils/Log.h>
#include <stdio.h>
#include <hardware/led_hal.h>

namespace android {

static jlong init_native(JNIEnv *env, jobject clazz)
{
	int err;
	struct led_module_t *module;
	struct led_device_t *device = NULL;

	err =  hw_get_module(LED_HARDWARE_MODULE_ID, (struct hw_module_t const**)&module);
	if (err != 0) 
		ALOGE("PHONGLT %s, %d\n", __func__, __LINE__);
	else {
		if (module->common.methods->open((struct hw_module_t *)module, "", ((hw_device_t **)&device)) != 0) {
			ALOGE("PHONGLT %s, %d\n", __func__, __LINE__);
			return 0;
		}
	}

	return (jlong)device;
} 

static void final_native(JNIEnv *env, jobject clazz, long ptr)
{
	struct led_device_t *device = (struct led_device_t *)ptr;

	if(device == NULL){
		ALOGE("PHONGLT %s, %d\n", __func__, __LINE__);
		return;
	}

	device->common.close((struct hw_device_t *)device);
}

static void get_status_native(JNIEnv *env, jobject clazz, long  ptr, jbyteArray buff)
{
	int err;
	jbyte *byteArray;
	struct led_device_t *device = (struct led_device_t *)ptr;

	byteArray = env->GetByteArrayElements(buff, NULL);
	if(byteArray == NULL) {
		ALOGE("PHONGLT %s, %d\n", __func__, __LINE__);
		return;
	}
	
	err = device->get_status((char *)byteArray);
	if (err != 0) {
		ALOGE("PHONGLT %s, %d\n", __func__, __LINE__);
	}
	
	env->ReleaseByteArrayElements(buff, byteArray, 0);
}

static void config_native(JNIEnv *env, jobject clazz, long  ptr, jbyteArray buff)
{
	int err;
	jbyte *byteArray;
	struct led_device_t *device = (struct led_device_t *)ptr;

	byteArray = env->GetByteArrayElements(buff, NULL);
	if(byteArray == NULL) {
		ALOGE("PHONGLT %s, %d\n", __func__, __LINE__);
		return;
	}

	err = device->config_led((char *)byteArray);
	if (err != 0) {
		ALOGE("PHONGLT %s, %d\n", __func__, __LINE__);
		return;
	}

	env->ReleaseByteArrayElements(buff, byteArray, 0);
	
}

static JNINativeMethod method_table[] = {
	{ "init_native", "()J", (void *)init_native },
	{ "final_native", "(J)V", (void *)final_native },
	{ "get_status_native", "([J[B])V", (void *)get_status_native },
	{ "config_native", "([J[B)V", (void *)config_native}, 
};

int register_android_server_LedService(JNIEnv *env)
{
	return jniRegisterNativeMethods(env, "com/android/server/LedService",
					method_table, NELEM(method_table));

}

};