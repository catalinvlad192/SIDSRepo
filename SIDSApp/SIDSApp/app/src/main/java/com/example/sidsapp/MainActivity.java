package com.example.sidsapp;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.BaseAdapter;
import android.widget.Button;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import com.example.sidsapp.db.model.FirebaseEntry;
import com.example.sidsapp.db.model.RealmEntry;
import com.example.sidsapp.miscellaneous.FirebaseWrapper;
import com.example.sidsapp.miscellaneous.RealmWrapper;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintStream;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.UUID;

public class MainActivity extends Activity
{
    private static final String TAG = "MainActivity";
    private static final int REQUEST_ENABLE_BT = 1;
    private static final long SCAN_PERIOD = 10000; // Stops scanning after 10 seconds.
    private UUID myUUID_ = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB"); // UUID for all HC-05 devices

    private Handler handler_;

    // Wrappers for Firebase and Realm
    private RealmWrapper realmWrapper;
    private FirebaseWrapper firebaseWrapper_;

    // List adapter elements
    private HashMap<String, BluetoothDevice> foundDevices_;
    private ArrayList<String> foundDevicesAddresses_;
    private MyAdapter myAdapter_;

    // Views
    private Button searchDevice_;
    private Button checkBaby_;
    private Button firstAid_;
    private ListView listView_;

    // Bt
    private BluetoothAdapter bluetoothAdapter_;
    private BluetoothSocket socket_ = null;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Search views by id
        searchDevice_ = findViewById(R.id.searchDeviceButton);
        checkBaby_ = findViewById(R.id.checkBabyButton);
        firstAid_ = findViewById(R.id.firstAidButton);
        listView_ = findViewById(R.id.listView);

        // Create wrapper objects
        realmWrapper = new RealmWrapper(getApplicationContext());
        firebaseWrapper_ = new FirebaseWrapper(realmWrapper, getApplicationContext());

        // Devices found, devices addresses and handler creation
        foundDevices_ = new HashMap<String, BluetoothDevice>();
        foundDevicesAddresses_ = new ArrayList<String>();
        handler_ = new Handler();

        enableBluetooth();

        // Register for broadcasts when a device is discovered.
        IntentFilter filter = new IntentFilter(BluetoothDevice.ACTION_FOUND);
        registerReceiver(receiver, filter);

        // Adapter list
        myAdapter_ = new MyAdapter(this, foundDevicesAddresses_, foundDevices_);
        listView_.setAdapter(myAdapter_);

        // Set item click on ListView
        listView_.setOnItemClickListener(new AdapterView.OnItemClickListener()
        {
            @Override
            public void onItemClick(AdapterView<?> adapterView, View view, int i, long l)
            {
                readFromDeviceViaBluetooth(i);
            }
        });

