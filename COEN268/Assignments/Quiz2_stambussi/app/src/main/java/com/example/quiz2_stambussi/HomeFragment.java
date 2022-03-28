package com.example.quiz2_stambussi;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.os.Bundle;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;


public class HomeFragment extends Fragment implements View.OnClickListener{

    OnFragmentInteractionListener listener;
    private EditText mobile_num, model;

    public HomeFragment() {
        // empty public constructor required
    }

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_home, container, false);
        Button btn_add, btn_delete, btn_view_all, btn_search, btn_update;
        btn_add = view.findViewById(R.id.btn_add);
        btn_view_all = view.findViewById(R.id.btn_seeAll);
        mobile_num = view.findViewById(R.id.mobile_num);
        model = view.findViewById(R.id.model);
        btn_add.setOnClickListener(this);
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
                //listener.replaceFragment(MainActivity.FragmentType.ADD);
                saveMobileInfoIntoDatabase();
                break;
            case R.id.btn_seeAll:
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

    private void saveMobileInfoIntoDatabase() {
        String mobileNum = mobile_num.getText().toString();
        String model_name = model.getText().toString();

        if (mobileNum.isEmpty() || model_name.isEmpty()) {
            Toast.makeText(getActivity(), "Number and Model cannot be empty", Toast.LENGTH_SHORT).show();
            return;
        }
        if(searchMobile() == 1)//check for duplicates in database
        {
            Toast.makeText(getActivity(), "Duplicate Found!", Toast.LENGTH_SHORT).show();
            return;
        }
        // Add the record to the database
        //instantiate database
        MobileDbHelper dbHelper = new MobileDbHelper(getActivity());
        //Get data repo in write mode
        SQLiteDatabase db = dbHelper.getWritableDatabase();
        //Create content values object
        ContentValues contentValues = new ContentValues();
        //put(column names of table, user data values) method
        contentValues.put(MobileInfoContract.Mobile.MOBILE_NUM, mobileNum);
        contentValues.put(MobileInfoContract.Mobile.MODEL_NAME, model_name);
        //insert new row
        long recordId = db.insert(MobileInfoContract.Mobile.TABLE_NAME,
                null, contentValues);
        //close database connection
        db.close();
        //Check insertion is successful
        if(recordId == -1)
        {
            Toast.makeText(getActivity(), "Insertion Failed", Toast.LENGTH_SHORT).show();
        }
        else
        {
            Toast.makeText(getActivity(), "Successfully added phone " + mobileNum + " in the db", Toast.LENGTH_SHORT).show();
        }
        //clear EditText fields
        mobile_num.setText("");
        model.setText("");
    }

    private int searchMobile() {
        String mobileNum = mobile_num.getText().toString();
        String model_name = model.getText().toString();

        // Search the student in the database
        //instantiate database
        MobileDbHelper dbHelper = new MobileDbHelper(getActivity());
        //Get data repo in read mode
        SQLiteDatabase db = dbHelper.getReadableDatabase();

        //Query() method
        String[] columns = {
                MobileInfoContract.Mobile.MOBILE_NUM,
                MobileInfoContract.Mobile.MODEL_NAME
        };
        String selection = MobileInfoContract.Mobile.MOBILE_NUM + " LIKE? ";
        String[] selectionArgs = {"%" + mobileNum + "%"};

        Cursor cursor =
                db.query(MobileInfoContract.Mobile.TABLE_NAME, columns, selection,
                        selectionArgs, null, null, MobileInfoContract.Mobile.MOBILE_NUM);
        String result = "";
        while(cursor.moveToNext()) //while there is data in the database
        {
            String id = cursor.getString(cursor.getColumnIndex(MobileInfoContract.Mobile.MOBILE_NUM));
            String std_name = cursor.getString(cursor.getColumnIndex(MobileInfoContract.Mobile.MODEL_NAME));

            //append record to the result
            result = result + "\n\nID: " + id + "\nNAME: " + std_name;
        }
        //close database connection
        db.close();
        if(result.length() == 0) return 0;
        else return 1; //duplicate found
    }
}