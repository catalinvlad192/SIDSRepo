#include "SMDataProcessor.h"

namespace sm{
DataProcessor::DataProcessor(int thermoPin)
    : thermometer_(thermoPin)
    , pulse_(0)
    , prevPulse_(76)
    , ox_(0.0f)
    , prevOx_(0.0f)
    , temp_(0.0f)
    , prevTemp_(0.0f)
    , isDeviceRemoved_(0)
{}

void DataProcessor::tick()
{
    tickPulse();
    tickOx();
    temp_ = thermometer_.getTemperature();

    if (prevPulse_ > PULSE_MIN && pulse_ < PULSE_THRESHOLD && ox_ > OX_MIN)
    {
        pulse_ = prevPulse_;
    }
    else if (pulse_ > PULSE_MIN && prevOx_ > OX_MIN && ox_ < OX_THRESHOLD)
    {
        ox_ = prevOx_;
    }
    else
    {
        prevOx_ = ox_;
        prevPulse_ = pulse_;
    }

    char problems[50];
    checkIfDeviceRemoved();

    int isProblem = checkForProblems(problems);

    char tempStr[7];
    dtostrf(temp_, 3, 2, tempStr);

    char oxStr[7];
    dtostrf(ox_, 3, 2, oxStr);

    char str[100];
    sprintf(str, "%d %5s %5s %d STOP",
        pulse_,
        oxStr,
        tempStr,
        isDeviceRemoved_);

    if(isProblem == 1)
        bt_.communicate(str, problems);
    else
        bt_.communicate(str, "");

}

void DataProcessor::tickPulse()
{
    MAX30105Pulse maxPulse;
    int avgPulse = 0;
    int pulseCount = 0;

    if (maxPulse.begin())
    {
        for(unsigned short int i = 0; i < 600; i++)
        {
            maxPulse.tick();
            int pulse = maxPulse.getBPM();
            if(pulse > 0 && pulse <= 250)
            {
                avgPulse+=pulse;
                pulseCount++;
            }
        }
    }
    if (pulseCount > 0)
    {
        pulse_ = avgPulse/pulseCount;
    }
    else
    {
        pulse_ = 0;
    }
}

void DataProcessor::tickOx()
{
    MAX30105Ox maxOx;
    int avgOx = 0;
    int oxCount = 0;

    if (maxOx.begin())
    {
        for(unsigned short int i = 0; i < 10; i++)
        {
            maxOx.tick();
            int ox = maxOx.getSpo2();
            if(ox <=100 && ox > 0)
            {
                avgOx+=ox;
                oxCount++;
            }
        }
    }
    if (oxCount > 0)
    {
        ox_ = ((float)avgOx)/((float)oxCount);
    }
    else
    {
        ox_ = 0.0f;
    }
}

int DataProcessor::checkIfDeviceRemoved()
{
    if ((temp_ < TEMP_THRESHOLD && (prevTemp_ > TEMP_THRESHOLD || prevTemp_ == 0.0f)) &&
            (ox_ < OX_THRESHOLD && (prevOx_ > OX_THRESHOLD || prevOx_ == 0.0f)) &&
            (pulse_ < PULSE_THRESHOLD && (prevPulse_ > PULSE_THRESHOLD || prevPulse_ == 0)))
    {
        isDeviceRemoved_ = 1;
    }
    else
    {
        isDeviceRemoved_ = 0;
    }
}

int DataProcessor::checkForProblems(char problems[50])
{
    if (isDeviceRemoved_) return 0;

    if (
        ((pulse_ >= PULSE_MAX || pulse_ < PULSE_MIN) && temp_ >= TEMP_MIN && temp_ < TEMP_MAX && ox_ > OX_MIN) ||
        ((temp_ >= TEMP_MAX || temp_ < TEMP_MIN) && pulse_ >= PULSE_MIN && pulse_ < PULSE_MAX && ox_ > OX_MIN) ||
        (ox_ < OX_MIN && temp_ >= TEMP_MIN && temp_ < TEMP_MAX && pulse_ >= PULSE_MIN && pulse_ < PULSE_MAX)
        )
    {
        char tempStr[7];
        dtostrf(temp_, 3, 2, tempStr);

        char oxStr[7];
        dtostrf(ox_, 3, 2, oxStr);

        sprintf(problems, "P: %d Ox: %5s T: %5s",
            pulse_,
            oxStr,
            tempStr);
        return 1;
    }
    return 0;
}
} // namespace sm
