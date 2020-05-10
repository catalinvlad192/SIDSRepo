#include "WProgram.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// Serial for bluetooth ---------------------------------------------------------------------------
SerialMock::SerialMock()
{
	strcpy(inputStr_, "");
	strcpy(outputStr_, "");
}
int SerialMock::println(const char* str)
{
	strcat(inputStr_, str);
	strcat(inputStr_, "\n");
	return strlen(str);
}
int SerialMock::println(float f)
{
	// float to string then print concat to inputStr_
	char sf[10];
	strcpy(sf, "");
	sprintf(sf, "%.2f", f);
	strcat(inputStr_, sf);
	strcat(inputStr_, "\n");
	return 1;
}
int SerialMock::print(const char* str)
{
	strcat(inputStr_, str);
	return strlen(str);
}

int SerialMock::print(float f)
{
	// float to string then print concat to inputStr_
	char sf[10];
	sprintf(sf, "%.2f", f);
	strcat(inputStr_, sf);
	return 1;
}
int SerialMock::available()
{
	if (strcmp(outputStr_, "") != 0)
		return 1;
	return 0;
}
char SerialMock::read()
{
	char x = outputStr_[0];
	strcpy(outputStr_, outputStr_ + 1);
	return x;
}
void SerialMock::setOutputString(const char outStr[500])
{
	strcpy(outputStr_, outStr);
}
void SerialMock::getInputString(char intStr[500])
{
	strcpy(intStr, inputStr_);
}

void SerialMock::reset()
{
	strcpy(inputStr_, "");
	strcpy(outputStr_, "");
}
SerialMock Serial;
SerialMock Serial2;
SerialMock Serial3;
// Serial for bluetooth ---------------------------------------------------------------------------

// Tone for Buzzer --------------------------------------------------------------------------------
char TONE_LAST_NOTE_CALL[50] = "";
void tone(int buzzerPin, int note, int duration)
{
	char n[5];
	sprintf(n, "%d", note);
	
	strcat(TONE_LAST_NOTE_CALL, n);
	strcat(TONE_LAST_NOTE_CALL, " ");
}
// Tone for Buzzer --------------------------------------------------------------------------------

// Leds -------------------------------------------------------------------------------------------
const int HIGH = 1;
const int LOW = 0;
char DIGITALWRITE_LAST_SET_PINS[50] = "";
char DIGITALWRITE_LAST_SET_VALUES[50] = "";
void digitalWrite(int pin, int value)
{
	char p[5];
	char v[5];
	sprintf(p, "%d", pin);
	sprintf(v, "%d", value);

	strcat(DIGITALWRITE_LAST_SET_PINS, p);
	strcat(DIGITALWRITE_LAST_SET_VALUES, v);
	strcat(DIGITALWRITE_LAST_SET_PINS, " ");
	strcat(DIGITALWRITE_LAST_SET_VALUES, " ");
}
// Leds -------------------------------------------------------------------------------------------

// DataProcessor -------------------------------------------------------------------------------------------
void delay(int d)
{}
// DataProcessor -------------------------------------------------------------------------------------------

// Thermometer ---------------------------------------------------------------------------------------------
int THERMOMETER_ANALOG_RETURN = 500;
int analogRead(int pin)
{
	// To be implemented
	return THERMOMETER_ANALOG_RETURN;
}
// Thermometer ---------------------------------------------------------------------------------------------

void dtostrf(float f, int x, int y, char* str)
{
	// float to string then print concat to inputStr_
	char sf[10];
	sprintf(sf, "%.2f", f);
	strcpy(str, sf);
}