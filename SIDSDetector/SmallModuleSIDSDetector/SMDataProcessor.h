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
    void setPulseOx(int pulse, float ox);

private:
    void tickPulse();
    void tickOx();
    int isDeviceRemoved(int pulse, float ox, float temp);
    int checkForProblems(int pulse, float ox, float temp, int isRemoved, char problems[20]);

    Thermometer thermometer_;
    Bluetooth bt_;

    int pulse_;
    float ox_;
};
} // namespace sm
#endif  // DATAPROCESSOR_H_
