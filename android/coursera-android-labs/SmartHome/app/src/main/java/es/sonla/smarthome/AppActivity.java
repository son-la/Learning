package es.sonla.smarthome;

import android.app.Activity;
import android.app.FragmentManager;
import android.app.FragmentTransaction;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;


public class AppActivity extends Activity implements ListFragment.ListSelectionListener {


    public static String[] SensorList;
    public static final int UNSELECTED = -1;

    private final ListFragment mListFragment = new ListFragment();
    private final DataFragment mDataFragment = new DataFragment();
    private FragmentManager mFragmentManager;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_app);

        /* Prepare data */
        SensorList = getResources().getStringArray(R.array.sensor_list);


        final String app = this.getIntent().getStringExtra("app");
        mFragmentManager = getFragmentManager();

        FragmentTransaction fragmentTransaction = mFragmentManager.beginTransaction();

        /* Get app then setup correspond fragment*/
        switch(app) {
            case "sensor" :
                fragmentTransaction.add(R.id.list_fragment_container, mListFragment);
                fragmentTransaction.add(R.id.data_fragment_container, mDataFragment);
                break;
            default:
                break;
        }

        fragmentTransaction.commit();

    }


    @Override
    public void onResume()
    {
        super.onResume();
        getWindow().getDecorView().setSystemUiVisibility(View.SYSTEM_UI_FLAG_FULLSCREEN);
    }

    @Override
    public void onListSelection(int index) {
        mDataFragment.showSensor(index);
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {

        return super.onOptionsItemSelected(item);

    }
}
