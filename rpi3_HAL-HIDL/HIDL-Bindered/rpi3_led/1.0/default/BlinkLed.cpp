#include "BlinkLed.h"

namespace android {
namespace hardware {
namespace rpi3_led {
namespace V1_0 {
namespace implementation {

// Methods from IBlinkLed follow.
Return<int32_t> BlinkLed::simpfn(int32_t valueIn) {
    // TODO implement
    return valueIn + 100;
}

IBlinkLed *BlinkLed::getInstance(void) {
    return new BlinkLed();
}

// Methods from ::android::hidl::base::V1_0::IBase follow.

//IBlinkLed* HIDL_FETCH_IBlinkLed(const char* /* name */) {
//    return new BlinkLed();
//}

}  // namespace implementation
}  // namespace V1_0
}  // namespace rpi3_led
}  // namespace hardware
}  // namespace android
