/*  Stephen Tambussi
    COEN 268 - Lab 4 - 3/2/2022
*/
package com.project.lab4;

import android.provider.BaseColumns;

public final class StudentInfoContract {
    private StudentInfoContract()
    {
        //Empty constructor
    }

    public static class Students implements BaseColumns
    {
        public static final String TABLE_NAME = "StudentsInfo";
        public static final String STUDENT_ID = "student_id";
        public static final String STUDENT_NAME = "name";
        public static final String STUDENT_EMAIL = "email";


    }
}
