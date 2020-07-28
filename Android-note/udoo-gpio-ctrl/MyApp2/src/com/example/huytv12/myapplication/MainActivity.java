package com.example.huytv12.myapplication;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.os.ServiceManager;
import android.os.LedManager;

public class MainActivity extends AppCompatActivity {
	private String name = "pin_out";
	private int val = 1;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        LedManager lman = (LedManager)getSystemService(GPIO_SERVICE);

        try
        {
		lman.init(name);
        }
        catch(Exception ex)
        {
            System.out.println("Kien: service start error!");
        }
    }

    public void buttonClick(View view) {
	lman.config(val);
        val != val;
    }
}
