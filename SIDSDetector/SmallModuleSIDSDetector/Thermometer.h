#ifndef THERMOMETER_H_
#define THERMOMETER_H_

#if defined(ARDUINO) && ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#include <inttypes.h>

class Thermometer
{
public:
    Thermometer(int analogPin);
    float getTemperature();

private:
    int analogPin_;
    float bodyTemperature_;
};

#endif  // THERMOMETER_H_
