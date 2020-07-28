#include <android/hardware/hello/1.0/IHello.h>
#include <hidl/LegacySupport.h>
#include <hidl/HidlSupport.h>
#include <log/log.h>
#include <stdio.h>
#include <hidl/Status.h>

using android::hardware::hello::V1_0::IHello;
using android::status_t;
using android::sp;
using android::hardware::hidl_string;

const char servicename[] = "android.hardware.hello.IHello";

int main()
{
	sp<IHello> service = IHello::getService(servicename, true);
	if ( service == nullptr ) {
		printf("Can't find IHello service...");
		return -1;
	}

	printf("Get service successfully\n");
	service->String_hello([&](hidl_string hello) {
		printf("Get string from hidl %s\n", hello.c_str());
	});

	service->String_world([&](hidl_string world) {
		printf("Get string form hidl %s\n", world.c_str());
	});

	return 0;
}
