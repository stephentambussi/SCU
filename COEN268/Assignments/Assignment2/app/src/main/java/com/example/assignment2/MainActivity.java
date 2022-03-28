/* Stephen Tambussi - COEN 268 - Assignment 2 */
package com.example.assignment2;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.content.Intent;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {
    /* These strings contain the url for each wiki page */
    public final static String ps1_page = "https://en.wikipedia.org/wiki/PlayStation_(console)";
    public final static String ps2_page = "https://en.wikipedia.org/wiki/PlayStation_2";
    public final static String ps3_page = "https://en.wikipedia.org/wiki/PlayStation_3";
    public final static String ps4_page = "https://en.wikipedia.org/wiki/PlayStation_4";
    public final static String ps5_page = "https://en.wikipedia.org/wiki/PlayStation_5";
    public final static String psp_page = "https://en.wikipedia.org/wiki/PlayStation_Portable";
    public final static String psvita_page = "https://en.wikipedia.org/wiki/PlayStation_Vita";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    /* These methods below send the intent + url associated w/ the list item to the WebActivity */
    public void ps1(View view)
    {
        Toast.makeText(this, "Loading " + ps1_page, Toast.LENGTH_LONG).show();
        Intent intent = new Intent(this, WebActivity.class);
        intent.putExtra("ps_page", ps1_page);
        startActivity(intent);
    }

    public void ps2(View view)
    {
        Toast.makeText(this, "Loading " + ps2_page, Toast.LENGTH_LONG).show();
        Intent intent = new Intent(this, WebActivity.class);
        intent.putExtra("ps_page", ps2_page);
        startActivity(intent);
    }

    public void ps3(View view)
    {
        Toast.makeText(this, "Loading " + ps3_page, Toast.LENGTH_LONG).show();
        Intent intent = new Intent(this, WebActivity.class);
        intent.putExtra("ps_page", ps3_page);
        startActivity(intent);
    }

    public void ps4(View view)
    {
        Toast.makeText(this, "Loading " + ps4_page, Toast.LENGTH_LONG).show();
        Intent intent = new Intent(this, WebActivity.class);
        intent.putExtra("ps_page", ps4_page);
        startActivity(intent);
    }

    public void ps5(View view)
    {
        Toast.makeText(this, "Loading " + ps5_page, Toast.LENGTH_LONG).show();
        Intent intent = new Intent(this, WebActivity.class);
        intent.putExtra("ps_page", ps5_page);
        startActivity(intent);
    }

    public void psp(View view)
    {
        Toast.makeText(this, "Loading " + psp_page, Toast.LENGTH_LONG).show();
        Intent intent = new Intent(this, WebActivity.class);
        intent.putExtra("ps_page", psp_page);
        startActivity(intent);
    }

    public void psvita(View view)
    {
        Toast.makeText(this, "Loading " + psvita_page, Toast.LENGTH_LONG).show();
        Intent intent = new Intent(this, WebActivity.class);
        intent.putExtra("ps_page", psvita_page);
        startActivity(intent);
    }
}