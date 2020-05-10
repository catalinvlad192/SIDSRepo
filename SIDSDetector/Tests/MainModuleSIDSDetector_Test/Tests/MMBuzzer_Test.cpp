#include "../../pch.h"
#include "../../../MainModuleSIDSDetector/Buzzer.h"
#include <string.h>

using namespace mm;

TEST(MMBuzzer_Test, ShouldSingOnlyForAddedNotes)
{
    strcpy(TONE_LAST_NOTE_CALL, "");
    Buzzer buzzer(1);

    buzzer.sing();
    EXPECT_EQ(0, strcmp(TONE_LAST_NOTE_CALL, ""));

    buzzer.addNoteFor(Buzzer::EBuzzType_AmbientTemperature);
    buzzer.sing();
    EXPECT_EQ(0, strcmp(TONE_LAST_NOTE_CALL, "784 "));

    strcpy(TONE_LAST_NOTE_CALL, "");
    buzzer.addNoteFor(Buzzer::EBuzzType_BodyTemperature);
    buzzer.sing();
    EXPECT_EQ(0, strcmp(TONE_LAST_NOTE_CALL, "659 784 "));

    strcpy(TONE_LAST_NOTE_CALL, "");
    buzzer.addNoteFor(Buzzer::EBuzzType_Pulse);
    buzzer.sing();
    EXPECT_EQ(0, strcmp(TONE_LAST_NOTE_CALL, "523 659 784 "));

    strcpy(TONE_LAST_NOTE_CALL, "");
    buzzer.addNoteFor(Buzzer::EBuzzType_Humidity);
    buzzer.sing();
    EXPECT_EQ(0, strcmp(TONE_LAST_NOTE_CALL, "523 659 698 784 "));

    strcpy(TONE_LAST_NOTE_CALL, "");
    buzzer.addNoteFor(Buzzer::EBuzzType_OxygenLevel);
    buzzer.sing();
    EXPECT_EQ(0, strcmp(TONE_LAST_NOTE_CALL, "523 587 659 698 784 "));

    strcpy(TONE_LAST_NOTE_CALL, "");
    buzzer.addNoteFor(Buzzer::EBuzzType_Pulse);
    buzzer.addNoteFor(Buzzer::EBuzzType_OxygenLevel);
    buzzer.addNoteFor(Buzzer::EBuzzType_BodyTemperature);
    buzzer.addNoteFor(Buzzer::EBuzzType_Humidity);
    buzzer.addNoteFor(Buzzer::EBuzzType_AmbientTemperature);
    buzzer.sing();
    EXPECT_EQ(0, strcmp(TONE_LAST_NOTE_CALL, "523 587 659 698 784 "));

    strcpy(TONE_LAST_NOTE_CALL, "");
    buzzer.clear();
    buzzer.sing();
    EXPECT_EQ(0, strcmp(TONE_LAST_NOTE_CALL, ""));

    strcpy(TONE_LAST_NOTE_CALL, "");
}