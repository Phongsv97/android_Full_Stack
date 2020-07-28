// FIXME: your file license if you have one

#pragma once

#include <android/hardware/blinkled/1.0/IBlinkLed.h>
#include <hidl/MQDescriptor.h>
#include <hidl/Status.h>

namespace android {
namespace hardware {
namespace blinkled {
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
    // Methods from ::android::hardware::blinkled::V1_0::IBlinkLed follow.
    Return<int32_t> readStatus() override;

    // Methods from ::android::hidl::base::V1_0::IBase follow.

};

// FIXME: most likely delete, this is only for passthrough implementations
// extern "C" IBlinkLed* HIDL_FETCH_IBlinkLed(const char* name);

}  // namespace implementation
}  // namespace V1_0
}  // namespace blinkled
}  // namespace hardware
}  // namespace android
