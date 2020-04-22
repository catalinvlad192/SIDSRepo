#include "Leds.h"

#include "SensorData.h"

Leds::Leds(int pulseLed, int oxygenLed,int bodyTemperatureLed,int humidityLed,int ambientTemperatureLed)
    : pulseLed_(pulseLed)
    , oxygenLed_(oxygenLed)
    , bodyTemperatureLed_(bodyTemperatureLed)
    , humidityLed_(humidityLed)
    , ambientTemperatureLed_(ambientTemperatureLed)
{}

void Leds::setLed(ELed type) const
{
    switch (type)
    {
        case ELed_Pulse: { digitalWrite(pulseLed_, HIGH); break; }
        case ELed_OxygenLevel: { digitalWrite(oxygenLed_, HIGH); break; }
        case ELed_BodyTemperature: { digitalWrite(bodyTemperatureLed_, HIGH); break; }
        case ELed_Humidity: { digitalWrite(humidityLed_, HIGH); break; }
        case ELed_AmbientTemperature: { digitalWrite(ambientTemperatureLed_, HIGH); break; }
        default: break;
    }
}

void Leds::reset() const
{
    digitalWrite(pulseLed_, LOW);
    digitalWrite(oxygenLed_, LOW);
    digitalWrite(bodyTemperatureLed_, LOW);
    digitalWrite(humidityLed_, LOW);
    digitalWrite(ambientTemperatureLed_, LOW);
}
