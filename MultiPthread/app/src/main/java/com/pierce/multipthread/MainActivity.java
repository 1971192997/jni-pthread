package com.pierce.multipthread;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.

    private Button test;
    private PThread pThread;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        test = findViewById(R.id.button);
        pThread = new PThread();
        pThread.init();

        test.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                pThread.pthread();
            }
        });

    }

    @Override
    protected void onStop() {
        super.onStop();
        if (null == pThread) {

        } else {
            pThread.destroy();
        }
    }
}
