package com.example.quiz1_stambussi;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.Toast;
import android.view.View;
import android.widget.EditText;

public class MainActivity extends AppCompatActivity {

    EditText name;
    EditText password;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main); //associates the layout resource file with this activity
        name = findViewById(R.id.edit_name); //R is resource
        password = findViewById(R.id.edit_pwd);
    }

    public void submit(View view)
    {
        if((name.getText().toString().equals("")) || (password.getText().toString().equals("")))
        {
            Toast.makeText(this, "Enter Name or Password", Toast.LENGTH_SHORT).show(); //try LENGTH_SHORT
            return;
        }
    }
}