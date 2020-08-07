#ifndef ANDROID_HARDWARE_RPI3_LED_V1_0_BLINKLED_H
#define ANDROID_HARDWARE_RPI3_LED_V1_0_BLINKLED_H

#include <android/hardware/rpi3_led/1.0/IBlinkLed.h>
#include <hidl/MQDescriptor.h>
#include <hidl/Status.h>

namespace android {
namespace hardware {
namespace rpi3_led {
namespace V1_0 {
namespace implementation {

using ::android::hardware::hidl_array;
using ::android::hardware::hidl_memory;
using ::android::hardware::hidl_string;
using ::android::hardware::hidl_vec;
using ::android::hardware::Return;
using ::android::hardware::Void;
using ::android::sp;

struct BlinkLed : public IBlinkLed {
    // Methods from IBlinkLed follow.
    Return<int32_t> simpfn(int32_t valueIn) override;

    // Methods from ::android::hidl::base::V1_0::IBase follow.
    static IBlinkLed* getInstance(void);

};

// FIXME: most likely delete, this is only for passthrough implementations
// extern "C" IBlinkLed* HIDL_FETCH_IBlinkLed(const char* name);

}  // namespace implementation
}  // namespace V1_0
}  // namespace rpi3_led
}  // namespace hardware
}  // namespace android

#endif  // ANDROID_HARDWARE_RPI3_LED_V1_0_BLINKLED_H
