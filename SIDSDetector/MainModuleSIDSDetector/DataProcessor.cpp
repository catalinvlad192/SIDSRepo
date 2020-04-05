#include "DataProcessor.h"

#include "Buzzer.h"
#include "Leds.h"
#include "SensorData.h"

#include <string.h>

#define deviceId 120

DataProcessor::DataProcessor(int buzzerPin, int pulseLed, int oxygenLed, int bodyTemperatureLed, int smokeLevelLed, int ambientTemperatureLed)
    : data_(SensorData(3))
    , buzzer_(Buzzer(buzzerPin))
    , leds_(Leds(pulseLed, oxygenLed, bodyTemperatureLed, smokeLevelLed, ambientTemperatureLed))
{
    isBmeOk_ = true;
    if (!bme_.begin(0x76)) {
        Serial.println("Could not find a valid BME680 sensor, check wiring!");
        isBmeOk_ = false;
    }
    if (isBmeOk_)
    {
        // Set up oversampling and filter initialization
        bme_.setTemperatureOversampling(BME680_OS_8X);
        bme_.setHumidityOversampling(BME680_OS_2X);
        bme_.setPressureOversampling(BME680_OS_4X);
        bme_.setIIRFilterSize(BME680_FILTER_SIZE_3);
        bme_.setGasHeater(320, 150); // 320*C for 150 ms

        bme_.performReading();
    }
}

void DataProcessor::tick()
{
      //BLE
      readAmbientParameters();
      setLedsAndBuzzer();
      btCommunication();
}

void DataProcessor::readAmbientParameters()
{
    static unsigned int numberOfCalls = 0;

    if (numberOfCalls == 0)
    {
        float temperature=0.0f , humidity = 0.0f;
        unsigned int gas = 0;

        numberOfCalls = 1;

        bme_.performReading();

        bme_.performReading();
        temperature += bme_.temperature;
        humidity += bme_.humidity;
        gas += bme_.gas_resistance;

        bme_.performReading();
        temperature += bme_.temperature;
        humidity += bme_.humidity;
        gas += bme_.gas_resistance;

        bme_.performReading();
        temperature += bme_.temperature;
        humidity += bme_.humidity;
        gas += bme_.gas_resistance;

        temperature /= 3.0f;
        humidity /= 3.0f;
        gas /= 3;

        data_.ambientTemperature_ = temperature;
        data_.humidity_ = humidity;
        data_.smokeLevel_ = gas;
    }
    else if(numberOfCalls < 100)
    {
        numberOfCalls++;
    }
    else
    {
        numberOfCalls = 0;
    }
}

void DataProcessor::setLedsAndBuzzer()
{
    buzzer_.clear();
    leds_.reset();

    if(!data_.isDeviceProperlyAttached)
    {
        leds_.setLed(Leds::ELed_Pulse);
        leds_.setLed(Leds::ELed_OxygenLevel);
        leds_.setLed(Leds::ELed_BodyTemperature);
        leds_.setLed(Leds::ELed_SmokeLevel);
        leds_.setLed(Leds::ELed_AmbientTemperature);
    }
    else
    {
        if (data_.pulse_ < data_.getPulseMin() || data_.pulse_ > data_.getPulseMax() )
    {
        leds_.setLed(Leds::ELed_Pulse);
        buzzer_.addNoteFor(Buzzer::EBuzzType_Pulse);
    }
    if (data_.oxygenLevel_ < data_.getOxygenLevelMin())
    {
        leds_.setLed(Leds::ELed_OxygenLevel);
        buzzer_.addNoteFor(Buzzer::EBuzzType_OxygenLevel);
    }
    if (data_.bodyTemperature_ < data_.getBodyTempMin() || data_.bodyTemperature_ > data_.getBodyTempMax())
    {
        leds_.setLed(Leds::ELed_BodyTemperature);
        buzzer_.addNoteFor(Buzzer::EBuzzType_BodyTemperature);
    }
    if (data_.smokeLevel_ > data_.getSmokeLevelMax())
    {
        leds_.setLed(Leds::ELed_SmokeLevel);
        buzzer_.addNoteFor(Buzzer::EBuzzType_SmokeLevel);
    }
    if (data_.ambientTemperature_ < data_.getAmbientTempMin() || data_.ambientTemperature_ > data_.getAmbientTempMax())
    {
        leds_.setLed(Leds::ELed_AmbientTemperature);
        buzzer_.addNoteFor(Buzzer::EBuzzType_AmbientTemperature);
    }
        buzzer_.sing();
    }
}

void DataProcessor::btCommunication()
{
    int pulse = data_.pulse_;
    int oxygen = data_.oxygenLevel_;
    int bodyTemp = data_.bodyTemperature_;
    int co2 = data_.smokeLevel_;
    int humidity = data_.humidity_;
    int temp = data_.ambientTemperature_;

    char str[100];
    sprintf(str, "%d %d %d %d %d %d %d STOP",
        deviceId,
        pulse,
        oxygen,
        bodyTemp,
        co2,
        humidity,
        temp);
    bt_.communicate(str);
}
