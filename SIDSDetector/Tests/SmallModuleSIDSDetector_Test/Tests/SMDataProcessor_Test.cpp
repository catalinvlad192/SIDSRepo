#include "../../pch.h"
#include "../../SmallModuleSIDSDetector/SMDataProcessor.h"

using namespace sm;

TEST(SMDataProcessor_Test, ShouldSendDataFurther)
{
    int pulse = 120;

    Serial.reset();
    DataProcessor dp(1);
    char inputString[1000];
    THERMOMETER_ANALOG_RETURN = 963;
    dp.setPulseOx(pulse, 95.34f);

    for (int i = 0; i < 2005; i++)
    {
        if(pulse == 121)
            dp.setPulseOx(--pulse, 95.34f);
        else
            dp.setPulseOx(++pulse, 95.34f);
        dp.tick();
    }

    Serial.getInputString(inputString);
    EXPECT_EQ(0, strcmp(inputString, "SML\n120 95.34 37.22 0 STOP\n\nOVR\n"));

    Serial.reset();
}

TEST(SMDataProcessor_Test, ShouldNoticeIfDeviceWasRemoved)
{
    int pulse = 120;

    Serial.reset();
    DataProcessor dp(1);
    char inputString[1000];
    THERMOMETER_ANALOG_RETURN = 963;
    dp.setPulseOx(pulse, 95.34f);

    for (int i = 0; i < 2005; i++)
    {
        if (pulse == 121)
            dp.setPulseOx(--pulse, 95.34f);
        else
            dp.setPulseOx(++pulse, 95.34f);
        dp.tick();
    }
    Serial.getInputString(inputString);
    EXPECT_EQ(0, strcmp(inputString, "SML\n120 95.34 37.22 0 STOP\n\nOVR\n"));

    Serial.reset();
    pulse = 40;
    THERMOMETER_ANALOG_RETURN = 863;
    for (int i = 0; i < 2005; i++)
    {
        if (pulse == 40)
            dp.setPulseOx(--pulse, 95.34f);
        else
            dp.setPulseOx(++pulse, 95.34f);
        dp.tick();
    }
    Serial.getInputString(inputString);
    EXPECT_EQ(0, strcmp(inputString, "SML\n39 95.34  9.47 1 STOP\n\nOVR\n"));

    Serial.reset();
    pulse = 40;
    THERMOMETER_ANALOG_RETURN = 863;
    for (int i = 0; i < 2005; i++)
    {
        if (pulse == 40)
            dp.setPulseOx(--pulse, 95.34f);
        else
            dp.setPulseOx(++pulse, 95.34f);
        dp.tick();
    }
    Serial.getInputString(inputString);
    EXPECT_EQ(0, strcmp(inputString, "SML\n39 95.34  9.47 1 STOP\n\nOVR\n"));

    Serial.reset();
    pulse = 120;
    THERMOMETER_ANALOG_RETURN = 963;
    for (int i = 0; i < 2005; i++)
    {
        if (pulse == 120)
            dp.setPulseOx(--pulse, 95.34f);
        else
            dp.setPulseOx(++pulse, 95.34f);
        dp.tick();
    }
    Serial.getInputString(inputString);
    EXPECT_EQ(0, strcmp(inputString, "SML\n119 95.34 37.22 1 STOP\n\nOVR\n"));

    Serial.reset();
    pulse = 120;
    THERMOMETER_ANALOG_RETURN = 963;
    for (int i = 0; i < 2005; i++)
    {
        if (pulse == 120)
            dp.setPulseOx(--pulse, 95.34f);
        else
            dp.setPulseOx(++pulse, 95.34f);
        dp.tick();
    }
    Serial.getInputString(inputString);
    EXPECT_EQ(0, strcmp(inputString, "SML\n119 95.34 37.22 0 STOP\n\nOVR\n"));

    Serial.reset();
}

TEST(SMDataProcessor_Test, ShouldNoticeAProblemAndSendItFurther)
{
    int pulse = 120;

    Serial.reset();
    DataProcessor dp(1);
    char inputString[1000];
    THERMOMETER_ANALOG_RETURN = 963;
    dp.setPulseOx(pulse, 95.34f);

    for (int i = 0; i < 2005; i++)
    {
        if (pulse == 121)
            dp.setPulseOx(--pulse, 95.34f);
        else
            dp.setPulseOx(++pulse, 95.34f);
        dp.tick();
    }
    Serial.getInputString(inputString);
    EXPECT_EQ(0, strcmp(inputString, "SML\n120 95.34 37.22 0 STOP\n\nOVR\n"));

    Serial.reset();
    pulse = 40;
    THERMOMETER_ANALOG_RETURN = 963;
    for (int i = 0; i < 2005; i++)
    {
        if (pulse == 40)
            dp.setPulseOx(--pulse, 95.34f);
        else
            dp.setPulseOx(++pulse, 95.34f);
        dp.tick();
    }
    Serial.getInputString(inputString);
    EXPECT_EQ(0, strcmp(inputString, "SML\n39 95.34 37.22 0 STOP\nP: 39, Ox: 95.34, T: 37.22\nOVR\n"));

    Serial.reset();
    pulse = 120;
    THERMOMETER_ANALOG_RETURN = 963;
    for (int i = 0; i < 2005; i++)
    {
        if (pulse == 120)
            dp.setPulseOx(--pulse, 95.34f);
        else
            dp.setPulseOx(++pulse, 95.34f);
        dp.tick();
    }
    Serial.getInputString(inputString);
    EXPECT_EQ(0, strcmp(inputString, "SML\n119 95.34 37.22 0 STOP\n\nOVR\n"));

    Serial.reset();
    pulse = 120;
    THERMOMETER_ANALOG_RETURN = 863;
    for (int i = 0; i < 2005; i++)
    {
        if (pulse == 120)
            dp.setPulseOx(--pulse, 95.34f);
        else
            dp.setPulseOx(++pulse, 95.34f);
        dp.tick();
    }
    Serial.getInputString(inputString);
    EXPECT_EQ(0, strcmp(inputString, "SML\n119 95.34  9.47 0 STOP\nP: 119, Ox: 95.34, T:  9.47\nOVR\n"));

    Serial.reset();
}

TEST(SMDataProcessor_Test, IfNoChangeInPulseShouldNotBeTakenInConsideration)
{
    int pulse = 120;

    Serial.reset();
    DataProcessor dp(1);
    char inputString[1000];
    THERMOMETER_ANALOG_RETURN = 963;
    dp.setPulseOx(pulse, 95.34f);

    for (int i = 0; i < 2005; i++)
    {
        dp.tick();
    }
    Serial.getInputString(inputString);
    EXPECT_EQ(0, strcmp(inputString, "SML\n119 95.34 37.22 0 STOP\n\nOVR\n"));

    Serial.reset();
}