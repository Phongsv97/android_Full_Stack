/*
 * Copyright (C) 2019 VN RD team.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#define LOG_TAG "TEST_BTN"

//#include <vendor/hardware/voltest/1.0/IVoltest.h>
#include <android/hardware/testvol/1.0/ITestvol.h>
#include <hidl/LegacySupport.h>
#include <hidl/HidlSupport.h>
#include <log/log.h>
#include <stdio.h>
#include <hidl/Status.h>

//using vendor::hardware::voltest::V1_0::IVoltest;
using android::hardware::testvol::V1_0::ITestvol;
using android::status_t;
using android::sp;

const char servicename[] = "android.hardware.testvol.ITestvol";

int main()
{
	int status;
	//status_t stat;

	printf("Starting test\n");
	sp<ITestvol> service = ITestvol::getService(servicename, true);
	if ( service == nullptr ) {
		printf("Can't find ITestvol service...");
		return -1;
	}

	/*stat = service->registerAsService(servicename);
	if (stat != ::android::OK) {
		ALOGE("Failed to register service %s.", servicename);
		exit(EXIT_FAILURE);
	}*/

	printf("Get service successfully\n");
	status = service->read_stat();
	printf("btn status is %d\n", status);

	return 0;
}
