package com.project.lab4;

import android.content.Context;
import android.os.Bundle;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;


public class HomeFragment extends Fragment implements View.OnClickListener{

    OnFragmentInteractionListener listener;

    public HomeFragment() {
        // empty public constructor required
    }

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_home, container, false);
        Button btn_add, btn_delete, btn_view_all, btn_search, btn_update;
        btn_add = view.findViewById(R.id.btn_add);
        btn_delete = view.findViewById(R.id.btn_delete);
        btn_search = view.findViewById(R.id.btn_search);
        btn_update = view.findViewById(R.id.btn_update);
        btn_view_all = view.findViewById(R.id.btn_viewAll);
        btn_add.setOnClickListener(this);
        btn_delete.setOnClickListener(this);
        btn_search.setOnClickListener(this);
        btn_update.setOnClickListener(this);
        btn_view_all.setOnClickListener(this);
        return view;
    }

    public interface OnFragmentInteractionListener{
        void replaceFragment(MainActivity.FragmentType type);
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.btn_add:
                listener.replaceFragment(MainActivity.FragmentType.ADD);
                break;
            case R.id.btn_search:
                listener.replaceFragment(MainActivity.FragmentType.SEARCH);
                break;
            case R.id.btn_delete:
                listener.replaceFragment(MainActivity.FragmentType.DELETE);
                break;
            case R.id.btn_update:
                listener.replaceFragment(MainActivity.FragmentType.UPDATE);
                break;
            case R.id.btn_viewAll:
                listener.replaceFragment(MainActivity.FragmentType.VIEW_ALL);
                break;
        }
    }

    @Override
    public void onAttach(Context context) {
        super.onAttach(context);
        if (context instanceof OnFragmentInteractionListener) {
            listener = (OnFragmentInteractionListener) context;
        } else {
            throw new RuntimeException(context.toString()
                    + " must implement OnFragmentInteractionListener");
        }
    }
}