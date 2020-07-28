/*
 * Copyright (C) 2019 VN RD Team
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

#define LOG_TAG "vendor.hardware.voltest@1.0-service"

#include <vendor/hardware/voltest/1.0/IVoltest.h>
#include <hidl/LegacySupport.h>
#include <hidl/HidlTransportSupport.h>

#include "Voltest.h"

using vendor::hardware::voltest::V1_0::IVoltest;
using vendor::hardware::voltest::V1_0::implementation::Voltest;
using android::hardware::defaultPassthroughServiceImplementation;
using android::hardware::joinRpcThreadpool;
using android::hardware::configureRpcThreadpool;
using android::sp;

int main() {
//      return defaultPassthroughServiceImplementation<IVoldown>();

        sp<IVoltest> service = new Voltest();
        configureRpcThreadpool(1, true);
        if(android::OK !=  service->registerAsService())
                return 1;

        joinRpcThreadpool();

        return 0;
}


