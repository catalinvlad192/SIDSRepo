#include "../../pch.h"
#include "../../../MainModuleSIDSDetector/Bluetooth.h"
#include <string.h>

using namespace mm;

TEST(MMBluetooth_Test, ShouldSendStringAndAbnormalities)
{
    Serial2.reset();
    Serial3.reset();

    char inputString[1000];

    const char str1[] = "24813 120 89.23 36.54 4000 45.12 23.98 STOP";
    const char str2[] = "24999 140 85.23 37.54 5000 55.12 21.98 STOP";

    const char abn11[] = "P: 99, Ox: 85.02 T: 39.12";
    const char abn12[] = "P: 109, Ox: 84.02 T: 35.12";
    const char abn21[] = "P: 140, Ox: 99.02 T: 40.12";
    const char abn22[] = "P: 150, Ox: 70.02 T: 36.12";

    Bluetooth bt;
    
    bt.communicateApl(str1, abn11, abn12);
    Serial2.getInputString(inputString);
    EXPECT_EQ(0, strcmp(inputString,"GB\n24813 120 89.23 36.54 4000 45.12 23.98 STOP\nP: 99, Ox: 85.02 T: 39.12\nP: 109, Ox: 84.02 T: 35.12\nOVR\n"));

    Serial2.reset();

    bt.communicateApl(str2, abn21, abn22);
    Serial2.getInputString(inputString);
    EXPECT_EQ(0, strcmp(inputString, "GB\n24999 140 85.23 37.54 5000 55.12 21.98 STOP\nP: 140, Ox: 99.02 T: 40.12\nP: 150, Ox: 70.02 T: 36.12\nOVR\n"));

    Serial2.reset();
    Serial3.reset();
}

TEST(MMBluetooth_Test, ShouldReceiveAndProcessData)
{
    Serial2.reset();
    Serial3.reset();

    const char outputString[] = "SML\n150  97.30  37.52 0 STOP\nP: 90, Ox: 80.14%, T: 32.45\nOVR\n";
 
    int pulse;
    float ox;
    float temp;
    int removed;
    char problem[50];
    strcpy(problem, "");

    Bluetooth bt;
    Serial3.setOutputString(outputString);
    bt.communicateDev(&pulse, &ox, &temp, &removed, problem);
   
    EXPECT_EQ(150, pulse);
    EXPECT_EQ(97.3f, ox);
    EXPECT_EQ(37.52f, temp);
    EXPECT_EQ(0, removed);
    EXPECT_EQ(0, strcmp(problem, "P: 90, Ox: 80.14%, T: 32.45"));

    Serial2.reset();
    Serial3.reset();
}

TEST(MMBluetooth_Test, ShouldNotUpdateIfOutOfBoundaries)
{
    Serial2.reset();
    Serial3.reset();

    const char outputString1[] = "SML\n-1  40.22  -5.52 5 STOP\nP: 90, Ox: 80.14%, T: 32.45\nOVR\n";
    const char outputString2[] = "SML\n320  120.22  60.52 -4 STOP\nP: 90, Ox: 80.14%, T: 32.45\nOVR\n";
    const char outputString3[] = "SML\n150  97.30  37.52 0 STOP\nP: 90, Ox: 80.14%, T: 32.45\nOVR\n";

    int pulse = 0;
    float ox = 0.0f;
    float temp = 0.0f;
    int removed = 0;
    char problem[50];
    strcpy(problem, "");

    Bluetooth* bt = new Bluetooth();

    // 1 --------------------------------------------------------------------------------------------
    Serial3.setOutputString(outputString1);
    bt->communicateDev(&pulse, &ox, &temp, &removed, problem);

    EXPECT_EQ(0, pulse);
    EXPECT_EQ(0.0f, ox);
    EXPECT_EQ(0.0f, temp);
    EXPECT_EQ(0, removed);
    EXPECT_EQ(0, strcmp(problem, "P: 90, Ox: 80.14%, T: 32.45"));

    // 2 --------------------------------------------------------------------------------------------
    Serial3.reset();
    Serial3.setOutputString(outputString2);
    bt->communicateDev(&pulse, &ox, &temp, &removed, problem);

    EXPECT_EQ(0, pulse);
    EXPECT_EQ(0.0f, ox);
    EXPECT_EQ(0.0f, temp);
    EXPECT_EQ(0, removed);
    EXPECT_EQ(0, strcmp(problem, "P: 90, Ox: 80.14%, T: 32.45"));

    // 3 --------------------------------------------------------------------------------------------
    Serial3.reset();
    Serial3.setOutputString(outputString3);
    bt->communicateDev(&pulse, &ox, &temp, &removed, problem);

    EXPECT_EQ(150, pulse);
    EXPECT_EQ(97.3f, ox);
    EXPECT_EQ(37.52f, temp);
    EXPECT_EQ(0, removed);
    EXPECT_EQ(0, strcmp(problem, "P: 90, Ox: 80.14%, T: 32.45"));

    delete(bt);

    Serial2.reset();
    Serial3.reset();
}

