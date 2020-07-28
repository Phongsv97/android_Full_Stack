
/*
 * Copyright (C) 2012 Opersys inc.
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
	private static final String TAG = "led";
	private Context mContext;
	private int mNativePointer;

	public LedService(Context context) 
	{
		super();
		mContext = context;
		Log.i(TAG, "Led service is started");
		//mNativePointer = init_native(name);
	}

	protected void finalize() throws Throwable 
	{
		final_native(mNativePointer);
		super.finalize();
	}

	public void init(String name)
	{
		byte[] buff = name.getBytes();
		mNativePointer = init_native(buff);
	}	

	public void config(int val)
	{
		config_native(mNativePointer, val);
	}
	
	private static native int init_native(byte[] name);
	private static native void final_native(int ptr);
	private static native void config_native(int prt, int val);
}
