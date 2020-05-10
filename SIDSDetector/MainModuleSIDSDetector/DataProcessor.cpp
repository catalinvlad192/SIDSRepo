#include "DataProcessor.h"
#include "Buzzer.h"
#include "Leds.h"
#include "SensorData.h"

#include <string.h>

#define deviceId 24813

namespace mm{
DataProcessor::DataProcessor(int buzzerPin, int pulseLed, int oxygenLed, int bodyTemperatureLed, int humidityLed, int ambientTemperatureLed)
    : data_(SensorData(3))
    , buzzer_(Buzzer(buzzerPin))
    , leds_(Leds(pulseLed, oxygenLed, bodyTemperatureLed, humidityLed, ambientTemperatureLed))
{
    isBmeOk_ = true;
    if (!bme_.begin(0x76)) {
        Serial.println("Could not find a valid BME680 sensor, check wiring!");
        isBmeOk_ = false;
        delay(50);
    }
    //if (isBmeOk_)
    //{
        // Set up oversampling and filter initialization
        bme_.setTemperatureOversampling(BME680_OS_8X);
        bme_.setHumidityOversampling(BME680_OS_2X);
        bme_.setPressureOversampling(BME680_OS_4X);
        bme_.setIIRFilterSize(BME680_FILTER_SIZE_3);
        bme_.setGasHeater(320, 150); // 320*C for 150 ms

        bme_.performReading();
    //}
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

        Serial.print("Temperature ");
        Serial.println(data_.ambientTemperature_);
        Serial.print("Humidity ");
        Serial.println(data_.humidity_);
        Serial.print("Gas ");
        Serial.println(data_.smokeLevel_);

        delay(50);

    }
    else if (numberOfCalls < 100)
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

    if (data_.isDeviceRemoved_)
    {
        leds_.setLed(Leds::ELed_Pulse);
        leds_.setLed(Leds::ELed_OxygenLevel);
        leds_.setLed(Leds::ELed_BodyTemperature);
        leds_.setLed(Leds::ELed_Humidity);
        leds_.setLed(Leds::ELed_AmbientTemperature);
    }
    else
    {
        // Blue
        if (data_.pulse_ < data_.getPulseMin() || data_.pulse_ > data_.getPulseMax() )
        {
            leds_.setLed(Leds::ELed_Pulse);
            buzzer_.addNoteFor(Buzzer::EBuzzType_Pulse);
        }
        // Red
        if (data_.oxygenLevel_ < data_.OXYGENLEVEL_MIN)
        {
            leds_.setLed(Leds::ELed_OxygenLevel);
            buzzer_.addNoteFor(Buzzer::EBuzzType_OxygenLevel);
        }
        // Yellow
        if (data_.bodyTemperature_ < data_.BODYTEMP_MIN || data_.bodyTemperature_ > data_.BODYTEMP_MAX)
        {
            leds_.setLed(Leds::ELed_BodyTemperature);
            buzzer_.addNoteFor(Buzzer::EBuzzType_BodyTemperature);
        }
        // Green
        if (data_.humidity_ < data_.HUMIDITY_MIN || data_.humidity_ > data_.HUMIDITY_MAX)
        {
            leds_.setLed(Leds::ELed_Humidity);
            buzzer_.addNoteFor(Buzzer::EBuzzType_Humidity);
        }
        // White
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
    if (Serial2.available() > 0)
    {
        int gb = Serial2.read(); // garbage
        int mths = Serial2.read();

        while (Serial2.available() > 0)
        {
            char ch = Serial2.read();
        }

        // aplication
        data_.setMonths(mths);

        int co2 = data_.smokeLevel_;

        char oxygenStr[7];
        dtostrf(data_.oxygenLevel_, 3, 2, oxygenStr);

        char bodyTempStr[7];
        dtostrf(data_.bodyTemperature_, 3, 2, bodyTempStr);


        char humidityStr[7];
        dtostrf(data_.humidity_, 3, 2, humidityStr);

        char ambTempStr[7];
        dtostrf(data_.ambientTemperature_, 3, 2, ambTempStr);

        char str[100];
        sprintf(str, "%d %d %5s %5s %d %5s %5s STOP",
            deviceId,
            data_.pulse_,
            oxygenStr,
            bodyTempStr,
            co2,
            humidityStr,
            ambTempStr);

        bt_.communicateApl(str, data_.abnormalities_[0], data_.abnormalities_[1]);
        delay(50);
    }
    delay(50);
    if (Serial3.available() > 0)
    {
        delay(10);
        char prob[50];
        strcpy(prob, "-");
        delay(50);
        bt_.communicateDev(
            &(data_.pulse_),
            &(data_.oxygenLevel_),
            &(data_.bodyTemperature_),
            &(data_.isDeviceRemoved_),
            prob);

        data_.addAbnormality(prob);

        delay(50);
    }
}
} // namespace mm
