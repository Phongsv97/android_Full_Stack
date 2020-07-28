#define LOG_TAG "android.hardware.testvol@1.0-service"

#include <android/hardware/testvol/1.0/ITestvol.h>
#include <hidl/LegacySupport.h>

// Generated HIDL files
using android::hardware::testvol::V1_0::ITestvol;
using android::hardware::defaultPassthroughServiceImplementation;

int main() {
    return defaultPassthroughServiceImplementation<ITestvol>();
}