TEST(MMBluetooth_Test, ShouldNotCrashIfMissingProblems)
{
    Serial2.reset();
    Serial3.reset();

    const char outputString[] = "SML\n150  97.30  37.52 0 STOP\nOVR\n";

    int pulse;
    float ox;
    float temp;
    int removed;
    char problem[50];
    strcpy(problem, "");

    Bluetooth bt;
    Serial3.setOutputString(outputString);
    bt.communicateDev(&pulse, &ox, &temp, &removed, problem);

    EXPECT_EQ(150, pulse);
    EXPECT_EQ(97.3f, ox);
    EXPECT_EQ(37.52f, temp);
    EXPECT_EQ(0, removed);
    EXPECT_EQ(0, strcmp(problem, ""));

    Serial2.reset();
    Serial3.reset();
}

TEST(MMBluetooth_Test, ShouldNotCrashIfMissingParameters)
{
    Serial2.reset();
    Serial3.reset();

    const char outputString1[] = "SML\n   97.30  37.52   STOP   \nP: 90, Ox: 80.14%, T: 32.45\nOVR\n";
    const char outputString2[] = "SML\nP: 90, Ox: 80.14%, T: 32.45\nOVR\n";

    // 1 --------------------------------------------------------------------------------------------
    int pulse = 0;
    float ox = 0.0f;
    float temp = 0.0f;
    int removed = 0;
    char problem[50];
    strcpy(problem, "");

    Bluetooth bt;

    Serial3.setOutputString(outputString1);
    bt.communicateDev(&pulse, &ox, &temp, &removed, problem);

    EXPECT_EQ(97, pulse);
    EXPECT_EQ(0.0f, ox);
    EXPECT_EQ(0.0f, temp);
    EXPECT_EQ(0, removed);
    EXPECT_EQ(0, strcmp(problem, "P: 90, Ox: 80.14%, T: 32.45"));

    // 2 --------------------------------------------------------------------------------------------
    pulse = 0;
    ox = 0.0f;
    temp = 0.0f;
    removed = 0;

    Serial3.reset();
    Serial3.setOutputString(outputString2);
    bt.communicateDev(&pulse, &ox, &temp, &removed, problem);

    EXPECT_EQ(0, pulse);
    EXPECT_EQ(90.0f, ox);
    EXPECT_EQ(0.0f, temp);
    EXPECT_EQ(0, removed);
    EXPECT_EQ(0, strcmp(problem, ""));

    Serial2.reset();
    Serial3.reset();
}

