#ifndef SM_MAX30105OX_H_
#define SM_MAX30105OX_H_

#if defined(ARDUINO) && ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#include <Wire.h>
#include "MAX30105.h"
#include "spo2_algorithm.h"

#include <inttypes.h>

class MAX30105Ox
{
public:
    MAX30105Ox();
    int begin();
    void tick();
    int getSpo2() { return spo2;}

private:
    MAX30105 particleSensor;

    uint16_t irBuffer[20]; //infrared LED sensor data
    uint16_t redBuffer[20];  //red LED sensor data
    int32_t bufferLength = 20; //data length
    int32_t spo2 = 0; //SPO2 value
    int8_t validSPO2 = 0; //indicator to show if the SPO2 calculation is valid
    int32_t heartRate = 0; //heart rate value
    int8_t validHeartRate = 0; //indicator to show if the heart rate calculation is valid
};

#endif  // SM_MAX30105OX_H_
