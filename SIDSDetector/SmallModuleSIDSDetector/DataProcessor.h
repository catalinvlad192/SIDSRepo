#ifndef DATAPROCESSOR_H_
#define DATAPROCESSOR_H_

#if defined(ARDUINO) && ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#include <inttypes.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "Thermometer.h"
#include "Bluetooth.h"

class DataProcessor
{
public:
    DataProcessor(int thermoPin);
    void tick();
    void setPulseOx(int pulse, float ox);

private:
    int calculatePulse();
    int calculatePulseWith(int instantPulse);
    float calculateTemperature();
    int isDeviceRemoved(int pulse, float temp);

    Thermometer thermometer_;
    Bluetooth bt_;

    int pulse_;
    float ox_;
};

#endif  // DATAPROCESSOR_H_
