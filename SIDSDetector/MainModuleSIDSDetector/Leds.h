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
        ELed_SmokeLevel,
        ELed_AmbientTemperature
    };

  Leds(int pulseLed, int oxygenLed,int bodyTemperatureLed,int smokeLevelLed,int ambientTemperatureLed);

  void setLed(ELed type);

  void reset();

private:
  int pulseLed_;
  int oxygenLed_;
  int bodyTemperatureLed_;
  int smokeLevelLed_;
  int ambientTemperatureLed_;
};
#endif
