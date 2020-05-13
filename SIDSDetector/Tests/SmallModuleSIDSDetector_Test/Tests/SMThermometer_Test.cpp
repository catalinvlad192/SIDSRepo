#include "../../pch.h"
#include "../../SmallModuleSIDSDetector/Thermometer.h"
#include <math.h>

using namespace sm;

TEST(SMThermometer_Test, SmallModuleThermometerTest)
{
    Thermometer t(1);
    float temp = -5.0f;

    // Absolute 0,
    THERMOMETER_ANALOG_RETURN = 0;
    temp = t.getTemperature();
    temp = roundf(temp * 100) / 100;
    EXPECT_EQ(-273.15f, temp);

    // Should not crash to value < 0
    THERMOMETER_ANALOG_RETURN = -1;
    temp = t.getTemperature();
    temp = roundf(temp * 100) / 100;
    EXPECT_EQ(-273.15f, temp);

    THERMOMETER_ANALOG_RETURN = 1;
    temp = t.getTemperature();
    temp = roundf(temp * 100) / 100;
    EXPECT_EQ(-123.05f, temp);

    THERMOMETER_ANALOG_RETURN = 499;
    temp = t.getTemperature();
    temp = roundf(temp * 100) / 100;
    EXPECT_EQ(-27.52f, temp);

    THERMOMETER_ANALOG_RETURN = 500;
    temp = t.getTemperature();
    temp = roundf(temp * 100) / 100;
    EXPECT_EQ(-27.45f, temp);

    THERMOMETER_ANALOG_RETURN = 501;
    temp = t.getTemperature();
    temp = roundf(temp * 100) / 100;
    EXPECT_EQ(-27.37f, temp);

    THERMOMETER_ANALOG_RETURN = 511;
    temp = t.getTemperature();
    temp = roundf(temp * 100) / 100;
    EXPECT_EQ(-26.62f, temp);

    THERMOMETER_ANALOG_RETURN = 512;
    temp = t.getTemperature();
    temp = roundf(temp * 100) / 100;
    EXPECT_EQ(-26.54f, temp);

    THERMOMETER_ANALOG_RETURN = 513;
    temp = t.getTemperature();
    temp = roundf(temp * 100) / 100;
    EXPECT_EQ(-26.47f, temp);

    THERMOMETER_ANALOG_RETURN = 1022;
    temp = t.getTemperature();
    temp = roundf(temp * 100) / 100;
    EXPECT_EQ(198.81f, temp);

    THERMOMETER_ANALOG_RETURN = 1023;
    temp = t.getTemperature();
    temp = roundf(temp * 100) / 100;
    EXPECT_EQ(200.00f, temp);

    THERMOMETER_ANALOG_RETURN = 1024;
    temp = t.getTemperature();
    temp = roundf(temp * 100) / 100;
    EXPECT_EQ(200.00f, temp);
}