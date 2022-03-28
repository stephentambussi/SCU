/*  Stephen Tambussi
    COEN 268 - Lab 3 - 2/16/2022
*/
package com.project.lab3;

import android.app.Service;
import android.content.Intent;
import android.os.Binder;
import android.os.IBinder;
import android.util.Log;

import java.util.Random;

public class MyService extends Service {
    private static final String TAG = "MyService";
    private boolean isRandOn;
    int rNum;

    public MyService() {
    }

    class MyLocalBinder extends Binder {
        public MyService getService()
        {
            return MyService.this;
        }
    }

    private Binder myBinder = new MyLocalBinder();

    @Override
    public IBinder onBind(Intent intent) {
        // TODO: Return the communication channel to the service.
        Log.i(TAG, "On Bind");
        return myBinder;
    }

    private void generateRandomNumber()
    {
        while(isRandOn)
        {
            try
            {
                Thread.sleep(1000); //sleep for 1 second
                rNum = new Random().nextInt(100); //random num < 100
                Log.i(TAG, "Thread id " + Thread.currentThread().getId() + " Random Number: " + rNum);
            } catch (Exception e) {
                Log.e(TAG, e.getMessage());
            }
        }
    }

    public int getRandomNumber()
    {
        return rNum;
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId)
    {
        Log.i(TAG, "onStartCommand");
        Log.i(TAG, "Thread id: " + Thread.currentThread().getId() + " Start id: " + startId);
        if(!isRandOn)
        {
            Runnable runnable = () -> {
                Log.i(TAG, "Inside Run");
                isRandOn = true;
                generateRandomNumber();
            };
            Thread t = new Thread(runnable); //creates new thread that executes runnable
            t.start(); //starts thread
        }
        return START_NOT_STICKY; //if system shutdowns or program killed, do not restart service
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
        Log.i(TAG, "On Destroy");
        isRandOn = false;
    }

    @Override
    public boolean onUnbind(Intent intent)
    {
        Log.i(TAG, "On Unbind");
        return super.onUnbind(intent);
    }
}
