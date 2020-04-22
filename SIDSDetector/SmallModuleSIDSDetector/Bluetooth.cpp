#include "Bluetooth.h"

Bluetooth::Bluetooth(int board_tx, int board_rx, int board_en, int board_vcc)
    : board_tx_(board_tx)
    , board_rx_(board_rx)
    , board_en_(board_en)
    , board_vcc_(board_vcc)
    , BTSerial_AT_(board_tx_, board_rx_)
{}

void Bluetooth::communicate(char* string, char* problems)
{
    connectAndReset();
    delay(1000);

    BTSerial_AT_.println("SML");
    BTSerial_AT_.println(string);
    BTSerial_AT_.println(problems);
    BTSerial_AT_.println("OVR");

    delay(1000);

    disconnectAndReset();
}

void Bluetooth::connectAndReset()
{
    Serial.println("connectAndReset");
    // Enter AT mode
    digitalWrite(board_vcc_, LOW);
    digitalWrite(board_en_, HIGH);
    delay(1000);
    digitalWrite(board_vcc_, HIGH);
    BTSerial_AT_ = SoftwareSerial(board_tx_, board_rx_);
    BTSerial_AT_.begin(38400);
    delay(1000);

    // Configure and connect
    BTSerial_AT_.print("AT+RMAAD\r\n"); // clear already connected devices
    delay(100);
    BTSerial_AT_.print("AT+CMODE=0\r\n"); // Connect to the specified device
    delay(100);
    BTSerial_AT_.print("AT+BIND=98d3,b1,fd4d2b\r\n"); // clear already connected devices
    delay(100);
    BTSerial_AT_.print("AT+RESET\r\n"); // clear already connected devices
    digitalWrite(board_en_, LOW);
    delay(100);
    BTSerial_AT_ = SoftwareSerial(board_rx_, board_tx_);
    BTSerial_AT_.begin(9600);
    delay(1000);
    Serial.println("connectAndReset-FIN");
}
void Bluetooth::disconnectAndReset()
{
    Serial.println("disconnectAndReset");
    // Enter AT mode
    digitalWrite(board_vcc_, LOW);
    digitalWrite(board_en_, HIGH);
    delay(1000);
    digitalWrite(board_vcc_, HIGH);
    BTSerial_AT_ = SoftwareSerial(board_tx_, board_rx_);
    BTSerial_AT_.begin(38400);
    delay(1000);

    // Configure and connect
    BTSerial_AT_.print("AT+RMAAD\r\n"); // clear already connected devices
    delay(100);
    BTSerial_AT_.print("AT+CMODE=1\r\n"); // Connect to the specified device
    delay(100);
    //BTSerial_AT_.print("AT+BIND=0000,00,000000\r\n"); // clear already connected devices
    //delay(100);
    BTSerial_AT_.print("AT+RESET\r\n"); // clear already connected devices
    digitalWrite(board_en_, LOW);
    delay(100);
    BTSerial_AT_ = SoftwareSerial(board_rx_, board_tx_);
    BTSerial_AT_.begin(9600);
    delay(1000);
    Serial.println("disconnectAndReset-FIN");
}
