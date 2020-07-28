#ifndef ANDROID_HARDWARE_TESTVOL_V1_0_TESTVOL_H
#define ANDROID_HARDWARE_TESTVOL_V1_0_TESTVOL_H

#include <android/hardware/testvol/1.0/ITestvol.h>
#include <hidl/MQDescriptor.h>
#include <hidl/Status.h>
#include <hardware/testvol.h>

namespace android {
namespace hardware {
namespace testvol {
namespace V1_0 {
namespace implementation {

using ::android::hardware::hidl_array;
using ::android::hardware::hidl_memory;
using ::android::hardware::hidl_string;
using ::android::hardware::hidl_vec;
using ::android::hardware::Return;
using ::android::hardware::Void;
using ::android::sp;

struct Testvol : public ITestvol {
    Testvol(volume_module_t *device);
    // Methods from ::android::hardware::testvol::V1_0::ITestvol follow.
    Return<int32_t> read_stat() override;

    // Methods from ::android::hidl::base::V1_0::IBase follow.
    private:
        volume_module_t *mDevice;
};

// FIXME: most likely delete, this is only for passthrough implementations
extern "C" ITestvol* HIDL_FETCH_ITestvol(const char* name);

}  // namespace implementation
}  // namespace V1_0
}  // namespace testvol
}  // namespace hardware
}  // namespace android

#endif  // ANDROID_HARDWARE_TESTVOL_V1_0_TESTVOL_H
