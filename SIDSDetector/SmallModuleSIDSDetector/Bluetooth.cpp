#include "Bluetooth.h"

Bluetooth::Bluetooth()
{}

void Bluetooth::communicate(char* string)
{
    if (Serial.available() > 0)
    {
        while(Serial.available() > 0)
        {
            char t = Serial.read();
        }

        Serial.println("GARBAGE");
        Serial.println(string);
        Serial.println("P: 100, T: 37.9, Ox: 85%");
        Serial.println("OVER");
    }
}