TEST(MMBluetooth_Test, ShouldNotCrashIfMissingHeadOrTrail)
{
    Serial2.reset();
    Serial3.reset();

    const char outputString1[] = "\n150  97.30  37.52 0 STOP\nP: 90, Ox: 80.14%, T: 32.45\nOVR\n";
    const char outputString2[] = "150  97.30  37.52 0\nP: 90, Ox: 80.14%, T: 32.45\nOVR\n";
    const char outputString3[] = "SML\n150  97.30  37.52 0 STOP\nP: 90, Ox: 80.14%, T: 32.45\n";
    const char outputString4[] = "SML\n150  97.30  37.52 0 STOP\nP: 90, Ox: 80.14%, T: 32.45\n\n";
    const char outputString5[] = "SML\n150  97.30  37.52 0 STOP\nP: 90, Ox: 80.14%, T: 32.45";
    const char outputString6[] = "150  97.30  37.52 0\nP: 90, Ox: 80.14%, T: 32.45";

    // 1 --------------------------------------------------------------------------------------------
    int pulse = 0;
    float ox = 0.0f;
    float temp = 0.0f;
    int removed = 0;
    char problem[50];
    strcpy(problem, "");

    Bluetooth bt;

    Serial3.setOutputString(outputString1);
    bt.communicateDev(&pulse, &ox, &temp, &removed, problem);

    EXPECT_EQ(0, pulse);
    EXPECT_EQ(0.0f, ox);
    EXPECT_EQ(0.0f, temp);
    EXPECT_EQ(0, removed);
    EXPECT_EQ(0, strcmp(problem, ""));

    // 2 --------------------------------------------------------------------------------------------
    pulse = 0;
    ox = 0.0f;
    temp = 0.0f;
    removed = 0;

    Serial3.reset();
    Serial3.setOutputString(outputString2);
    bt.communicateDev(&pulse, &ox, &temp, &removed, problem);

    EXPECT_EQ(0, pulse);
    EXPECT_EQ(0.0f, ox);
    EXPECT_EQ(0.0f, temp);
    EXPECT_EQ(0, removed);
    EXPECT_EQ(0, strcmp(problem, ""));

    // 3 --------------------------------------------------------------------------------------------
    pulse = 0;
    ox = 0.0f;
    temp = 0.0f;
    removed = 0;

    Serial3.reset();
    Serial3.setOutputString(outputString3);
    bt.communicateDev(&pulse, &ox, &temp, &removed, problem);

    EXPECT_EQ(0, pulse);
    EXPECT_EQ(0.0f, ox);
    EXPECT_EQ(0.0f, temp);
    EXPECT_EQ(0, removed);
    EXPECT_EQ(0, strcmp(problem, ""));

    // 4 --------------------------------------------------------------------------------------------
    pulse = 0;
    ox = 0.0f;
    temp = 0.0f;
    removed = 0;

    Serial3.reset();
    Serial3.setOutputString(outputString4);
    bt.communicateDev(&pulse, &ox, &temp, &removed, problem);

    EXPECT_EQ(0, pulse);
    EXPECT_EQ(0.0f, ox);
    EXPECT_EQ(0.0f, temp);
    EXPECT_EQ(0, removed);
    EXPECT_EQ(0, strcmp(problem, ""));

    // 5 --------------------------------------------------------------------------------------------
    pulse = 0;
    ox = 0.0f;
    temp = 0.0f;
    removed = 0;

    Serial3.reset();
    Serial3.setOutputString(outputString5);
    bt.communicateDev(&pulse, &ox, &temp, &removed, problem);

    EXPECT_EQ(0, pulse);
    EXPECT_EQ(0.0f, ox);
    EXPECT_EQ(0.0f, temp);
    EXPECT_EQ(0, removed);
    EXPECT_EQ(0, strcmp(problem, ""));

    // 6 --------------------------------------------------------------------------------------------
    pulse = 0;
    ox = 0.0f;
    temp = 0.0f;
    removed = 0;

    Serial3.reset();
    Serial3.setOutputString(outputString6);
    bt.communicateDev(&pulse, &ox, &temp, &removed, problem);

    EXPECT_EQ(0, pulse);
    EXPECT_EQ(0.0f, ox);
    EXPECT_EQ(0.0f, temp);
    EXPECT_EQ(0, removed);
    EXPECT_EQ(0, strcmp(problem, ""));

    Serial2.reset();
    Serial3.reset();
}

TEST(MMBluetooth_Test, ShouldNotCrashIfExtraInformationAvailable)
{
    Serial2.reset();
    Serial3.reset();

    const char outputString1[] = "SML\n150  97.30  ab 37.52 1 45   12 wwc STOP \nP: 90, Ox: 80.14%, T: 32.45\nOVR\n";
    const char outputString2[] = "zrtavawerSML\n150  97.30  37.52 1 STOP\nP: 90, Ox: 80.14%, T: 32.45\nOVR\ngdert\n";

    // 1 --------------------------------------------------------------------------------------------
    int pulse = 0;
    float ox = 0.0f;
    float temp = 0.0f;
    int removed = 0;
    char problem[50];
    strcpy(problem, "");

    Bluetooth bt;

    Serial3.setOutputString(outputString1);
    bt.communicateDev(&pulse, &ox, &temp, &removed, problem);

    EXPECT_EQ(150, pulse);
    EXPECT_EQ(97.3f, ox);
    EXPECT_EQ(0, temp);
    EXPECT_EQ(0, removed);
    EXPECT_EQ(0, strcmp(problem, "P: 90, Ox: 80.14%, T: 32.45"));

    // 2 --------------------------------------------------------------------------------------------
    pulse = 0;
    ox = 0.0f;
    temp = 0.0f;
    removed = 0;

    Serial3.reset();
    Serial3.setOutputString(outputString2);
    bt.communicateDev(&pulse, &ox, &temp, &removed, problem);

    EXPECT_EQ(150, pulse);
    EXPECT_EQ(97.3f, ox);
    EXPECT_EQ(37.52f, temp);
    EXPECT_EQ(1, removed);
    EXPECT_EQ(0, strcmp(problem, "P: 90, Ox: 80.14%, T: 32.45"));

    Serial2.reset();
    Serial3.reset();
}