#include "Hello.h"
#include <string.h>

namespace android {
namespace hardware {
namespace hello {
namespace V1_0 {
namespace implementation {

// Methods from ::android::hardware::hello::V1_0::IHello follow.
Return<void> Hello::String_hello(String_hello_cb _hidl_cb) {
    // TODO implement
    char str[6];

    memset(str, 0, 6);
    sprintf(str, "hello");

    //strcpy(str, "hello");
    _hidl_cb(str);
    return Void();
}

Return<void> Hello::String_world(String_world_cb _hidl_cb) {
    // TODO implement
    char str[6] = "world";

    //strcpy(str, "world");
    _hidl_cb(str);
    return Void();
}


// Methods from ::android::hidl::base::V1_0::IBase follow.

//IHello* HIDL_FETCH_IHello(const char* /* name */) {   binder don't need this function
    //return new Hello();
//}
//
}  // namespace implementation
}  // namespace V1_0
}  // namespace hello
}  // namespace hardware
}  // namespace android
