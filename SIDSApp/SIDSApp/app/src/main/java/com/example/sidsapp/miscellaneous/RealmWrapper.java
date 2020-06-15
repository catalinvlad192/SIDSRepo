package com.example.sidsapp.miscellaneous;

import android.content.Context;
import android.util.Log;
import android.widget.Toast;

import com.example.sidsapp.db.model.FirebaseEntry;
import com.example.sidsapp.db.model.RealmEntry;

import java.util.List;

import io.realm.Realm;
import io.realm.RealmConfiguration;
import io.realm.RealmResults;

public class RealmWrapper
{
    private static final String TAG = "[RealmWrapper]";

    private Realm realm_;
    private Context context_;

    public RealmWrapper(Context context)
    {
        realm_ = null;

        context_ = context;
        Realm.init(context);
        RealmConfiguration config = new RealmConfiguration.Builder()
                .deleteRealmIfMigrationNeeded()
                .build();
        Realm.setDefaultConfiguration(config);

        realm_ = Realm.getDefaultInstance();
    }

    public void createOrUpdateEntry(FirebaseEntry val)
    {
        if (realm_ != null)
        {
            RealmEntry entry = realm_.where(RealmEntry.class)
                    .equalTo("deviceId", val.deviceId)
                    .equalTo("time", val.time)
                    .findFirst();

            realm_.beginTransaction();

            if (entry == null) {
                RealmEntry newEntry = realm_.createObject(RealmEntry.class);

                newEntry.deviceId = val.deviceId;
                newEntry.time = val.time;
                newEntry.pulse = val.pulse;
                newEntry.oxygenLevel = val.oxygenLevel;
                newEntry.bodyTemperature = val.bodyTemperature;
                newEntry.CO2Resistance = val.CO2Resistance;
                newEntry.humidity = val.humidity;
                newEntry.ambientTemperature = val.ambientTemperature;
                newEntry.problems = val.problems;
            } else {
                entry.pulse = val.pulse;
                entry.oxygenLevel = val.oxygenLevel;
                entry.bodyTemperature = val.bodyTemperature;
                entry.CO2Resistance = val.CO2Resistance;
                entry.humidity = val.humidity;
                entry.ambientTemperature = val.ambientTemperature;
                entry.problems = val.problems;
            }
            realm_.commitTransaction();
        }
        else
        {
            Log.d(TAG, "CTR: Realm db not present in application");
            Toast.makeText(context_, "Trouble accessing Realm database", Toast.LENGTH_SHORT).show();
        }
    }

    public RealmEntry fetchMostRecent() {
        RealmResults<RealmEntry> realmResults = realm_
                .where(RealmEntry.class).findAll();
        List<RealmEntry> results = realm_.copyFromRealm(realmResults);
        RealmEntry mRecent = null;
        for (RealmEntry r : results) {
            if (mRecent == null || r.time.compareTo(mRecent.time) > 0) {
                mRecent = r;
            }
        }
        return mRecent;
    }


    public void deleteEverything()
    {
        if (realm_ != null)
        {
            RealmResults<RealmEntry> results = realm_.where(RealmEntry.class).findAll();

            realm_.beginTransaction();

            results.deleteAllFromRealm();

            realm_.commitTransaction();
        }
        else
        {
            Log.d(TAG, "CTR: Realm db not present in application");
            Toast.makeText(context_, "Trouble accessing Realm database", Toast.LENGTH_SHORT).show();
        }
    }

    public RealmResults<RealmEntry> getEntireDatabase()
    {
        RealmResults<RealmEntry> entriesDb = realm_.where(RealmEntry.class).findAll();
        return entriesDb;
    }

    public void close()
    {
        if (realm_ != null) realm_.close();
    }
}
