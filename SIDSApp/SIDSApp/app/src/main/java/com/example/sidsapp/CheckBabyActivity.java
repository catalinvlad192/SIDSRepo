package com.example.sidsapp;

import android.app.Dialog;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ListView;
import android.widget.ProgressBar;
import android.widget.TextView;

import androidx.appcompat.app.ActionBar;
import androidx.appcompat.app.AppCompatActivity;
import androidx.preference.PreferenceFragmentCompat;
import androidx.preference.PreferenceManager;

import com.example.sidsapp.db.model.RealmEntry;
import com.example.sidsapp.miscellaneous.IAQProcessor;
import com.mikhaellopez.circularprogressbar.CircularProgressBar;

import java.util.ArrayList;
import java.util.Arrays;

import io.realm.RealmResults;

public class CheckBabyActivity extends AppCompatActivity {

    private TextView pulseText, pulseVal;
    private TextView oxText, oxVal;
    private TextView btempText, btempVal;
    private TextView humidityText, humidityVal;
    private TextView atempText, atempVal;
    private TextView iaqText, iaqVal;

    private TextView oxProgressVal, humidityProgressVal, iaqProgressVal;

    private ProgressBar pulseProgress, btempProgress, atempProgress;
    private CircularProgressBar oxProgress, humidityProgress, iaqProgress;

    private Button issuesButton;
    private Dialog dialog;

