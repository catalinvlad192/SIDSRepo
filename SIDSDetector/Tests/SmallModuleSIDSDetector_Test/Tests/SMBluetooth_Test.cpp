#include "../../pch.h"
#include "../../SmallModuleSIDSDetector/SMBluetooth.h"

using namespace sm;

TEST(SMBluetooth_Test, SmallModuleBluetoothTest)
{
    Bluetooth bt;
    Serial.reset();

    //const char string[] = "SML\n150  97.30  37.52 0 STOP\nP: 90, Ox: 80.14%, T: 32.45\nOVR\n";
    const char string[] = "150  97.30  37.52 0 STOP";
    const char problem[] = "P: 90, Ox: 80.14%, T: 32.45";
    char inputString[1000];

    bt.communicate(string, problem);
    Serial.getInputString(inputString);
    EXPECT_EQ(0, strcmp(inputString, "SML\n150  97.30  37.52 0 STOP\nP: 90, Ox: 80.14%, T: 32.45\nOVR\n"));

    Serial.reset();
}