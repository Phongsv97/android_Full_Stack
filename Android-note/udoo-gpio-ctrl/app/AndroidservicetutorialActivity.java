package com.android.server.Led;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.app.NotificationManager;
import android.os.LedManager;
import android.content.ServiceConnection;
import android.os.IBinder;
import android.content.ComponentName;

public class AndroidservicetutorialActivity extends Activity {
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		LedManager lman = (LedManager)getSystemService(GPIO_SERVICE);
		lman.init("pin_out");
		lman.config(1);
	}
}
