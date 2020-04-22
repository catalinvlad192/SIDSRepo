#include "DataProcessor.h"

#define PULSE_MIN 50 // 90
#define PULSE_MAX 90 // 200

#define TEMP_MAX 38.0f
#define TEMP_MIN 36.0f

#define TEMP_THRESHOLD_1 35.0f
#define TEMP_THRESHOLD_2 33.0f

DataProcessor::DataProcessor(int thermoPin, int BOARD_TX, int BOARD_RX, int BOARD_EN, int BOARD_VCC)
    : thermometer_(thermoPin)
    , bt_(BOARD_TX, BOARD_RX, BOARD_EN, BOARD_VCC)
    , pulse_(0)
    , ox_(0.0f)
{}

void DataProcessor::tick()
{
    float temperature = calculateTemperature();
    int pulse = calculatePulse();

    static int count = 0;
    count++;
    if(count > 2000)
    {
        char problems[20];
        int isDevRem = isDeviceRemoved(pulse, temperature);
        int isProblem = checkForProblems(pulse, temperature, problems);

        char tempStr[7];
        dtostrf(temperature, 3, 2, tempStr);

        char oxStr[7];
        dtostrf(ox_, 3, 2, oxStr);

        char str[100];
        sprintf(str, "%d %5s %5s %d STOP",
            pulse,
            oxStr,
            tempStr,
            isDevRem);

        if(isProblem)
            bt_.communicate(str, problems);
        else
            bt_.communicate(str, "");
        count = 0;
    }
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
    static int prevPulse = 0;
    static float prevTemp = 0.0f;
    static int wasAlreadyRemoved = 0;
    if(wasAlreadyRemoved == 1 ||
        ((pulse < PULSE_MIN && temp < TEMP_THRESHOLD_2)
            && (prevPulse >= PULSE_MIN && prevTemp >= TEMP_THRESHOLD_1)) ||
        (pulse < 30 && temp < 30.0f))
    {
        prevPulse = pulse;
        prevTemp = temp;
        wasAlreadyRemoved = 1;
        return 1;
    }
    else
    {
        prevPulse = pulse;
        prevTemp = temp;
        wasAlreadyRemoved = 0;
        return 0;
    }
}

int DataProcessor::checkForProblems(int pulse, float temp, char problems[20])
{
    if (((pulse >= PULSE_MAX || pulse < PULSE_MIN) && temp >= TEMP_MIN && temp < TEMP_MAX) ||
        ((temp >= TEMP_MAX || temp < TEMP_MIN ) && pulse >= PULSE_MIN && pulse < PULSE_MAX))
    {

        char tempStr[7];
        dtostrf(temp, 3, 2, tempStr);

        char oxStr[7];
        dtostrf(ox_, 3, 2, oxStr);

        sprintf(problems, "P: %d, Ox: %5s%, T: %5s",
            pulse,
            oxStr,
            tempStr);
        return true;
    }
    return false;
}
