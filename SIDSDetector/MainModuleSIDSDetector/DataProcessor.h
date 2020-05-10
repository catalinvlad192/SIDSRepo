#ifndef MM_DATAPROCESSOR_H_
#define MM_DATAPROCESSOR_H_

#if defined(ARDUINO) && ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#include <inttypes.h>
#include <Adafruit_Sensor.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "Adafruit_BME680.h"
#include "Buzzer.h"
#include "Leds.h"
#include "SensorData.h"
#include "Bluetooth.h"

namespace mm{
class DataProcessor
{
public:
    DataProcessor(int buzzerPin,
        int pulseLed,
        int oxygenLed,
        int bodyTemperatureLed,
        int humidityLed,
        int ambientTemperatureLed);
    void tick();

private:
    void setLedsAndBuzzer();
    void readAmbientParameters();
    void btCommunication();

    SensorData data_;
    Buzzer buzzer_;
    Leds leds_;
    Adafruit_BME680 bme_; //I2C
    Bluetooth bt_;
    bool isBmeOk_ = true;

};
} // namespace mm
#endif
