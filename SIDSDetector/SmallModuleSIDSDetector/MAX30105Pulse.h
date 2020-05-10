#ifndef SM_MAX30105PULSE_H_
#define SM_MAX30105PULSE_H_

#if defined(ARDUINO) && ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#include <Wire.h>
#include "MAX30105.h"
#include "spo2_algorithm.h"

#include "heartRate.h"

#include <inttypes.h>

#define RATE_SIZE 4 //Increase this for more averaging. 4 is good.

class MAX30105Pulse
{
public:
    MAX30105Pulse();
    int begin();
    void tick();
    int getBPM() { return beatAvg;}

private:
    MAX30105 particleSensor;

    byte rates[RATE_SIZE]; //Array of heart rates
    byte rateSpot = 0; //Index in array
    long lastBeat = 0; //Time at which the last beat occurred
    float beatsPerMinute = 0.0f;
    int beatAvg = 0;
};

#endif  // SM_MAX30105PULSE_H_