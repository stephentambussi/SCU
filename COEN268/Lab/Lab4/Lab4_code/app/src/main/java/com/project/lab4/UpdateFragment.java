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

public class UpdateFragment extends Fragment {

    private Button btn_update;
    private EditText et_name, et_email, et_std_id;

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_update, container, false);
        btn_update = view.findViewById(R.id.btn_update);
        et_email = view.findViewById(R.id.et_email);
        et_name = view.findViewById(R.id.et_name);
        et_std_id = view.findViewById(R.id.et_std_id);
        btn_update.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                updateStudentInfo();
            }
        });
        return view;
    }

    private void updateStudentInfo() {
        String id = et_std_id.getText().toString();
        String name = et_name.getText().toString();
        String email = et_email.getText().toString();

        if (id.isEmpty() || name.isEmpty()) {
            Toast.makeText(getActivity(), "Please enter a valid record", Toast.LENGTH_SHORT).show();
            return;
        }
        // Update the student info in the database
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
        //Update database with new data at row of user's name
        String whereClause = StudentInfoContract.Students.STUDENT_NAME + "=?";
        String[] whereArgs = {name};
        int count = db.update(StudentInfoContract.Students.TABLE_NAME, contentValues, whereClause, whereArgs);
        //close database connection
        db.close();
        if(count < 1)
        {
            Toast.makeText(getActivity(), "No records updated", Toast.LENGTH_SHORT).show();
        }
        else
        {
            Toast.makeText(getActivity(), "Updated " + count + " records" , Toast.LENGTH_SHORT).show();
        }
        //clear EditText fields
        et_std_id.setText("");
        et_name.setText("");
        et_email.setText("");
    }
}