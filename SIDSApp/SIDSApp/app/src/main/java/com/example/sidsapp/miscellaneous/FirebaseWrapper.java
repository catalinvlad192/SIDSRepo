package com.example.sidsapp.miscellaneous;

import android.content.Context;
import android.util.Log;
import android.widget.Toast;

import com.example.sidsapp.db.model.FirebaseEntry;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

public class FirebaseWrapper
{
    private static final String TAG = "[FirebaseWrapper]";
    private FirebaseDatabase database_;
    private DatabaseReference myRef_;
    private RealmWrapper realmWrapper_;
    private Context context_;

    public FirebaseWrapper(RealmWrapper realm, final Context context)
    {
        myRef_ = null;

        context_ = context;
        database_ = FirebaseDatabase.getInstance();
        myRef_ = database_.getReference("myDb");
        realmWrapper_ = realm;



        if (myRef_ != null)
        {
            myRef_.addValueEventListener(new ValueEventListener() {
                @Override
                public void onCancelled(DatabaseError error) {
                    // Failed to read value
                    Log.w(TAG, "[onCancelled]Failed to read value.", error.toException());
                }

                @Override
                public void onDataChange(DataSnapshot dataSnapshot) {
                    // This method is called once with the initial value and again
                    // whenever data at this location is updated.
                    realmWrapper_.deleteEverything();
                    for(DataSnapshot x : dataSnapshot.getChildren())
                    {
                        for (DataSnapshot y : x.getChildren())
                        {
                            FirebaseEntry value = y.getValue(FirebaseEntry.class);
                            if(value != null)
                            {
                                realmWrapper_.createOrUpdateEntry(value);
                                Log.d(TAG, "[onDataChange]Value is: "
                                        + value.toString());

                            }else {
                                Log.d(TAG, "[onDataChange]Value is NULL");
                            }
                        }
                    }
                }
            });
        }
        else
        {
            Log.d(TAG, "CTR: Ref to database does not exist");
            Toast.makeText(context_, "Could not connect to Firebase database", Toast.LENGTH_SHORT).show();
        }
    }

    public void push(FirebaseEntry entry)
    {
        if (myRef_ != null)
        {
            myRef_.child(entry.deviceId).child(entry.time).setValue(entry);
        }
        else
        {
            Log.d(TAG, "push(): Ref to database does not exist");
            Toast.makeText(context_, "Could not connect to Firebase database", Toast.LENGTH_SHORT).show();
        }
    }
}
