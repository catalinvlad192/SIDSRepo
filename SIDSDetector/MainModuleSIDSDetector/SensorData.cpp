#include "SensorData.h"

#include <string.h>

namespace mm{
SensorData::SensorData(unsigned int monthsOfAge) :
    pulse_(140),
    oxygenLevel_(99.0f),
    bodyTemperature_(37.0f),
    smokeLevel_(10.0f),
    humidity_(60.0f),
    ambientTemperature_(20.0f),
    isDeviceRemoved_(0),
	monthsOfAge_(monthsOfAge)
{
    init();
	strcpy(abnormalities_[0], "");
    strcpy(abnormalities_[1], "");
}

void SensorData::init()
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
        AMBIENTTEMP_MAX = 23.0f;
    }
}

void SensorData::addAbnormality(const char abnormality[50])
{
    if (strcmp(abnormality, "") == 0)
    {
        return;
    }

    if (abnIndex_ == 0)
    {
        strcpy(abnormalities_[0], abnormality);
        abnIndex_ = 1;
    }
    else
    {
        strcpy(abnormalities_[1], abnormality);
        abnIndex_ = 0;
    }
}

void SensorData::setMonths(int months)
{
    monthsOfAge_ = months;
    init();
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
} // namespace mm
