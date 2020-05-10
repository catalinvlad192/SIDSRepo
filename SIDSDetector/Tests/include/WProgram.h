#ifndef MY_WPROGRAM_H_
#define MY_WPROGRAM_H_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>

// Serial for bluetooth ---------------------------------------------------------------------------
class SerialMock
{
public:
	SerialMock();
	int println(const char* str);
	int println(float f);
	int print(const char* str);
	int print(float f);
	int available();
	char read();
	void setOutputString(const char outStr[500]);
	void getInputString(char intStr[500]);

	void reset();

private:
	char inputStr_[1000];
	char outputStr_[1000];
};

extern SerialMock Serial;
extern SerialMock Serial2;
extern SerialMock Serial3;
// Serial for bluetooth ---------------------------------------------------------------------------

// Tone for Buzzer --------------------------------------------------------------------------------
extern char TONE_LAST_NOTE_CALL[50];
void tone(int buzzerPin, int note, int duration);
// Tone for Buzzer --------------------------------------------------------------------------------

// Leds -------------------------------------------------------------------------------------------
extern const int HIGH;
extern const int LOW;
extern char DIGITALWRITE_LAST_SET_PINS[50];
extern char DIGITALWRITE_LAST_SET_VALUES[50];
void digitalWrite(int pin, int value);
// Leds -------------------------------------------------------------------------------------------

// DataProcessor -------------------------------------------------------------------------------------------
void delay(int d);
// DataProcessor -------------------------------------------------------------------------------------------

// Thermometer ---------------------------------------------------------------------------------------------
extern int THERMOMETER_ANALOG_RETURN;
int analogRead(int pin);
// Thermometer ---------------------------------------------------------------------------------------------

void dtostrf(float f, int x, int y, char* str);
#endif // MY_WPROGRAM_H_