#include "DataProcessor.h"

#define PULSE_MIN 50 // 90

DataProcessor::DataProcessor(int thermoPin)
    : thermometer_(thermoPin)
    , pulse_(0)
    , ox_(0.0f)
{}

void DataProcessor::tick()
{
    float temperature = calculateTemperature();
    int pulse = calculatePulse();

    char tempStr[7];
    dtostrf(temperature, 3, 2, tempStr);

    char oxStr[7];
    dtostrf(ox_, 3, 2, oxStr);

    int isRem = isDeviceRemoved(pulse, temperature);

    char str[100];
    sprintf(str, "%d %5s %5s %d STOP",
        pulse,
        oxStr,
        tempStr,
        isRem);

    static int count = 0;
    count++;
    if(count > 1000)
    {
        Serial.println(str);
        count = 0;
    }
    // bt_.communicate(str);
}

void DataProcessor::setPulseOx(int pulse, float ox)
{
    pulse_ = pulse;
    ox_ = ox;
}

int DataProcessor::calculatePulse()
{
    static int sameValueCount = 0;
    static int sameValue = 0;

    if(pulse_ == sameValue)
    {
        if(sameValueCount > 200)
        {
            return calculatePulseWith(1);
        }
        else
        {
            sameValueCount++;
            return calculatePulseWith(pulse_);
        }
    }

    sameValueCount = 0;
    sameValue = pulse_;
    return calculatePulseWith(pulse_);
}

int DataProcessor::calculatePulseWith(int instantPulse)
{
    static int pulseCount = 0;
    static int pulseSum = 0;
    static int lastGoodPulse = 0;

    if((pulseSum > 0 && (pulseSum + instantPulse) < 0) || pulseCount > 600)
    {
        lastGoodPulse = pulseSum/pulseCount;

        pulseCount = 0;
        pulseSum = 0;
    }
    else if (instantPulse > 0 && instantPulse < 250)
    {
        pulseCount++;
        pulseSum = pulseSum + instantPulse;
    }

    return lastGoodPulse;
}

float DataProcessor::calculateTemperature()
{
    static float tempCount = 0.0f;
    static float tempSum = 0.0f;
    static float lastGoodTemp = 0.0f;

    float instantTemperature = thermometer_.getTemperature();

    tempCount++;
    tempSum = tempSum + instantTemperature;

    if(tempCount > 600)
    {
        lastGoodTemp = tempSum/tempCount;

        tempCount = 0.0f;
        tempSum = 0.0f;
    }

    return lastGoodTemp;
}

int DataProcessor::isDeviceRemoved(int pulse, float temp)
{
    if(pulse < PULSE_MIN && temp < 33.0f)
        return 1;

    return 0;
}
