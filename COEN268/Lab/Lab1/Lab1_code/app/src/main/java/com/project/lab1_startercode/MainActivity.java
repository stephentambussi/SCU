/*  Stephen Tambussi
    COEN 268 - Lab 1 - 1/26/2022
*/
package com.project.lab1_startercode;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.widget.EditText;
import android.widget.Toast;
import android.view.View;
import android.content.Intent;

public class MainActivity extends AppCompatActivity {

    public final static String TAG = "MainActivity";
    public final static String USERNAME = "testUser";
    public final static String PASSWORD = "123456";

    EditText username;
    EditText password;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Log.i(TAG, "On Create");

        // set the UI layout for this activity
        setContentView(R.layout.activity_main);

        // initialize UI elements
        username = findViewById(R.id.et_username); //R is resource
        password = findViewById(R.id.et_password);
    }

    @Override
    protected void onStart()
    {
        super.onStart();
        Log.i(TAG, "On Start");
    }

    @Override
    protected void onResume()
    {
        super.onResume();
        Log.i(TAG, "On Resume");
    }

    @Override
    protected void onPause()
    {
        super.onPause();
        Log.i(TAG, "On Pause");
    }

    @Override
    protected void onStop() {
        super.onStop();
        Log.i(TAG, "On Stop");
    }

    @Override
    protected void onRestart() {
        super.onRestart();
        Log.i(TAG, "On Restart");
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        Log.i(TAG, "On Destroy");
    }

    public void login(View view)
    {
        //Implementation
        if(!(username.getText().toString().equals(USERNAME)) || !(password.getText().toString().equals(PASSWORD)))
        {
            Toast.makeText(this, "Incorrect Name or Password", Toast.LENGTH_LONG).show(); //try LENGTH_SHORT
            return;
        }
        Intent intent = new Intent(this, SecondActivity.class);
        intent.putExtra("name", USERNAME);
        startActivity(intent);
    }
}