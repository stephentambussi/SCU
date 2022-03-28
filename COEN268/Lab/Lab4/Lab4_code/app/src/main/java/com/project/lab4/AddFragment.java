/*  Stephen Tambussi
    COEN 268 - Lab 4 - 3/2/2022
*/
package com.project.lab4;

import android.content.ContentValues;
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


public class AddFragment extends Fragment {

    private Button btn_save;
    private EditText et_name, et_email, et_std_id;

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_add, container, false);
        btn_save = view.findViewById(R.id.btn_save);
        et_email = view.findViewById(R.id.et_email);
        et_name = view.findViewById(R.id.et_name);
        et_std_id = view.findViewById(R.id.et_std_id);
        btn_save.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                saveStudentInfoIntoDatabase();
            }
        });
        return view;
    }

    private void saveStudentInfoIntoDatabase() {
        String id = et_std_id.getText().toString();
        String name = et_name.getText().toString();
        String email = et_email.getText().toString();

        if (id.isEmpty() || name.isEmpty()) {
            Toast.makeText(getActivity(), "Name and ID cannot be empty", Toast.LENGTH_SHORT).show();
            return;
        }
        // Add the record to the database
        //instantiate database
        StudentDbHelper dbHelper = new StudentDbHelper(getActivity());
        //Get data repo in write mode
        SQLiteDatabase db = dbHelper.getWritableDatabase();
        //Create content values object
        ContentValues contentValues = new ContentValues();
        //put(column names of table, user data values) method
        contentValues.put(StudentInfoContract.Students.STUDENT_ID, id);
        contentValues.put(StudentInfoContract.Students.STUDENT_NAME, name);
        contentValues.put(StudentInfoContract.Students.STUDENT_EMAIL, email);
        //insert new row
        long recordId = db.insert(StudentInfoContract.Students.TABLE_NAME,
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
            Toast.makeText(getActivity(), "Successfully added student " + name + " in the db", Toast.LENGTH_SHORT).show();
        }
        //clear EditText fields
        et_std_id.setText("");
        et_name.setText("");
        et_email.setText("");
    }
}