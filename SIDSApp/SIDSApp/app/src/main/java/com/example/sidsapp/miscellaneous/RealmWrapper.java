package com.example.sidsapp.miscellaneous;

import android.content.Context;
import android.util.Log;
import android.widget.Toast;

import com.example.sidsapp.db.model.FirebaseEntry;
import com.example.sidsapp.db.model.RealmEntry;

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
                    .equalTo("deviceId_", val.deviceId_)
                    .findFirst();

            realm_.beginTransaction();

            if (entry == null) {
                RealmEntry newEntry = realm_.createObject(RealmEntry.class);

                newEntry.deviceId_ = val.deviceId_;
                newEntry.pulse_ = val.pulse_;
                newEntry.oxygenLevel_ = val.oxygenLevel_;
                newEntry.bodyTemp_ = val.bodyTemp_;
                newEntry.CO2_ = val.CO2_;
                newEntry.humidity_ = val.humidity_;
                newEntry.temp_ = val.temp_;
                newEntry.problems_ = val.problems_;
            } else {
                entry.pulse_ = val.pulse_;
                entry.oxygenLevel_ = val.oxygenLevel_;
                entry.bodyTemp_ = val.bodyTemp_;
                entry.CO2_ = val.CO2_;
                entry.humidity_ = val.humidity_;
                entry.temp_ = val.temp_;
                entry.problems_ = val.problems_;
            }
            realm_.commitTransaction();
        }
        else
        {
            Log.d(TAG, "CTR: Realm db not present in application");
            Toast.makeText(context_, "Trouble accessing Realm database", Toast.LENGTH_SHORT).show();
        }
    }

    public RealmEntry fetchById(String id)
    {
        if (realm_ != null)
        {
            return realm_.where(RealmEntry.class)
                    .equalTo("deviceId_", id)
                    .findFirst();
        }
        else
        {
            Log.d(TAG, "CTR: Realm db not present in application");
            Toast.makeText(context_, "Trouble accessing Realm database", Toast.LENGTH_SHORT).show();
            return null;
        }
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

//    public RealmResults<RealmEntry> getEntireDatabase()
//    {
//        RealmResults<RealmEntry> entriesDb = realm_.where(RealmEntry.class).findAll();
//        return entriesDb;
//    }

    public void close()
    {
        if (realm_ != null) realm_.close();
    }
}
