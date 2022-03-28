/*  Stephen Tambussi
    COEN 268 - Lab 3 - 2/16/2022
*/
package com.project.lab3;

import androidx.appcompat.app.AppCompatActivity;

import android.content.ComponentName;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.Bundle;
import android.os.IBinder;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity implements View.OnClickListener{
    private static final String TAG = "MainActivity";
    private ServiceConnection myConnection;
    boolean isBound;

    Button buttonStart, buttonStop;
    Button buttonBind, buttonUnBind;
    Button buttonGetRandomNumber;
    TextView tvRandomNumber;
    Intent sIntent;
    MyService myService;
    
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        //set layout
        setContentView(R.layout.activity_main);

        //initialize UI elements
        buttonStart = findViewById(R.id.btn_start);
        buttonStop = findViewById(R.id.btn_stop);
        buttonBind = findViewById(R.id.btn_bind);
        buttonUnBind = findViewById(R.id.btn_unbind);
        buttonGetRandomNumber = findViewById(R.id.btn_getNumber);
        tvRandomNumber = findViewById(R.id.tv_random_number);

        //set on click listener
        buttonStart.setOnClickListener(this);
        buttonStop.setOnClickListener(this);
        buttonBind.setOnClickListener(this);
        buttonUnBind.setOnClickListener(this);
        buttonGetRandomNumber.setOnClickListener(this);

        sIntent = new Intent(this, MyService.class); //initialize sIntent
    }

    @Override
    public void onClick(View view) {
        switch (view.getId()) {
            case R.id.btn_start:
                //1: START A SERVICE
                startMyService();
                break;
            case R.id.btn_stop:
                //2: STOP A SERVICE
                stopMyService();
                break;
            case R.id.btn_bind:
                //3: BIND A SERVICE
                bindMyService();
                break;
            case R.id.btn_unbind:
                //4: UNBIND A SERVICE
                unbindMyService();
                break;
            case R.id.btn_getNumber:
                //5: GET AND RANDOM NUMBER FROM SERVICE AND DISPLAY IT
                getNumber();
                break;
        }
    }

    private void getNumber()
    {
        if(isBound)
        {
            //sets the layout text view to the random number
            tvRandomNumber.setText("Random Number: " + myService.getRandomNumber());
        }
    }

    private void unbindMyService()
    {
        if(isBound)
        {
            Log.i(TAG, "Unbinding Service");
            unbindService(myConnection);
            myConnection = null;
            isBound = false;
        }
    }

    private void bindMyService()
    {
        if(myConnection == null)
        {
            Log.i(TAG, "Binding Service");
            myConnection = new ServiceConnection() {
                @Override
                public void onServiceConnected(ComponentName name, IBinder ibinder) {
                    Log.i(TAG, "On Service Connected");
                    MyService.MyLocalBinder myBinder = (MyService.MyLocalBinder) ibinder;
                    myService = myBinder.getService();
                    isBound = true;
                }

                @Override
                public void onServiceDisconnected(ComponentName name) {
                    Log.i(TAG, "On Service Disconnected");
                    isBound = false;
                }
            };
        }
        bindService(sIntent, myConnection, BIND_AUTO_CREATE); //BIND_AUTO_CREATE creates if it does not exist
    }

    public void startMyService()
    {
        Log.i(TAG, "Starting Service");
        Log.i(TAG, "Thread id: " + Thread.currentThread().getId());
        startService(sIntent);
    }

    public void stopMyService()
    {
        Log.i(TAG, "Stopping Service");
        stopService(sIntent);
    }
}