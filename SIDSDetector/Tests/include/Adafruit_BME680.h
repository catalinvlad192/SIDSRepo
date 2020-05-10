#ifndef ADAFRUIT_BME680_H_
#define ADAFRUIT_BME680_H_

#define BME680_OS_8X 8
#define BME680_OS_2X 2
#define BME680_OS_4X 4
#define BME680_FILTER_SIZE_3 3

extern float bme680_temperatureMock;
extern float bme680_humidityMock;

class Adafruit_BME680
{
public:
	Adafruit_BME680();

	bool begin(int address);

	void setTemperatureOversampling(int x);
	void setHumidityOversampling(int x);
	void setPressureOversampling(int x);
	void setIIRFilterSize(int x);
	void setGasHeater(int x, int y);
	void performReading();

	float temperature;
	float humidity;
	int gas_resistance;
};

#endif