#ifndef LEDS_H_
#define LEDS_H_

#if defined(ARDUINO) && ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#include <inttypes.h>

#include "SensorData.h"

class Leds {
public:
    enum ELed
    {
        ELed_Pulse = 0,
        ELed_OxygenLevel,
        ELed_BodyTemperature,
        ELed_Humidity,
        ELed_AmbientTemperature
    };

    Leds(int pulseLed, int oxygenLed,int bodyTemperatureLed,int humidityLed,int ambientTemperatureLed);

    void setLed(ELed type) const;
    void reset() const;

private:
    const int pulseLed_;
    const int oxygenLed_;
    const int bodyTemperatureLed_;
    const int humidityLed_;
    const int ambientTemperatureLed_;
};
#endif
