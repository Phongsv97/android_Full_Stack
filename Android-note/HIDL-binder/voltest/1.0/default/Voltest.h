#ifndef VENDOR_HARDWARE_VOLTEST_V1_0_VOLTEST_H
#define VENDOR_HARDWARE_VOLTEST_V1_0_VOLTEST_H

#include <vendor/hardware/voltest/1.0/IVoltest.h>
#include <hidl/MQDescriptor.h>
#include <hidl/Status.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

namespace vendor {
namespace hardware {
namespace voltest {
namespace V1_0 {
namespace implementation {

using ::android::hardware::hidl_array;
using ::android::hardware::hidl_memory;
using ::android::hardware::hidl_string;
using ::android::hardware::hidl_vec;
using ::android::hardware::Return;
using ::android::hardware::Void;
using ::android::sp;

struct Voltest : public IVoltest {
	// Methods from ::android::hardware::voldown::V1_0::IVoldown follow.
	Return<int32_t> readstatus() override;

	// Methods from ::android::hidl::base::V1_0::IBase follow.

};

}
}
}
}
}
#endif
