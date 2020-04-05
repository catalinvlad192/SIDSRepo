#include "Bluetooth.h"

Bluetooth::Bluetooth() : monthsOfAge_(0)
{}

void Bluetooth::communicate(char* string)
{
    if (Serial.available() > 0)
    {
        while(Serial.available() > 0)
        {
            char t = Serial.read();
        }

        int months = Serial.read();
        if(months >= 0 && months <=12)
        {
            monthsOfAge_ = months;
        }

        Serial.println("GARBAGE");
        Serial.println(string);
        Serial.println("P: 100, T: 37.9, Ox: 85%");
        Serial.println("OVER");
    }
}

int Bluetooth::getBabyAgeInMonths()
{
    return monthsOfAge_;
}
