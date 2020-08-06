package com.blink.blinkled;

import com.blink.blinkled.R;
import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class BlinkLed extends Activity {
    Button btnLedOn, btnLedOff;
    TextView txtHello;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        //anh xa
        txtHello = (TextView)findViewById(R.id.txtHello);
        btnLedOff = (Button)findViewById(R.id.buttonOff);
        btnLedOn = (Button)findViewById(R.id.buttonOn);

        //code
        btnLedOn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                txtHello.setText("PHONGLT button ON");
            }
        });

        btnLedOff.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                txtHello.setText("PHONGLT button OFF");
            }
        });
    }
}
