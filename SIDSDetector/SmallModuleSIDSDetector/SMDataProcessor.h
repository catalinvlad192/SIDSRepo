#ifndef SM_DATAPROCESSOR_H_
#define SM_DATAPROCESSOR_H_

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
#include "SMBluetooth.h"
#include "MAX30105Pulse.h"
#include "MAX30105Ox.h"

namespace sm{
class DataProcessor
{
public:
    DataProcessor(int thermoPin);
    void tick();

private:
    void tickPulse();
    void tickOx();
    int checkIfDeviceRemoved();
    int checkForProblems(char problems[20]);

    Thermometer thermometer_;
    Bluetooth bt_;

    int pulse_;
    int prevPulse_;
    float ox_;
    float prevOx_;
    float temp_;
    float prevTemp_;
    int isDeviceRemoved_;

    const int PULSE_MIN = 50; // 90
    const int PULSE_MAX = 90; // 200
    const int PULSE_THRESHOLD = 40;

    const float TEMP_MAX = 38.0f;
    const float TEMP_MIN = 35.5f;
    const float TEMP_THRESHOLD = 33.0;

    const float OX_MIN = 88.0f;
    const float OX_THRESHOLD = 70.0f;

};
} // namespace sm
#endif  // DATAPROCESSOR_H_
