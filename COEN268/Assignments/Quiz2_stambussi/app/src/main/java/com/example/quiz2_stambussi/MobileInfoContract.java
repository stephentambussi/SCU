package com.example.quiz2_stambussi;

import android.provider.BaseColumns;

//Be able to change this for Quiz2
public class MobileInfoContract {
    private MobileInfoContract()
    {
        //Empty Constructor
    }

    public static class Mobile implements BaseColumns
    {
        //inherited from BaseColumns:
        //_ID: unique ID for a row
        //_COUNT: number of rows
        public static final String TABLE_NAME = "MobileInfo";
        public static final String MOBILE_NUM = "mobile_num"; //table field (column name)
        public static final String MODEL_NAME = "name"; //table field (column name)
    }
}
