#include "Testvol.h"

#include <log/log.h>
#include <hardware/hardware.h>
#include <hardware/testvol.h>

namespace android {
namespace hardware {
namespace testvol {
namespace V1_0 {
namespace implementation {

Testvol::Testvol(volume_module_t *device) : mDevice(device) {}

// Methods from ::android::hardware::testvol::V1_0::ITestvol follow.
Return<int32_t> Testvol::read_stat() {
    int32_t status;

    status = mDevice->read_status(mDevice);

    return status;
}


// Methods from ::android::hidl::base::V1_0::IBase follow.

ITestvol* HIDL_FETCH_ITestvol(const char* /* name */) {
    volume_module_t *module;

    int ret = hw_get_module(VOL_HARDWARE_ID, 
                           const_cast<hw_module_t const**>(
                               reinterpret_cast<hw_module_t**>(&module)));
    if (ret == 0) {
        return new Testvol(module);
    } else {
        ALOGE("hw_get_module %s failed: %d", VOL_HARDWARE_ID, ret);
        return nullptr;
    }
}
//
}  // namespace implementation
}  // namespace V1_0
}  // namespace testvol
}  // namespace hardware
}  // namespace android
