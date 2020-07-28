#ifndef ANDROID_HARDWARE_HELLO_V1_0_HELLO_H
#define ANDROID_HARDWARE_HELLO_V1_0_HELLO_H

#include <android/hardware/hello/1.0/IHello.h>
#include <hidl/MQDescriptor.h>
#include <hidl/Status.h>

namespace android {
namespace hardware {
namespace hello {
namespace V1_0 {
namespace implementation {

using ::android::hardware::hidl_array;
using ::android::hardware::hidl_memory;
using ::android::hardware::hidl_string;
using ::android::hardware::hidl_vec;
using ::android::hardware::Return;
using ::android::hardware::Void;
using ::android::sp;

struct Hello : public IHello {
    // Methods from ::android::hardware::hello::V1_0::IHello follow.
    Return<void> String_hello(String_hello_cb _hidl_cb) override;
    Return<void> String_world(String_world_cb _hidl_cb) override;

    // Methods from ::android::hidl::base::V1_0::IBase follow.

};

// FIXME: most likely delete, this is only for passthrough implementations
// extern "C" IHello* HIDL_FETCH_IHello(const char* name);

}  // namespace implementation
}  // namespace V1_0
}  // namespace hello
}  // namespace hardware
}  // namespace android

#endif  // ANDROID_HARDWARE_HELLO_V1_0_HELLO_H
