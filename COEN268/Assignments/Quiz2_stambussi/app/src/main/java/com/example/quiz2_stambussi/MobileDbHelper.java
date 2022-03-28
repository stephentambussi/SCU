package com.example.quiz2_stambussi;

import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

//Be able to change this for Quiz2
public class MobileDbHelper extends SQLiteOpenHelper {
    private static final String DATABASE_NAME = "mobile.db";
    private static final int DATABASE_VERSION = 1;

    //Command for creating table
    private static final String CREATE_TABLE = "CREATE TABLE " +
            MobileInfoContract.Mobile.TABLE_NAME + "(" +
            MobileInfoContract.Mobile._ID + " INTEGER PRIMARY KEY" +
            " AUTOINCREMENT," +
            MobileInfoContract.Mobile.MOBILE_NUM + " TEXT NOT NULL, " +
            MobileInfoContract.Mobile.MODEL_NAME + " TEXT NOT NULL "+ ")";

    //Command for deleting studentsinfo table
    private static final String DROP_TABLE = "DROP TABLE IF EXISTS " +
            MobileInfoContract.Mobile.TABLE_NAME;

    public MobileDbHelper(Context context)
    {
        super(context, DATABASE_NAME, null, DATABASE_VERSION);
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

