LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE_RELATIVE_PATH := hw
LOCAL_PROPRIETARY_MODULE := true
LOCAL_MODULE := vendor.hardware.voltest@1.0-service
LOCAL_INIT_RC := vendor.hardware.voltest@1.0-service.rc
LOCAL_SRC_FILES := \
    service.cpp \
    Voltest.cpp

LOCAL_SHARED_LIBRARIES := \
    libcutils \
    libhidlbase \
    libhidltransport \
    liblog \
    libutils \
    libhardware \
    vendor.hardware.voltest@1.0 \
    libbbox_recv
    

LOCAL_C_INCLUDES := $(TARGET_OUT_INTERMEDIATES)/KERNEL_OBJ/usr/include \
                    $(TARGET_OUT_HEADERS)/common/inc \

include $(BUILD_EXECUTABLE)
