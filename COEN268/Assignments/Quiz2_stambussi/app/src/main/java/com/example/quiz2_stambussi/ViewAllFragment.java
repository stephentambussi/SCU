package com.example.quiz2_stambussi;

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
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;


public class ViewAllFragment extends Fragment implements View.OnClickListener {

    private Mobile[] mobile ;
    private ArrayAdapter<Mobile> listAdapter ;
    //private TextView tv_all_student;
    ViewAllFragment.OnFragmentInteractionListener listener;
    public ViewAllFragment()
    {

    }



    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_view_all, container,false);

        Button btn_delete;
        btn_delete = view.findViewById(R.id.btn_delete);
        //tv_all_student = view.findViewById(R.id.tv_all_student_info);
        btn_delete.setOnClickListener(this);
        ListView mainListView = (ListView) view.findViewById( R.id.list_view );

        /*
        // When item is tapped, toggle checked properties of CheckBox and Planet.
        mainListView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick( AdapterView<?> parent, View item,
                                     int position, long id) {
                Mobile planet = listAdapter.getItem( position );
                planet.toggleChecked();
                MobileViewHolder viewHolder = (MobileViewHolder) item.getTag();
                viewHolder.getCheckBox().setChecked( planet.isChecked() );
            }
        });

        // Create and populate planets.
        mobile = (Mobile[]) onRetainCustomNonConfigurationInstance() ;
        if ( mobile == null ) {
            //do nothing
        }
        ArrayList<Mobile> mobileList = new ArrayList<Mobile>();
        mobileList.addAll(Arrays.asList(mobile));

        // Set our custom array adapter as the ListView's adapter.
        listAdapter = new MobileAdapter(getActivity(), mobileList);
        mainListView.setAdapter( listAdapter );
        */
        return view;
    }

    private static class Mobile {
        private String name = "" ;
        private String num = "";
        private boolean checked = false ;
        public Mobile() {}
        public Mobile( String name, String num ) {
            this.name = name ;
            this.num = num;
        }
        public Mobile( String name, boolean checked ) {
            this.name = name ;
            this.checked = checked ;
        }
        public String getName() {
            return name;
        }
        public void setName(String name) {
            this.name = name;
        }
        public String getNum() {
            return num;
        }
        public void setNum(String num) {
            this.name = num;
        }
        public boolean isChecked() {
            return checked;
        }
        public void setChecked(boolean checked) {
            this.checked = checked;
        }
        public String toString() {
            return name ;
        }
        public void toggleChecked() {
            checked = !checked ;
        }
    }

    private static class MobileViewHolder {
        private CheckBox checkBox ;
        private TextView textView ;
        private TextView textView2;
        public MobileViewHolder() {}
        public MobileViewHolder( TextView textView, TextView textView2, CheckBox checkBox ) {
            this.checkBox = checkBox ;
            this.textView = textView ;
            this.textView2 = textView2;
        }
        public CheckBox getCheckBox() {
            return checkBox;
        }
        public void setCheckBox(CheckBox checkBox) {
            this.checkBox = checkBox;
        }
        public TextView getTextView() {
            return textView;
        }
        public TextView getTextView2() {
            return textView2;
        }
        public void setTextView(TextView textView) {
            this.textView = textView;
        }
    }

    @Override
    public void onViewCreated(@NonNull View view, @Nullable Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);
        getAllMobileInfo();
    }

    public interface OnFragmentInteractionListener{
        void replaceFragment(MainActivity.FragmentType type);
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.btn_delete:
                //listener.replaceFragment(MainActivity.FragmentType.ADD);
                //saveMobileInfoIntoDatabase();
                break;
        }
    }

    @Override
    public void onAttach(Context context) {
        super.onAttach(context);
        if (context instanceof ViewAllFragment.OnFragmentInteractionListener) {
            listener = (ViewAllFragment.OnFragmentInteractionListener) context;
        } else {
            throw new RuntimeException(context.toString()
                    + " must implement OnFragmentInteractionListener");
        }
    }

    private void getAllMobileInfo() {
        // Retrieve the student info saved from the database
        //instantiate database
        MobileDbHelper dbHelper = new MobileDbHelper(getActivity());
        //Get data repo in read mode
        SQLiteDatabase db = dbHelper.getReadableDatabase();
        //Query() method to get database values
        Cursor cursor = db.query(MobileInfoContract.Mobile.TABLE_NAME, null,
                null, null, null, null,
                MobileInfoContract.Mobile.MOBILE_NUM);
        String result = "";
        while(cursor.moveToNext()) //while there is data in the database
        {
            String id = cursor.getString(cursor.getColumnIndex(MobileInfoContract.Mobile.MOBILE_NUM));
            String name = cursor.getString(cursor.getColumnIndex(MobileInfoContract.Mobile.MODEL_NAME));

            //append record to the result
            result = result + "\n\nID: " + id + "\nNAME: " + name;
        }
        //close database connection
        db.close();
        if(result.length() == 0) result = "No records Found";

        //Populate layout
        //tv_all_student.setText(result);
    }

    /*
    private void deleteMobile() {
        String id = et_id.getText().toString();
        if (id.isEmpty()) {
            Toast.makeText(getActivity(), "ID cannot be empty", Toast.LENGTH_SHORT).show();
            return;
        }
        // Delete the student with the input id from the database
        //instantiate database
        MobileDbHelper dbHelper = new MobileDbHelper(getActivity());
        //Get data repo in write mode
        SQLiteDatabase db = dbHelper.getWritableDatabase();

        //Update database by removing student info at row of id
        String whereClause = MobileInfoContract.Students.STUDENT_ID + "=?";
        String[] whereArgs = {id};
        int count = db.delete(MobileInfoContract.Students.TABLE_NAME, whereClause, whereArgs);
        //close database connection
        db.close();
        if(count < 1)
        {
            Toast.makeText(getActivity(), "No records removed", Toast.LENGTH_SHORT).show();
        }
        else
        {
            Toast.makeText(getActivity(), "Removed " + count + " records" , Toast.LENGTH_SHORT).show();
        }
        //clear EditText fields
        et_id.setText("");
    }

     */
    private static class MobileAdapter extends ArrayAdapter<Mobile> {

        private LayoutInflater inflater;

        public MobileAdapter( Context context, List<Mobile> mobileList ) {
            super(context, R.layout.simplerow, R.id.mobile_rowTextView, mobileList );
            // Cache the LayoutInflate to avoid asking for a new one each time.
            inflater = LayoutInflater.from(context) ;
        }

        @Override
        public View getView(int position, View convertView, ViewGroup parent) {
            // Planet to display
            Mobile mobile = this.getItem( position );

            // The child views in each row.
            CheckBox checkBox ;
            TextView textView, textView2;

            // Create a new row view
            if ( convertView == null ) {
                convertView = inflater.inflate(R.layout.simplerow, null);

                // Find the child views.
                textView = (TextView) convertView.findViewById( R.id.mobile_rowTextView );
                textView2 = (TextView) convertView.findViewById( R.id.model_rowTextView );
                checkBox = (CheckBox) convertView.findViewById( R.id.CheckBox01 );

                // Optimization: Tag the row with it's child views, so we don't have to
                // call findViewById() later when we reuse the row.
                convertView.setTag( new MobileViewHolder(textView, textView2, checkBox) );

                // If CheckBox is toggled, update the planet it is tagged with.
                checkBox.setOnClickListener( new View.OnClickListener() {
                    public void onClick(View v) {
                        CheckBox cb = (CheckBox) v ;
                        Mobile mobile = (Mobile) cb.getTag();
                        mobile.setChecked( cb.isChecked() );
                    }
                });
            }
            // Reuse existing row view
            else {
                // Because we use a ViewHolder, we avoid having to call findViewById().
                MobileViewHolder viewHolder = (MobileViewHolder) convertView.getTag();
                checkBox = viewHolder.getCheckBox() ;
                textView = viewHolder.getTextView() ;
                textView2 = viewHolder.getTextView();
            }

            // Tag the CheckBox with the Planet it is displaying, so that we can
            // access the planet in onClick() when the CheckBox is toggled.
            checkBox.setTag( mobile );

            // Display planet data
            checkBox.setChecked( mobile.isChecked() );
            textView.setText( mobile.getName() );
            textView2.setText(mobile.getName());

            return convertView;
        }

    }
    public Object onRetainCustomNonConfigurationInstance() {
        return mobile;
    }
}