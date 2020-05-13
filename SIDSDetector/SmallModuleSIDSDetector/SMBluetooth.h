#ifndef SM_BLUETOOTH_H_
#define SM_BLUETOOTH_H_

#if defined(ARDUINO) && ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#include <inttypes.h>

namespace sm{
class Bluetooth
{
public:
    Bluetooth();
    void communicate(const char* string, const char problems[50]);
};
} // namespace sm
#endif  // BLUETOOTH_H_
