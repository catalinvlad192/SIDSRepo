#include "Adafruit_BME680.h"

float bme680_temperatureMock = 26.13f;
float bme680_humidityMock = 65.45f;

Adafruit_BME680::Adafruit_BME680()
	: temperature(26.13f)
	, humidity(65.45f)
	, gas_resistance(321)
{
	temperature = bme680_temperatureMock;
	humidity = bme680_humidityMock;
}

bool Adafruit_BME680::begin(int address) { return true; }

void Adafruit_BME680::setTemperatureOversampling(int x){}
void Adafruit_BME680::setHumidityOversampling(int x){}
void Adafruit_BME680::setPressureOversampling(int x){}
void Adafruit_BME680::setIIRFilterSize(int x){}
void Adafruit_BME680::setGasHeater(int x, int y){}
void Adafruit_BME680::performReading(){}