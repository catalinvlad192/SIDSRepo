package com.example.sidsapp.db.model;

public class FirebaseEntry
{
    public String deviceId_;
    public String pulse_;
    public String oxygenLevel_;
    public String bodyTemp_;
    public String CO2_;
    public String humidity_;
    public String temp_;
    public String problems_;

    public String toString()
    {
        return deviceId_
                + " Pulse: " + pulse_
                + " OxygenLevel: " + oxygenLevel_
                + " BodyTemperature: " + bodyTemp_
                + " Gas: " + CO2_
                + " Humidity: " + humidity_
                + " Temp: " + temp_;
    }

    public void addProblem(String str)
    {
        problems_ = problems_ + " \n " + str;
    }
}
