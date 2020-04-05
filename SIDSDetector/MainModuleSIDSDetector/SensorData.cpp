#include "SensorData.h"

SensorData::SensorData(unsigned int monthsOfAge) :
  pulse_(140),
  oxygenLevel_(99.0f),
  bodyTemperature_(37.0f),
  smokeLevel_(10.0f),
  humidity_(60.0f),
  ambientTemperature_(20.0f),
  isDeviceProperlyAttached(false)
{
  if (monthsOfAge_ <= 3)
  {
    PULSE_MIN = 110;
    PULSE_MAX = 180;
    AMBIENTTEMP_MIN = 20.0f;
    AMBIENTTEMP_MAX = 25.0f;
  }
  else if (monthsOfAge_ <= 6)
  {
    PULSE_MIN = 105;
    PULSE_MAX = 175;
    AMBIENTTEMP_MIN = 19.0f;
    AMBIENTTEMP_MAX = 24.0f;
  }
  else if (monthsOfAge_ <= 9)
  {
    PULSE_MIN = 100;
    PULSE_MAX = 170;
    AMBIENTTEMP_MIN = 18.0f;
    AMBIENTTEMP_MAX = 23.0f;
  }
  else
  {
    PULSE_MIN = 90;
    PULSE_MAX = 160;
    AMBIENTTEMP_MIN = 18.0f;
    AMBIENTTEMP_MAX = 22.0f;
  }
}

//Getters for 'consts'
int SensorData::getPulseMin() const
{
  return PULSE_MIN;
}
int SensorData::getPulseMax() const
{
  return PULSE_MAX;
}
float SensorData::getAmbientTempMin() const
{
  return AMBIENTTEMP_MIN;
}
float SensorData::getAmbientTempMax() const
{
  return AMBIENTTEMP_MAX;
}
float SensorData::getOxygenLevelMin() const
{
  return OXYGENLEVEL_MIN;
}
float SensorData::getBodyTempMin() const
{
  return BODYTEMP_MIN;
}
float SensorData::getBodyTempMax() const
{
  return BODYTEMP_MAX;
}
float SensorData::getSmokeLevelMax() const
{
  return SMOKELEVEL_MAX;
}
