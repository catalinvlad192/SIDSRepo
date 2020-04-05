#include "Leds.h"

#include "SensorData.h"

Leds::Leds(int pulseLed, int oxygenLed,int bodyTemperatureLed,int smokeLevelLed,int ambientTemperatureLed)
: pulseLed_(pulseLed),
  oxygenLed_(oxygenLed),
  bodyTemperatureLed_(bodyTemperatureLed),
  smokeLevelLed_(smokeLevelLed),
  ambientTemperatureLed_(ambientTemperatureLed)
{
}

// Pulse
void Leds::setLed(ELed type)
{
  //Serial.println(type);

  switch(type)
  {
      case ELed_Pulse: { digitalWrite(pulseLed_, HIGH); break; }
      case ELed_OxygenLevel: { digitalWrite(oxygenLed_, HIGH); break; }
      case ELed_BodyTemperature: { digitalWrite(bodyTemperatureLed_, HIGH); break; }
      case ELed_SmokeLevel: { digitalWrite(smokeLevelLed_, HIGH); break; }
      case ELed_AmbientTemperature: { digitalWrite(ambientTemperatureLed_, HIGH); break; }
      default: break;
  }
}

void Leds::reset()
{
  digitalWrite(pulseLed_, LOW);
  digitalWrite(oxygenLed_, LOW);
  digitalWrite(bodyTemperatureLed_, LOW);
  digitalWrite(smokeLevelLed_, LOW);
  digitalWrite(ambientTemperatureLed_, LOW);
}
