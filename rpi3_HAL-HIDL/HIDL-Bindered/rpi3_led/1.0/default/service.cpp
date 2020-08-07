#include <android/hardware/rpi3_led/1.0/IBlinkLed.h>
#include <hidl/LegacySupport.h>
#include "BlinkLed.h"

using android::hardware::rpi3_led::V1_0::IBlinkLed;
using android::hardware::rpi3_led::V1_0::implementation::BlinkLed;
using android::hardware::configureRpcThreadpool;
using android::hardware::joinRpcThreadpool;
using android::sp;

int main() {
    int res;
    android::sp<IBlinkLed> ser = BlinkLed::getInstance();
    ALOGE("simp main");
    configureRpcThreadpool(1, true);

    if (ser != nullptr) {
        res = ser->registerAsService();
        if (res != 0)
            ALOGE("Can't register instance of SimpleBlinkLed, nullptr");
    } else {
        ALOGE("Can't create instance of SimpleBlinkLed, nullptr");
    }

    joinRpcThreadpool();

    return 0;
}