package es.sonla.smarthome;

import android.app.Activity;
import android.net.Uri;
import android.os.Bundle;
import android.app.Fragment;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.ListView;


public class ListFragment extends android.app.ListFragment {

    ListSelectionListener mListener = null;
    private int index;
    private int mCurrIdx = -1;

    public interface ListSelectionListener {
        public void onListSelection(int index);
    }


    @Override
    public void onAttach(Activity activity) {
        super.onAttach(activity);
        try {

            // Set the ListSelectionListener for communicating with the QuoteViewerActivity
            mListener = (ListSelectionListener) activity;

        } catch (ClassCastException e) {
            throw new ClassCastException(activity.toString()
                    + " must implement OnArticleSelectedListener");
        }
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        // This Fragment will add items to the ActionBar
        setHasOptionsMenu(true);

        // Retain this Fragment across Activity Reconfigurations
        setRetainInstance(true);
    }

    @Override
    public void onActivityCreated(Bundle savedState) {
        super.onActivityCreated(savedState);

        // Set the list adapter for the ListView
        // Discussed in more detail in the user interface classes lesson
        setListAdapter(new ArrayAdapter<String>(getActivity(),
                R.layout.fragment_list, AppActivity.SensorList));

        // If a title has already been selected in the past, reset the selection state now
        if (mCurrIdx != AppActivity.UNSELECTED) {
            setSelection(mCurrIdx);
        }
    }

    @Override
    public void onListItemClick(ListView l, View v, int pos, long id) {
        mCurrIdx = pos;

        // Indicates the selected item has been checked
        getListView().setItemChecked(pos, true);

        // Inform the QuoteViewerActivity that the item in position pos has been selected
        mListener.onListSelection(pos);
    }


}
