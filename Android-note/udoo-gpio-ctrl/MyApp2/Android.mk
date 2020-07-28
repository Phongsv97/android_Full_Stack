LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := optional

LOCAL_SRC_FILES := $(call all-java-files-under, src)
LOCAL_RESOURCE_DIR += $(LOCAL_PATH)/res

LOCAL_STATIC_ANDROID_LIBRARIES := \
  	android-support-v7-appcompat \
    android-support-compat \
    android-support-core-utils \
    android-support-core-ui \
    android-support-fragment \
    $(ANDROID_SUPPORT_DESIGN_TARGETS) \
    android-support-transition \
    android-support-v7-recyclerview

LOCAL_STATIC_JAVA_LIBRARIES := \
    android-common \
    com.android.vcard \
    guava \
    libphonenumber \
	android-support-annotations

LOCAL_USE_AAPT2 := true

LOCAL_PRIVATE_PLATFORM_APIS := true
LOCAL_PACKAGE_NAME := MyApp2

include $(BUILD_PACKAGE)
