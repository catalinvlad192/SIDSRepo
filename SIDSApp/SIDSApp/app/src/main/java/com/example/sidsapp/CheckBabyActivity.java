package com.example.sidsapp;

import android.os.Bundle;
import android.util.Log;
import android.widget.ProgressBar;
import android.widget.TextView;

import androidx.appcompat.app.ActionBar;
import androidx.appcompat.app.AppCompatActivity;
import androidx.preference.PreferenceFragmentCompat;

import com.example.sidsapp.db.model.RealmEntry;
import com.mikhaellopez.circularprogressbar.CircularProgressBar;

public class CheckBabyActivity extends AppCompatActivity {

    private TextView pulseText, pulseVal;
    private TextView oxText, oxVal;
    private TextView btempText, btempVal;
    private TextView humidityText, humidityVal;
    private TextView atempText, atempVal;
    private TextView iaqText, iaqVal;

    private ProgressBar pulseProgress, btempProgress, atempProgress, iaqProgress;
    private CircularProgressBar oxProgress, humidityProgress;

    private RealmEntry entry;

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

        //----------Dirty init
        entry = new RealmEntry();
        entry.problems_ = "problems";
        entry.bodyTemp_ = "36.12";
        entry.CO2_ = "12000";
        entry.deviceId_ = "120";
        entry.humidity_ = "45.12";
        entry.oxygenLevel_ = "95.62";
        entry.pulse_ = "140";
        entry.temp_ = "23.14";
        //-----------------------------

        findById();

        setPulse();
        setOxygenLevel();
        setBodyTep();
        setHumidity();
        setAmbTemp();
        setIaq();
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

        pulseProgress = findViewById(R.id.pulseProgress);
        btempProgress = findViewById(R.id.btempProgress);
        atempProgress = findViewById(R.id.atempProgress);
        iaqProgress = findViewById(R.id.iaqProgress);
        oxProgress = findViewById(R.id.oxProgress);
        humidityProgress = findViewById(R.id.humidityProgress);
    }

    private void setPulse()
    {
        Log.d("CheckBabyActivity", entry.pulse_);
        int pulse = Integer.parseInt(entry.pulse_);
        pulseProgress.setProgress(55);
        pulseVal.setText(entry.pulse_);
        pulseText.setBackgroundResource(R.color.colorLightBlue);
    }
    private void setOxygenLevel()
    {
        Log.d("CheckBabyActivity", entry.oxygenLevel_);
        double ox = Double.parseDouble(entry.oxygenLevel_);
        oxProgress.setProgress(44);
        oxVal.setText(entry.oxygenLevel_);
        oxText.setBackgroundResource(R.color.colorAccent);
    }
    private void setBodyTep()
    {
        Log.d("CheckBabyActivity", entry.bodyTemp_);
        double btemp = Double.parseDouble(entry.bodyTemp_);
        btempProgress.setProgress(66);
        btempVal.setText(entry.bodyTemp_);
        btempText.setBackgroundResource(R.color.colorPrimary);
    }
    private void setHumidity()
    {
        Log.d("CheckBabyActivity", entry.humidity_);
        double hum = Double.parseDouble(entry.humidity_);
        humidityProgress.setProgress(88);
        humidityVal.setText(entry.humidity_);
        humidityText.setBackgroundResource(R.color.colorPrimaryDark);
    }
    private void setAmbTemp()
    {
        Log.d("CheckBabyActivity", entry.temp_);
        double atemp = Double.parseDouble(entry.temp_);
        atempProgress.setProgress(22);
        atempVal.setText(entry.temp_);
        atempText.setBackgroundResource(R.color.colorPrimaryDark);
    }
    private void setIaq()
    {
        Log.d("CheckBabyActivity", "Good");
        String iaq = "Good";
        iaqProgress.setProgress(45);
        iaqVal.setText(iaq);
        iaqText.setBackgroundResource(R.color.colorPrimaryDark);
    }
}