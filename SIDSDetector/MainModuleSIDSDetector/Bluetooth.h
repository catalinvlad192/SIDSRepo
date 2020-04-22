#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_

#if defined(ARDUINO) && ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#include <inttypes.h>
#include <string.h>

class Bluetooth {
public:
    Bluetooth();
    void communicateApl(char* string, char* abnormality1, char* abnormality2) const;
    void communicateDev(int* pulse, float* ox, float* temp, int* rem, char* prob) const;
};
#endif
