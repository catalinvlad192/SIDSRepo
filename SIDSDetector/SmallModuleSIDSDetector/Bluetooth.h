#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_

#if defined(ARDUINO) && ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#include <inttypes.h>
#include <SoftwareSerial.h>

class Bluetooth
{
public:
    Bluetooth(int board_tx, int board_rx, int board_en, int board_vcc);
    void communicate(char* string, char* problems);
private:
    void connectAndReset();
    void disconnectAndReset();

    int board_tx_;
    int board_rx_;
    int board_en_;
    int board_vcc_;
    SoftwareSerial BTSerial_AT_;
};

#endif  // BLUETOOTH_H_
