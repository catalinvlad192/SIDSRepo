#include "../../pch.h"
#include "../../MainModuleSIDSDetector/Leds.h"

using namespace mm;

const int PULSE_PIN = 1;
const int OX_PIN = 2;
const int BTEMP_PIN = 3;
const int HUM_PIN = 4;
const int ATEMP_PIN = 5;

TEST(MMLeds_Test, LedsTest)
{
    strcpy(DIGITALWRITE_LAST_SET_PINS, "");
    strcpy(DIGITALWRITE_LAST_SET_VALUES, "");

    Leds l(1, 2, 3, 4, 5);

    l.setLed(Leds::ELed_Pulse);
    EXPECT_EQ(0, strcmp(DIGITALWRITE_LAST_SET_PINS, "1 "));
    EXPECT_EQ(0, strcmp(DIGITALWRITE_LAST_SET_VALUES, "1 "));

    strcpy(DIGITALWRITE_LAST_SET_PINS, "");
    strcpy(DIGITALWRITE_LAST_SET_VALUES, "");
    l.setLed(Leds::ELed_OxygenLevel);
    EXPECT_EQ(0, strcmp(DIGITALWRITE_LAST_SET_PINS, "2 "));
    EXPECT_EQ(0, strcmp(DIGITALWRITE_LAST_SET_VALUES, "1 "));

    strcpy(DIGITALWRITE_LAST_SET_PINS, "");
    strcpy(DIGITALWRITE_LAST_SET_VALUES, "");
    l.setLed(Leds::ELed_BodyTemperature);
    EXPECT_EQ(0, strcmp(DIGITALWRITE_LAST_SET_PINS, "3 "));
    EXPECT_EQ(0, strcmp(DIGITALWRITE_LAST_SET_VALUES, "1 "));

    strcpy(DIGITALWRITE_LAST_SET_PINS, "");
    strcpy(DIGITALWRITE_LAST_SET_VALUES, "");
    l.setLed(Leds::ELed_Humidity);
    EXPECT_EQ(0, strcmp(DIGITALWRITE_LAST_SET_PINS, "4 "));
    EXPECT_EQ(0, strcmp(DIGITALWRITE_LAST_SET_VALUES, "1 "));

    strcpy(DIGITALWRITE_LAST_SET_PINS, "");
    strcpy(DIGITALWRITE_LAST_SET_VALUES, "");
    l.setLed(Leds::ELed_AmbientTemperature);
    EXPECT_EQ(0, strcmp(DIGITALWRITE_LAST_SET_PINS, "5 "));
    EXPECT_EQ(0, strcmp(DIGITALWRITE_LAST_SET_VALUES, "1 "));

    strcpy(DIGITALWRITE_LAST_SET_PINS, "");
    strcpy(DIGITALWRITE_LAST_SET_VALUES, "");
    l.setLed(Leds::ELed_AmbientTemperature);
    EXPECT_EQ(0, strcmp(DIGITALWRITE_LAST_SET_PINS, "5 "));
    EXPECT_EQ(0, strcmp(DIGITALWRITE_LAST_SET_VALUES, "1 "));

    strcpy(DIGITALWRITE_LAST_SET_PINS, "");
    strcpy(DIGITALWRITE_LAST_SET_VALUES, "");
    l.reset();
    EXPECT_EQ(0, strcmp(DIGITALWRITE_LAST_SET_PINS, "1 2 3 4 5 "));
    EXPECT_EQ(0, strcmp(DIGITALWRITE_LAST_SET_VALUES, "0 0 0 0 0 "));

    strcpy(DIGITALWRITE_LAST_SET_PINS, "");
    strcpy(DIGITALWRITE_LAST_SET_VALUES, "");
}