    private RealmEntry entry;
    private RealmResults<RealmEntry> all;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.settings_activity);
        getSupportFragmentManager()
                .beginTransaction()
                .replace(R.id.settings, new SettingsFragment())
                .commit();
        ActionBar actionBar = getSupportActionBar();
        if (actionBar != null) {
            actionBar.setDisplayHomeAsUpEnabled(true);
        }

        dialog = new Dialog(this);

        SharedPreferences prefs = PreferenceManager.getDefaultSharedPreferences(this);
        String id = prefs.getString("deviceId", "0");

        entry = MainActivity.realmWrapper_.fetchMostRecent();
        final RealmResults<RealmEntry> all = MainActivity.realmWrapper_.getEntireDatabase();

        findById();

        issuesButton.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View view)
            {

                ArrayList<String> prArray = new ArrayList<String>();
                if(entry != null)
                    prArray = new ArrayList<String>(Arrays.asList(entry.problems.split("\n")));

                for (RealmEntry e : all)
                {
                    ArrayList<String> arr = new ArrayList<String>(Arrays.asList(e.problems.split("\n")));
                    prArray.addAll(arr);
                }

                dialog.setContentView(R.layout.custom_popup);
                ArrayAdapter<String> adapter = new ArrayAdapter<String>(getApplicationContext(), R.layout.popup_element, R.id.problem, prArray);

                TextView close = dialog.findViewById(R.id.closeX);
                ListView listView = dialog.findViewById(R.id.popupListView);

                close.setOnClickListener(new View.OnClickListener() {
                    @Override
                    public void onClick(View view) {
                        dialog.dismiss();
                    }
                });


                listView.setAdapter(adapter);
                dialog.show();
            }
        });

        if(entry != null)
        {
            setPulse();
            setOxygenLevel();
            setBodyTep();
            setHumidity();
            setAmbTemp();
            setIaq();
        }
    }

    public static class SettingsFragment extends PreferenceFragmentCompat {
        @Override
        public void onCreatePreferences(Bundle savedInstanceState, String rootKey) {
            setPreferencesFromResource(R.xml.root_preferences, rootKey);
        }
    }

    private void findById()
    {
        pulseText = findViewById(R.id.pulseText);
        pulseVal = findViewById(R.id.pulseVal);
        oxText = findViewById(R.id.oxText);
        oxVal = findViewById(R.id.oxVal);
        btempText = findViewById(R.id.btempText);
        btempVal = findViewById(R.id.btempVal);
        humidityText = findViewById(R.id.humidityText);
        humidityVal = findViewById(R.id.humidityVal);
        atempText = findViewById(R.id.atempText);
        atempVal = findViewById(R.id.atempVal);
        iaqText = findViewById(R.id.iaqText);
        iaqVal = findViewById(R.id.iaqVal);

        oxProgressVal = findViewById(R.id.oxProgressVal);
        humidityProgressVal = findViewById(R.id.humidityProgressVal);
        iaqProgressVal = findViewById(R.id.iaqProgressVal);

        pulseProgress = findViewById(R.id.pulseProgress);
        btempProgress = findViewById(R.id.btempProgress);
        atempProgress = findViewById(R.id.atempProgress);
        iaqProgress = findViewById(R.id.iaqProgress);
        oxProgress = findViewById(R.id.oxProgress);
        humidityProgress = findViewById(R.id.humidityProgress);

        issuesButton = findViewById(R.id.issuesButton);
    }

    private void setPulse()
    {
        Log.d("CheckBabyActivity", entry.pulse);
        int pulse = Integer.parseInt(entry.pulse);

        if(pulse < 60)
            pulseProgress.setProgress(0);
        else if(pulse > 240)
            pulseProgress.setProgress(100);
        else
        {
            double percentage = ((pulse - 60.0)/180.0);
            int perc = (int)Math.round(percentage*100);
            pulseProgress.setProgress(perc);
        }
        pulseVal.setText(entry.pulse + " bpm");

        if(pulse < 100)
            pulseText.setBackgroundResource(R.color.bad_red);
        else if( pulse >= 100 && pulse < 130)
            pulseText.setBackgroundResource(R.color.orange);
        else if( pulse >= 130 && pulse < 150)
            pulseText.setBackgroundResource(R.color.avg_blue);
        else if( pulse >= 150 && pulse < 160)
            pulseText.setBackgroundResource(R.color.great_green);
        else if (pulse >= 160 && pulse < 180)
            pulseText.setBackgroundResource(R.color.avg_blue);
        else if (pulse >= 180 && pulse < 190)
            pulseText.setBackgroundResource(R.color.orange);
        else if (pulse >= 190)
            pulseText.setBackgroundResource(R.color.bad_red);
    }
    private void setOxygenLevel()
    {
        Log.d("CheckBabyActivity", entry.oxygenLevel);
        double ox = Double.parseDouble(entry.oxygenLevel);
        int oxint = (int)Math.round(ox);
        oxProgressVal.setText(entry.oxygenLevel + "%");
        oxProgress.setProgress(oxint);
        oxVal.setText(entry.oxygenLevel + "%");

        if(ox >= 95.0)
            oxText.setBackgroundResource(R.color.great_green);
        else if( ox < 95.0 && ox >= 90.0)
            oxText.setBackgroundResource(R.color.colorLightBlue);
        else if (ox < 90.0 && ox >= 85.0)
            oxText.setBackgroundResource(R.color.avg_blue);
        else if( ox < 85.0 && ox >= 80.0)
            oxText.setBackgroundResource(R.color.orange);
        else if( ox < 80.0)
            oxText.setBackgroundResource(R.color.bad_red);
    }
    private void setBodyTep()
    {
        Log.d("CheckBabyActivity", entry.bodyTemperature);
        double btemp = Double.parseDouble(entry.bodyTemperature);

        if(btemp < 35.0)
            btempProgress.setProgress(0);
        else if(btemp > 42.0)
            btempProgress.setProgress(100);
        else
        {
            double percentage = ((btemp - 34.0)/6.0);
            int perc = (int)Math.round(percentage*100);
            btempProgress.setProgress(perc);
        }

        btempVal.setText(entry.bodyTemperature + "C");

        if(btemp < 35.0)
            btempText.setBackgroundResource(R.color.bad_red);
        else if( btemp >= 35.0 && btemp < 35.5)
            btempText.setBackgroundResource(R.color.orange);
        else if (btemp >= 35.5 && btemp < 36.0)
            btempText.setBackgroundResource(R.color.avg_blue);
        else if( btemp >=  36.0 && btemp < 36.5)
            btempText.setBackgroundResource(R.color.colorLightBlue);
        else if( btemp >= 36.5 && btemp < 37.3)
            btempText.setBackgroundResource(R.color.great_green);
        else if( btemp >= 37.3 && btemp < 37.8)
            btempText.setBackgroundResource(R.color.colorLightBlue);
        else if( btemp >= 37.8 && btemp < 38.2)
            btempText.setBackgroundResource(R.color.avg_blue);
        else if( btemp >= 38.2 && btemp < 38.7)
            btempText.setBackgroundResource(R.color.orange);
        else if (btemp >= 38.7)
            btempText.setBackgroundResource(R.color.bad_red);
    }
    private void setHumidity()
    {

        Log.d("CheckBabyActivity", entry.humidity);
        double hum = Double.parseDouble(entry.humidity);
        int humint = (int)Math.round(hum);
        humidityProgressVal.setText(entry.humidity + "%");
        humidityProgress.setProgress(humint);
        humidityVal.setText(entry.humidity + "%");

        if(hum < 25.0)
            humidityText.setBackgroundResource(R.color.bad_red);
        else if( hum >= 25.0 && hum < 30.0)
            humidityText.setBackgroundResource(R.color.orange);
        else if (hum >= 30.0 && hum < 35.0)
            humidityText.setBackgroundResource(R.color.avg_blue);
        else if( hum >= 35.0 && hum < 40.0)
            humidityText.setBackgroundResource(R.color.colorLightBlue);
        else if( hum >= 40.0 && hum < 50.0)
            humidityText.setBackgroundResource(R.color.great_green);
        else if( hum >= 50.0 && hum < 55.0)
            humidityText.setBackgroundResource(R.color.colorLightBlue);
        else if (hum >= 55.0 && hum < 60.0)
            humidityText.setBackgroundResource(R.color.avg_blue);
        else if( hum >= 60.0 && hum < 65.0)
            humidityText.setBackgroundResource(R.color.orange);
        else if( hum >= 65.0)
            humidityText.setBackgroundResource(R.color.bad_red);
    }
    private void setAmbTemp()
    {
        Log.d("CheckBabyActivity", entry.ambientTemperature);
        double atemp = Double.parseDouble(entry.ambientTemperature);

        if(atemp < 15.0)
            atempProgress.setProgress(0);
        else if(atemp > 30.0)
            atempProgress.setProgress(100);
        else
        {
            double percentage = ((atemp - 15.0)/15.0);
            int perc = (int)Math.round(percentage*100);
            atempProgress.setProgress(perc);
        }
        atempVal.setText(entry.ambientTemperature + "C");
        atempText.setBackgroundResource(R.color.colorPrimaryDark);

        if(atemp < 15.0)
            atempText.setBackgroundResource(R.color.bad_red);
        else if( atemp >= 15.0 && atemp < 18.0)
            atempText.setBackgroundResource(R.color.orange);
        else if (atemp >= 18.0 && atemp < 19.0)
            atempText.setBackgroundResource(R.color.avg_blue);
        else if( atemp >= 19.0 && atemp < 20.0)
            atempText.setBackgroundResource(R.color.colorLightBlue);
        else if( atemp >= 20.0 && atemp < 22.0)
            atempText.setBackgroundResource(R.color.great_green);
        else if( atemp >= 22.0 && atemp < 23.0)
            atempText.setBackgroundResource(R.color.colorLightBlue);
        else if (atemp >= 23.0 && atemp < 24.0)
            atempText.setBackgroundResource(R.color.avg_blue);
        else if( atemp >= 24.0 && atemp < 25.0)
            atempText.setBackgroundResource(R.color.orange);
        else if( atemp >= 25.0)
            atempText.setBackgroundResource(R.color.bad_red);
    }
    private void setIaq()
    {
        Log.d("CheckBabyActivity", "Good");

        IAQProcessor.EIAQLevel iaqScore = IAQProcessor.calculateIAQ(Double.parseDouble(entry.humidity),
                Double.parseDouble(entry.CO2Resistance));

        switch(iaqScore)
        {
            case EIAQLevel_Hazardous:
                {
                    String iaq = "Hazardous";
                    iaqProgress.setProgress(0);
                    iaqProgressVal.setText(iaq);
                    iaqVal.setText(iaq);
                    iaqText.setBackgroundResource(R.color.bad_red);
                    break;
                }
            case EIAQLevel_VeryUnhealthy:
                {
                    String iaq = "Very unhealthy";
                    iaqProgress.setProgress(20);
                    iaqProgressVal.setText(iaq);
                    iaqVal.setText(iaq);
                    iaqText.setBackgroundResource(R.color.orange);
                    break;
                }
            case EIAQLevel_Unhealthy:
                {
                    String iaq = "Unhealthy";
                    iaqProgress.setProgress(40);
                    iaqProgressVal.setText(iaq);
                    iaqVal.setText(iaq);
                    iaqText.setBackgroundResource(R.color.yellow);
                    break;
                }
            case EIAQLevel_Moderate:
                {
                    String iaq = "Moderate";
                    iaqProgress.setProgress(60);
                    iaqProgressVal.setText(iaq);
                    iaqVal.setText(iaq);
                    iaqText.setBackgroundResource(R.color.avg_blue);
                    break;
                }
            case EIAQLevel_Good:
                {
                    String iaq = "Good";
                    iaqProgress.setProgress(80);
                    iaqProgressVal.setText(iaq);
                    iaqVal.setText(iaq);
                    iaqText.setBackgroundResource(R.color.colorLightBlue);
                    break;
                }
            case EIAQLevel_Great:
                {
                    String iaq = "Great";
                    iaqProgress.setProgress(100);
                    iaqProgressVal.setText(iaq);
                    iaqVal.setText(iaq);
                    iaqText.setBackgroundResource(R.color.great_green);
                    break;
                }
            default: break;
        }
    }
}