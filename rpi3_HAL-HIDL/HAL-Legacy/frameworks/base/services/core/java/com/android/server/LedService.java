/*
 * Copyright (C) 2008 The Android Open Source Project
 * Copyright 2019 VN R&D software team.
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

package com.android.server;

import android.content.Context;
import android.os.Handler;
import android.os.ILedService;
import android.os.Looper;
import android.os.Message;
import android.os.Process;
import android.util.Log;

public class LedService extends ILedService.Stub {
	private static final String TAG = "PHONGLT Led HAL";
	private Context mContext;
	private long mNativePointer;

	public LedService(Context context)
	{
		super();
		mContext = context;
		Log.i(TAG, "LedService is started");
		mNativePointer = init_native();
	}

	protected void finalize() throws Throwable
	{
		final_native(mNativePointer);
		super.finalize();
	}

	public int config_led(String mString)
	{
		byte[] byteArray = mString.getBytes();

		Log.i(TAG, "config_led");
		config_native(mNativePointer, byteArray);

		return 0;
	}

	// public String get_status()
	// {
	// 	byte[] byteArray = new byte[6];

	// 	Log.e(TAG, "get_status failed");

	// 	get_status_native(mNativePointer, byteArray);
		
	// 	return new String(byteArray);
	// }

	private static native long init_native();
	private static native void final_native(long ptr);
	private static native void get_status_native(long ptr);
	private static native void config_native(long ptr, byte[] byteArray);
}
