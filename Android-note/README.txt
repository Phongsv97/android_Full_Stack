*****Driver****
	- location: kernel/msm-4.9/drivers/<vendor>
		add new file: <vendor>_btn_test.c
		modify <vendor<vendor>akefile:
				obj-y += <vendor>_btn_test.o

*****HAL*****

        -       location: android_build/hardware/libhardware/include/hardware/
                        add new file: voldown.h
        -       location: hardware/libhardware/modules/voldown
                        folder "voldown" contain: voldown.c, Android.bp
                        build:
                                -       location : device/<vendor>_qcom/<vendor>_sdm429_64/device.mk

                                        PRODUCT_PACKAGES += voldown.default
					PRODUCT_PACKAGES += voldown_tests
        -       modify Android.mk in hardware/libhardware/module
				hardware_modules := \
						    camera \
 						    gralloc \
    						    voldown 
                                               
Note: Defined module ID in header file should be same as the name of the file
Ex: file name: voldown.c
Should be defined: #define VOL_HARDWARE_MODULE_ID          "voldown"

*****JNI*****

location: android_build/frameworks/base/services/core/jni/
add new file: com_android_server_VolbtnService.cpp
add line in onload.cpp:
        - int register_android_server_VolbtnService(JNIEnv *env);
        - register_android_server_VolbtnService(env);
add line in Android.bp
	"com_android_server_VolbtnService.cpp",
 
 *****Framework*****

- Add new file: VolbtnManager.java
	location:frameworks\base\core\java\android\os\VolbtnManager.java
- Add line in Context.java
	location: frameworks\base\core\java\android\content\Context.java
- Add new file: IVolbtnService.aidl
	location: frameworks\base\core\java\android\os\IVolbtnService.aidl
- Add line in Android.bp
	location:frameworks/base/Android.bp
- Add new file: VolbtnService.java
	location: frameworks\base\services\core\java\com\android\server\VolbtnService.java
- Add line in SystemServer.java
	location: frameworks\base\services\java\com\android\server\SystemServer.java
- Add line in SystemServiceRegistry.java
	location: frameworks\base\core\java\android\app\SystemServiceRegistry.java




Some other note:
# PACKAGE=android.hardware.naruto@1.0
# LOC=
# make hidl-gen -j64
# hidl-gen -o $LOC -Lc++-impl -randroid.hardware:hardware/interfaces -randroid.hidl:system/libhidl/transport $PACKAGE
# hidl-gen -o $LOC -Landroidbp-impl -randroid.hardware:hardware/interfaces -randroid.hidl:system/libhidl/transport $PACKAGE

./hardware/interfaces/update-makefiles.sh

sua file:
fih_qcom/fih_sdm429_64/sepolicy/hwservice_contexts
fih_qcom/fih_sdm429_64/sepolicy/hwservice.te
fih_qcom/fih_sdm429_64/sepolicy/attributes
Them file
fih_qcom/fih_sdm429_64/sepolicy/hal_voltest.te

sua file:
device/fih_qcom/fih_sdm429_64/device.mk
PRODUCT_PACKAGES += vendor.hardware.voltest@1.0-service

device/qcom/msm8937_64/manifest.xml
    <!-- Voltest HAL service -->
    <hal format="hidl">
        <name>vendor.hardware.voltest</name>
        <transport>hwbinder</transport>
        <version>1.0</version>
        <interface>
            <name>IVoltest</name>
            <instance>default</instance>
        </interface>
    </hal>

device/qcom/common/vendor_framework_compatibility_matrix.xml:
    <!-- Voltest HAL Service -->
    <hal format="hidl" optional="true">
        <name>vendor.hardware.voltest</name>
        <version>1.0</version>
        <interface>
            <name>IVoltest</name>
            <instance>default</instance>
        </interface>
    </hal>

add  in file /fih_qcom/fih_sdm429_64/sepolicy/file_contexts
#For Voltest
/(vendor|system/vendor)/bin/hw/vendor\.hardware\.box@1\.0-service      u:object_r:hal_voltest_default_exec:s0

Generate java:
hidl-gen -o ./tmp -Ljava -rvendor.hardware:vendor/FIH/interfaces -randroid.hidl:system/libhidl/transport vendor.hardware.voltest@1.0

add in file: device/fih_qcom/fih_sdm429_64/device.mk to build .jar file
PRODUCT_PACKAGES += vendor.hardware.voltest-V1.0-java