        checkBaby_.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View view)
            {
                openCheckBabyActivity();
            }
        });

        firstAid_.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View view) {
                openFirstAidActivity();
            }
        });

        // On startScanButton_ click
        searchDevice_.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                foundDevicesAddresses_.clear();
                foundDevices_.clear();
                myAdapter_.notifyDataSetChanged();

                // Stops scanning after a pre-defined scan period
                handler_.postDelayed(new Runnable() {
                    @Override
                    public void run() {
                        bluetoothAdapter_.cancelDiscovery();
                        Toast.makeText(MainActivity.this, "Stop scan",
                                Toast.LENGTH_SHORT).show();
                    }
                }, SCAN_PERIOD);
                bluetoothAdapter_.startDiscovery();
                Toast.makeText(MainActivity.this, "Start scan",
                        Toast.LENGTH_SHORT).show();
            }
        });
    }

    @Override
    protected void onDestroy()
    {
        super.onDestroy();
        firebaseWrapper_ = null;
        realmWrapper.close();
        unregisterReceiver(receiver);
    }

    private void openCheckBabyActivity()
    {
        startActivity(new Intent(this, CheckBabyActivity.class));
    }
    private void openFirstAidActivity()
    {
        startActivity(new Intent(this, FirstAidActivity.class));
    }

    private void enableBluetooth()
    {
        // Bluetooth adapter and bluetooth enable
        bluetoothAdapter_ = BluetoothAdapter.getDefaultAdapter();
        if (bluetoothAdapter_ == null)
        {
            Toast.makeText(this, "This device does not support Bluetooth",
                    Toast.LENGTH_SHORT).show();
        }
        if (!bluetoothAdapter_.isEnabled()) {
            Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(enableBtIntent, REQUEST_ENABLE_BT);
        }
    }

    private void readFromDeviceViaBluetooth(int index)
    {
        BluetoothDevice device = foundDevices_.get(foundDevicesAddresses_.get(index));
        socket_ = null;

        // Trying to connect to bluetooth device
        if (!connectToDevice(device))
            return;

        // Stop device discovery
        bluetoothAdapter_.cancelDiscovery();

        // Communication
        if(!communicate())
            return;

        // Close communication
        try
        {
            socket_.close();
        }
        catch (IOException closeException)
        {
            Log.e(TAG, "Could not close the client socket after finishing", closeException);
        }
    }

    private boolean connectToDevice(BluetoothDevice device)
    {
        // Trying to connect to bluetooth device
        try
        {
            if (device != null)
            {
                socket_ = device.createRfcommSocketToServiceRecord(myUUID_);
                socket_.connect();
            }
        }
        catch (IOException e)
        {
            Log.d(TAG, "Couldn't connect the first time. Trying fallback");
            try
            {
                socket_ =(BluetoothSocket) device.getClass().getMethod("createRfcommSocket",
                        new Class[] {int.class}).invoke(device,1);
                socket_.connect();
            }
            catch(Exception ex)
            {
                Log.d(TAG, "Could not connect not even the second time. Returning...");
                return false;
            }
        }
        return true;
    }

    private boolean communicate()
    {
        // Communication
        try
        {
            Log.d(TAG, "Connected");

            // Output/Input streams
            OutputStream outputStream = socket_.getOutputStream();
            PrintStream printStream = new PrintStream(outputStream);
            InputStream inputStream = socket_.getInputStream();
            BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(inputStream));

            // Write baby months
            outputStream.write(2);
            outputStream.write(2);

            printStream.println("SML");
            printStream.println("150  97.30  37.52 0");
            printStream.println("P: 90, Ox: 80.14%, T: 32.45");
            printStream.println("OVR");

            // Read garbage
//            String garbage = bufferedReader.readLine();
//
//            // Read parameters
//            String parameters = bufferedReader.readLine();
//
//            // Read problems
//            String problem1 = bufferedReader.readLine();
//            String problem2 = bufferedReader.readLine();
//
//            // Read over
//            String over = bufferedReader.readLine();
//
//            if (parameters == null) parameters = "x";
//            Log.d(TAG, "Received" + parameters);
//
//            String[] par = parameters.split(" ");
//
//            Toast.makeText(this, garbage + " " + parameters, Toast.LENGTH_SHORT).show();

//            if (par.length == 8) {
//                FirebaseEntry entry = new FirebaseEntry();
//                RealmEntry realmEntry = null;
//
//                entry.deviceId_ = par[0];
//                entry.pulse_ = par[1];
//                entry.oxygenLevel_ = par[2];
//                entry.bodyTemp_ = par[3];
//                entry.CO2_ = par[4];
//                entry.humidity_ = par[5];
//                entry.temp_ = par[6];
//
//                if( (realmEntry = realmWrapper.fetchById(par[0])) != null)
//                {
//                    entry.problems_ = realmEntry.problems_;
//                    entry.addProblem(problems);
//                }
//                else
//                {
//                    entry.problems_ = problems;
//                }
//
//                firebaseWrapper_.push(entry);
//            }
//            else
//            {
//                Toast.makeText(this, "Communication failure", Toast.LENGTH_SHORT).show();
//            }
        }
        catch (IOException connectException)
        {
            // Unable to connect; close the socket and return.
            try
            {
                socket_.close();
            } catch (IOException closeException)
            {
                Log.e(TAG, "Could not close the client socket", closeException);
            }
            return false;
        }
        return true;
    }

    // ListAdapter class
    class MyAdapter extends ArrayAdapter<String>
    {
        Context context_;
        ArrayList<String> devsAddress_;
        HashMap<String, BluetoothDevice> devsHashMap_;

        MyAdapter(Context ctx, ArrayList<String> devs, HashMap<String,BluetoothDevice> devMap)
        {
            super(ctx, R.layout.list_view_element_layout, devs);
            context_ = ctx;
            devsAddress_ = devs;
            devsHashMap_ = devMap;
        }

        @NonNull
        @Override
        public View getView(int position, @NonNull View convertView, @NonNull ViewGroup parent)
        {
            LayoutInflater layoutInflater = (LayoutInflater)getApplicationContext()
                    .getSystemService(Context.LAYOUT_INFLATER_SERVICE);
            View row = layoutInflater.inflate(R.layout.list_view_element_layout, parent, false);

            TextView title = row.findViewById(R.id.device_name);
            TextView address = row.findViewById(R.id.device_address);

            title.setText(devsHashMap_.get(devsAddress_.get(position)).getName());
            address.setText(devsAddress_.get(position));
            return row;
        }
    }

    // Create a BroadcastReceiver for ACTION_FOUND.
    private final BroadcastReceiver receiver = new BroadcastReceiver() {
        public void onReceive(Context context, Intent intent) {
            String action = intent.getAction();
            if (BluetoothDevice.ACTION_FOUND.equals(action)) {
                // Discovery has found a device. Get the BluetoothDevice
                // object and its info from the Intent.
                BluetoothDevice device = intent.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE);
                String name = device.getName();
                if(device.getName() != null)
                {
                    if( (foundDevices_.put(device.getAddress(), device)) == null )
                    {
                        foundDevicesAddresses_.add(device.getAddress());
                        ((BaseAdapter) myAdapter_).notifyDataSetChanged();

                        Toast.makeText(MainActivity.this, "Map size: "
                                + foundDevices_.size() + " ArraySize: "
                                + foundDevicesAddresses_.size(), Toast.LENGTH_SHORT).show();
                    }
                }
            }
        }
    };
}
