#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_

#if defined(ARDUINO) && ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#include <inttypes.h>

class Bluetooth {
public:
    Bluetooth();
    void communicate(char* string);
    int getBabyAgeInMonths();

private:
    int monthsOfAge_;
};
#endif
