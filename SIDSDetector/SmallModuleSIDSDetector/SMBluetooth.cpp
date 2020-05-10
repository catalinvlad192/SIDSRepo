#include "SMBluetooth.h"

namespace sm{
Bluetooth::Bluetooth(){}

void Bluetooth::communicate(const char* string, const char* problems)
{
    Serial.println("SML");
    Serial.println(string);
    Serial.println(problems);
    Serial.println("OVR");
}
} // namespace sm
