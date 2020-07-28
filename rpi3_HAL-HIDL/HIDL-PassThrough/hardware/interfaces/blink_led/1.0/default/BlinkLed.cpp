// FIXME: your file license if you have one

#include "BlinkLed.h"

namespace android {
namespace hardware {
namespace blinkled {
namespace V1_0 {
namespace implementation {

// Methods from ::android::hardware::blinkled::V1_0::IBlinkLed follow.
Return<int32_t> BlinkLed::readStatus() {
    // TODO implement
    return int32_t {};
}


// Methods from ::android::hidl::base::V1_0::IBase follow.

//IBlinkLed* HIDL_FETCH_IBlinkLed(const char* /* name */) {
    //return new BlinkLed();
//}
//
}  // namespace implementation
}  // namespace V1_0
}  // namespace blinkled
}  // namespace hardware
}  // namespace android
