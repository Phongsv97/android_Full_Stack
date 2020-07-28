#define LOG_TAG "android.hardware.hello@1.0-service"

#include <android/hardware/hello/1.0/IHello.h>
#include <hidl/LegacySupport.h>
#include <hidl/HidlTransportSupport.h>

#include "Hello.h"

using android::hardware::hello::V1_0::IHello;
using android::hardware::hello::V1_0::implementation::Hello;
using android::hardware::defaultPassthroughServiceImplementation;
using android::hardware::joinRpcThreadpool;
using android::hardware::configureRpcThreadpool;
using android::sp;

int main()
{
	sp<IHello> service = new Hello();
	configureRpcThreadpool(1, true);
	if(android::OK !=  service->registerAsService())
		return 1;

	joinRpcThreadpool();

	return 0;
}
