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
    DataProcessor(int thermoPin, int BOARD_TX, int BOARD_RX, int BOARD_EN, int BOARD_VCC);
    void tick();
    void setPulseOx(int pulse, float ox);

private:
    int calculatePulse();
    int calculatePulseWith(int instantPulse);
    float calculateTemperature();
    int isDeviceRemoved(int pulse, float temp);
    int checkForProblems(int pulse, float temp, char problems[20]);

    Thermometer thermometer_;
    Bluetooth bt_;

    int pulse_;
    float ox_;
};

#endif  // DATAPROCESSOR_H_
