package com.example.quiz2_stambussi;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;

public class MainActivity extends AppCompatActivity implements HomeFragment.OnFragmentInteractionListener{

    public enum FragmentType {
        ADD, DELETE, SEARCH, UPDATE, VIEW_ALL;
    }
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        HomeFragment homeFragment = new HomeFragment();
        getSupportFragmentManager().beginTransaction().add(R.id.fragment_container, homeFragment).commit();
    }


    @Override
    public void replaceFragment(FragmentType type) {
        switch(type){
            case VIEW_ALL:
                getSupportFragmentManager().beginTransaction().replace(R.id.fragment_container, new ViewAllFragment()).addToBackStack(null).commit();
                break;
        }

    }
}