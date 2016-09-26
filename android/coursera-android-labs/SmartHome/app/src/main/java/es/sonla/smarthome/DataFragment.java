package es.sonla.smarthome;

import android.app.Activity;
import android.net.Uri;
import android.os.AsyncTask;
import android.os.Bundle;
import android.app.Fragment;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.GridLayout;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.TextView;

import org.json.JSONArray;
import org.json.JSONObject;
import org.w3c.dom.Text;

import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;


public class DataFragment extends Fragment {

    private int mCurrIdx = AppActivity.UNSELECTED;
    private View mtLayout = null;

    public void showSensor(int index)
    {
        switch (index)
        {
            case 0:
                showTemeprature();
                break;
            default:
                break;
        }
    }

    @Override
    public void onDetach() {
        super.onDetach();
        mCurrIdx = AppActivity.UNSELECTED;
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
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {

        // Inflate the layout defined in quote_fragment.xml
        // The last parameter is false because the returned view does not need to be attached to the container ViewGroup
        mtLayout = (LinearLayout) inflater.inflate(R.layout.fragment_data, container, false);

        return mtLayout;
    }


    private void showTemeprature()
    {
        GetDataTask mDownloaderTask = new GetDataTask();
        try {
            URL[] url = new URL[2];
            url[0] = new URL("http://192.168.0.104:3000/sensors/temperature/now");
            url[1] = new URL("http://192.168.0.104:3000/sensors/temperature/day");
            mDownloaderTask.execute(url);
        }
        catch (Exception e)
        {
            throw new RuntimeException(e);
        }

    }



    public void setLayout(String[] result)
    {

        LinearLayout.LayoutParams lp1 = new LinearLayout.LayoutParams(
                RelativeLayout.LayoutParams.MATCH_PARENT,
                RelativeLayout.LayoutParams.MATCH_PARENT);
        lp1.weight = 1;

        LinearLayout.LayoutParams lp3 = new LinearLayout.LayoutParams(
                RelativeLayout.LayoutParams.MATCH_PARENT,
                RelativeLayout.LayoutParams.MATCH_PARENT);
        lp3.weight = 1;


        /* First row */
        LinearLayout first_row = new LinearLayout(getActivity());
        first_row.setGravity(Gravity.CENTER);
        first_row.setLayoutParams(lp1);
        first_row.setOrientation(LinearLayout.HORIZONTAL);
        ((LinearLayout) mtLayout).addView(first_row);

        LinearLayout stack1 = new LinearLayout(getActivity());
        stack1.setGravity(Gravity.CENTER);
        stack1.setLayoutParams(lp1);
        stack1.setOrientation(LinearLayout.VERTICAL);
        ((LinearLayout) first_row).addView(stack1);

        LinearLayout stack2 = new LinearLayout(getActivity());
        stack2.setGravity(Gravity.CENTER);
        stack2.setLayoutParams(lp1);
        stack2.setOrientation(LinearLayout.VERTICAL);
        ((LinearLayout) first_row).addView(stack2);



        TextView nowTxt = new TextView(getActivity());
        nowTxt.setGravity(Gravity.CENTER);
        nowTxt.setText("Now");
        nowTxt.setTextSize(20);
        //nowTxt.setLayoutParams(lp1);
        stack1.addView((TextView) nowTxt);

        TextView nowTv = new TextView(getActivity());
        nowTv.setGravity(Gravity.CENTER);
        nowTv.setText(result[0]);
        nowTv.setTextSize(20);
        //nowTv.setLayoutParams(lp3);
        stack1.addView((TextView) nowTv);


        TextView dayTxt = new TextView(getActivity());
        dayTxt.setGravity(Gravity.CENTER);
        dayTxt.setText("Day average");
        dayTxt.setTextSize(20);
        //dayTxt.setLayoutParams(lp1);
        stack2.addView((TextView) dayTxt);

        TextView dayTv = new TextView(getActivity());
        dayTv.setGravity(Gravity.CENTER);
        dayTv.setText(result[1]);
        dayTv.setTextSize(20);
        //dayTv.setLayoutParams(lp3);
        stack2.addView((TextView) dayTv);



        /* Second row */
        LinearLayout second_row = new LinearLayout(getActivity());
        second_row.setGravity(Gravity.CENTER);
        second_row.setLayoutParams(lp1);
        second_row.setOrientation(LinearLayout.HORIZONTAL);
        ((LinearLayout) mtLayout).addView(second_row);

        LinearLayout stack3 = new LinearLayout(getActivity());
        stack3.setGravity(Gravity.CENTER);
        stack3.setLayoutParams(lp1);
        stack3.setOrientation(LinearLayout.VERTICAL);
        ((LinearLayout) second_row).addView(stack3);


        TextView outsideTxt = new TextView(getActivity());
        outsideTxt.setGravity(Gravity.CENTER);
        outsideTxt.setText("Vaasa");
        outsideTxt.setTextSize(20);
        //outsideTxt.setLayoutParams(lp1);
        stack3.addView((TextView) outsideTxt);

        TextView outside = new TextView(getActivity());
        outside.setGravity(Gravity.CENTER);
        outside.setText("Unavailable");
        outside.setTextSize(20);
        //outside.setLayoutParams(lp3);
        stack3.addView((TextView) outside);
    }






















    public class GetDataTask extends AsyncTask<URL,Integer, String[]>
    {
        @Override
        protected void onPostExecute(String[] result)
        {
            try {
                JSONObject jObject;
                String[] input = new String[2];

                jObject= new JSONObject(result[0]);
                input[0] = String.format("%.2f", jObject.getDouble("temp"));

                jObject= new JSONObject(result[1]);
                input[1] = String.format("%.2f", jObject.getDouble("temp"));

               setLayout(input);
            }
            catch (Exception e)
            {
                throw new RuntimeException(e);
            }
        }


        @Override
        protected String[] doInBackground(URL ... url) {
            HttpURLConnection urlConnection;
            StringBuilder data1 = new StringBuilder();
            StringBuilder data2 = new StringBuilder();

            try {
                urlConnection = (HttpURLConnection) url[0].openConnection();

                InputStream in = new BufferedInputStream(urlConnection.getInputStream());

                BufferedReader r = new BufferedReader(new InputStreamReader(in));
                data1 = new StringBuilder();
                String line;
                while ((line = r.readLine()) != null) {
                    data1.append(line);
                }

                urlConnection.disconnect();

                /*****************************/
                urlConnection = (HttpURLConnection) url[1].openConnection();

                InputStream in2 = new BufferedInputStream(urlConnection.getInputStream());

                BufferedReader r2 = new BufferedReader(new InputStreamReader(in2));
                data2 = new StringBuilder();
                String line2;
                while ((line2 = r2.readLine()) != null) {
                    data2.append(line2);
                }

                urlConnection.disconnect();


            }
            catch (IOException e) {
                throw new RuntimeException(e);

            }

            String[] ret = new String[2];
            ret[0] = data1.toString();
            ret[1] = data2.toString();
            return ret;
        }
    }
}
