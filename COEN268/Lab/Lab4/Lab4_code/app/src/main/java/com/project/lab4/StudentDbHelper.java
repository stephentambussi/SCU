/*  Stephen Tambussi
    COEN 268 - Lab 4 - 3/2/2022
*/
package com.project.lab4;

import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

public class StudentDbHelper extends SQLiteOpenHelper {
    private static final String DATABASE_NAME = "students.db";
    private static final int DATABASE_VERSION = 1;

    //Command for creating studentsinfo table
    private static final String CREATE_TABLE = "CREATE TABLE " +
            StudentInfoContract.Students.TABLE_NAME + "(" +
            StudentInfoContract.Students._ID + " INTEGER PRIMARY KEY" +
            " AUTOINCREMENT," +
            StudentInfoContract.Students.STUDENT_NAME + " TEXT NOT NULL, " +
            StudentInfoContract.Students.STUDENT_ID + " TEXT NOT NULL, " +
            StudentInfoContract.Students.STUDENT_EMAIL + " TEXT" + ")";

    //Command for deleting studentsinfo table
    private static final String DROP_TABLE = "DROP TABLE IF EXISTS " +
            StudentInfoContract.Students.TABLE_NAME;

    public StudentDbHelper(Context context)
    {
        super(context,DATABASE_NAME, null, DATABASE_VERSION);
    }

    @Override
    public void onCreate(SQLiteDatabase sqLiteDatabase)
    {
        //create all tables
        sqLiteDatabase.execSQL(CREATE_TABLE);
    }

    @Override
    public void onUpgrade(SQLiteDatabase sqLiteDatabase, int oldVersion, int newVersion)
    {
        //drop(delete) existing tables
        sqLiteDatabase.execSQL(DROP_TABLE);
        //start over, create a new table
        onCreate(sqLiteDatabase);
    }
}
