#ifndef SM_THERMOMETER_H_
#define SM_THERMOMETER_H_

#if defined(ARDUINO) && ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

//#include <inttypes.h>

namespace sm{
class Thermometer
{
public:
    Thermometer(int analogPin);
    float getTemperature();

private:
    float getTemperatureF();
    int analogPin_;
    float bodyTemperature_;
};
} // namespace sm
#endif  // THERMOMETER_H_
