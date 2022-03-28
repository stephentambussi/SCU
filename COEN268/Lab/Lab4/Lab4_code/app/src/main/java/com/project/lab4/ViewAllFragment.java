/*  Stephen Tambussi
    COEN 268 - Lab 4 - 3/2/2022
*/
package com.project.lab4;

import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.os.Bundle;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;


public class ViewAllFragment extends Fragment {

    private TextView tv_all_student;

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_view_all, container,false);

        tv_all_student = view.findViewById(R.id.tv_all_student_info);
        return view;
    }

    @Override
    public void onViewCreated(@NonNull View view, @Nullable Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);
        getAllStudentInfo();
    }

    private void getAllStudentInfo() {
        // Retrieve the student info saved from the database
        //instantiate database
        StudentDbHelper dbHelper = new StudentDbHelper(getActivity());
        //Get data repo in read mode
        SQLiteDatabase db = dbHelper.getReadableDatabase();
        //Query() method to get database values
        Cursor cursor = db.query(StudentInfoContract.Students.TABLE_NAME, null,
                null, null, null, null,
                StudentInfoContract.Students.STUDENT_ID);
        String result = "";
        while(cursor.moveToNext()) //while there is data in the database
        {
            String id = cursor.getString(cursor.getColumnIndex(StudentInfoContract.Students.STUDENT_ID));
            String name = cursor.getString(cursor.getColumnIndex(StudentInfoContract.Students.STUDENT_NAME));
            String email = cursor.getString(cursor.getColumnIndex(StudentInfoContract.Students.STUDENT_EMAIL));

            //append record to the result
            result = result + "\n\nID: " + id + "\nNAME: " + name + "\nEMAIL: " + email;
        }
        //close database connection
        db.close();
        if(result.length() == 0) result = "No records Found";
        tv_all_student.setText(result);
    }
}