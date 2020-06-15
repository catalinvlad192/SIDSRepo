package com.example.sidsapp.db.model;

import io.realm.RealmObject;

public class RealmEntry extends RealmObject
{
    public String time;
    public String deviceId;
    public String pulse;
    public String oxygenLevel;
    public String bodyTemperature;
    public String CO2Resistance;
    public String humidity;
    public String ambientTemperature;
    public String isDeviceRemoved;
    public String problems;

    public String toString()
    {
        return deviceId + " " + time
                + " Pulse: " + pulse
                + " OxygenLevel: " + oxygenLevel
                + " BodyTemperature: " + bodyTemperature
                + " Gas: " + CO2Resistance
                + " Humidity: " + humidity
                + " Temp: " + ambientTemperature
                + " IsDeviceRemoved " + isDeviceRemoved;
    }

    public void addProblem(String str)
    {
        problems = problems + "\n" + str;
    }
}
