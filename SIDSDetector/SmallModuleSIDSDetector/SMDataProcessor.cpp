#include "SMDataProcessor.h"

#define PULSE_MIN 90 // 50 for tests
#define PULSE_MAX 200 // 90 for tests

#define TEMP_MAX 38.0f
#define TEMP_MIN 36.0f

#define TEMP_THRESHOLD_1 35.0f
#define TEMP_THRESHOLD_2 33.0f

namespace sm{
DataProcessor::DataProcessor(int thermoPin)
    : thermometer_(thermoPin)
    , pulse_(0)
    , ox_(0.0f)
{}

void DataProcessor::tick()
{
    tickPulse();
    tickOx();
    float temperature = thermometer_.getTemperature();

    char problems[50];
    int isDevRem = isDeviceRemoved(pulse_, temperature);

    int isProblem = checkForProblems(pulse_, temperature, problems);

    char tempStr[7];
    dtostrf(temperature, 3, 2, tempStr);

    char oxStr[7];
    dtostrf(ox_, 3, 2, oxStr);

    char str[100];
    sprintf(str, "%d %5s %5s %d STOP",
        pulse_,
        oxStr,
        tempStr,
        isDevRem);

    if(isProblem == 1)
        bt_.communicate(str, problems);
    else
        bt_.communicate(str, "");

}

void DataProcessor::setPulseOx(int pulse, float ox)
{
    pulse_ = pulse;
    ox_ = ox;
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

int DataProcessor::isDeviceRemoved(int pulse, float temp)
{
    static int prevPulse = 0;
    static float prevTemp = 0.0f;
    static int wasAlreadyRemoved = 0;

    if(prevPulse >= PULSE_MIN && pulse >= PULSE_MIN
        && prevTemp >= TEMP_MIN && temp >= TEMP_MIN)
    {
        wasAlreadyRemoved = 0;
    }

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

int DataProcessor::checkForProblems(int pulse, float temp, char problems[50])
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
        return 1;
    }
    return 0;
}
} // namespace sm
