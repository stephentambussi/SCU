/* Stephen Tambussi - COEN 268 - Assignment 2 */
package com.example.assignment2;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.webkit.WebView;
import android.webkit.WebViewClient;

class MyWebViewClient extends WebViewClient
{
    /* This prevents the webview from opening an external browser app */
    @Override
    public boolean shouldOverrideUrlLoading(WebView view, String url)
    {
        view.loadUrl(url);
        return true;
    }
}

public class WebActivity extends AppCompatActivity {

    private String web_address;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        WebView myWebView = new WebView(this);
        setContentView(myWebView);

        web_address = getIntent().getStringExtra("ps_page"); //Gets the url for the wiki page
        myWebView.setWebViewClient(new MyWebViewClient());
        myWebView.loadUrl(web_address);
    }
}