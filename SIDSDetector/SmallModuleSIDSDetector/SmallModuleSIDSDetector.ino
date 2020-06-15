#include "SMDataProcessor.h"

using namespace sm;

const int tempPin = A0;
const int pulsePin = A2;
const int ledPin = 13;


DataProcessor proc(tempPin);

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    proc.tick();
}
