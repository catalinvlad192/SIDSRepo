#include "../../pch.h"
#include "../../MainModuleSIDSDetector/DataProcessor.h"

using namespace mm;

TEST(MMDataProcessor_Test, ModuleTest)
{
    char inputString[1000];
    const char smth[] = "smth";
    const char outputString1[] = "SML\n150  97.30  37.52 0\nP: 90, Ox: 80.14%, T: 32.45\nOVR\n";
    const char outputString2[] = "SML\n160  99.30  38.52 0\nP: 190, Ox: 99.14%, T: 39.45\nOVR\n";
    const char outputString3[] = "SML\n190  80.30  40.52 0\nP: 200, Ox: 99.14%, T: 49.45\nOVR\n";

    Serial2.reset();
    Serial3.reset();

    bme680_temperatureMock = 26.13f;
    bme680_humidityMock = 65.45f;

    DataProcessor data(0, 1, 2, 3, 4, 5);

    Serial2.setOutputString(smth);
    Serial3.setOutputString(outputString1);
    data.tick();
    Serial2.getInputString(inputString);

    EXPECT_EQ(0, strcmp(DIGITALWRITE_LAST_SET_PINS, "1 2 3 4 5 4 "));
    EXPECT_EQ(0, strcmp(DIGITALWRITE_LAST_SET_VALUES, "0 0 0 0 0 1 "));
    EXPECT_EQ(0, strcmp(TONE_LAST_NOTE_CALL, ""));
    EXPECT_EQ(0, strcmp(inputString, "GB\n24813 140 99.00 37.00 321 65.45 22.13 0 STOP\n\n\nOVR\n"));

    strcpy(DIGITALWRITE_LAST_SET_PINS, "");
    strcpy(DIGITALWRITE_LAST_SET_VALUES, "");
    strcpy(TONE_LAST_NOTE_CALL, "");
    Serial2.reset();
    Serial3.reset();

    Serial2.setOutputString(smth);
    Serial3.setOutputString(outputString2);
    data.tick();
    Serial2.getInputString(inputString);

    EXPECT_EQ(0, strcmp(DIGITALWRITE_LAST_SET_PINS, "1 2 3 4 5 4 "));
    EXPECT_EQ(0, strcmp(DIGITALWRITE_LAST_SET_VALUES, "0 0 0 0 0 1 "));
    EXPECT_EQ(0, strcmp(TONE_LAST_NOTE_CALL, ""));
    EXPECT_EQ(0, strcmp(inputString, "GB\n24813 150 97.30 37.52 321 65.45 22.13 0 STOP\nP: 90, Ox: 80.14%, T: 32.45\n\nOVR\n"));

    strcpy(DIGITALWRITE_LAST_SET_PINS, "");
    strcpy(DIGITALWRITE_LAST_SET_VALUES, "");
    strcpy(TONE_LAST_NOTE_CALL, "");
    Serial2.reset();
    Serial3.reset();

    Serial2.setOutputString(smth);
    Serial3.setOutputString(outputString3);
    data.tick();
    Serial2.getInputString(inputString);

    EXPECT_EQ(0, strcmp(DIGITALWRITE_LAST_SET_PINS, "1 2 3 4 5 3 4 "));
    EXPECT_EQ(0, strcmp(DIGITALWRITE_LAST_SET_VALUES, "0 0 0 0 0 1 1 "));
    EXPECT_EQ(0, strcmp(TONE_LAST_NOTE_CALL, "659 "));
    EXPECT_EQ(0, strcmp(inputString, "GB\n24813 160 99.30 38.52 321 65.45 22.13 0 STOP\nP: 90, Ox: 80.14%, T: 32.45\nP: 190, Ox: 99.14%, T: 39.45\nOVR\n"));

    strcpy(DIGITALWRITE_LAST_SET_PINS, "");
    strcpy(DIGITALWRITE_LAST_SET_VALUES, "");
    strcpy(TONE_LAST_NOTE_CALL, "");
    Serial2.reset();
    Serial3.reset();

    Serial2.setOutputString(smth);
    data.tick();
    Serial2.getInputString(inputString);

    EXPECT_EQ(0, strcmp(DIGITALWRITE_LAST_SET_PINS, "1 2 3 4 5 1 2 3 4 "));
    EXPECT_EQ(0, strcmp(DIGITALWRITE_LAST_SET_VALUES, "0 0 0 0 0 1 1 1 1 "));
    EXPECT_EQ(0, strcmp(TONE_LAST_NOTE_CALL, "523 587 659 "));
    EXPECT_EQ(0, strcmp(inputString, "GB\n24813 190 80.30 40.52 321 65.45 22.13 0 STOP\nP: 200, Ox: 99.14%, T: 49.45\nP: 190, Ox: 99.14%, T: 39.45\nOVR\n"));

    Serial2.reset();
    Serial3.reset();
}