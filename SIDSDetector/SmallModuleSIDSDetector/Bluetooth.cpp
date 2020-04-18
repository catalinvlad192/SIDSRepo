#include "Bluetooth.h"

Bluetooth::Bluetooth()
{}

void Bluetooth::communicate(char* string, char* problems)
{
    if (Serial.available() > 0)
    {
        while(Serial.available() > 0)
        {
            char t = Serial.read();
        }

        Serial.println("GARBAGE");
        Serial.println(string);
        Serial.println(problems);
        Serial.println("OVER");
    }
}
