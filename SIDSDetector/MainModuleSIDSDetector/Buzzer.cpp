#include "Buzzer.h"

Buzzer::Buzzer(int buzzerPin) : buzzerPin_(buzzerPin), duration_(500)
{}

void Buzzer::sing()
{
    //Serial.println(buzzerPin_);
    //Serial.println(duration_);

    for (int thisNote = 0; thisNote < 5; thisNote++)
    {
        //Serial.println(melodyVec_[thisNote]);
        // pin8 output the voice, every scale is 0.5 sencond
        if(melodyVec_[thisNote] > 0)
        {
            tone(buzzerPin_, melodyVec_[thisNote], duration_);
        }
  }
}

void Buzzer::addNoteFor(EBuzzType type)
{
    //Serial.println(type);
    switch(type)
    {
        case EBuzzType_Pulse: { melodyVec_[0] = NOTE_C5; break; }
        case EBuzzType_OxygenLevel: { melodyVec_[1] = NOTE_D5; break; }
        case EBuzzType_BodyTemperature: { melodyVec_[2] = NOTE_E5; break; }
        case EBuzzType_SmokeLevel: { melodyVec_[3] = NOTE_F5; break; }
        case EBuzzType_AmbientTemperature: { melodyVec_[4] = NOTE_G5; break; }
        default: break;
    }
}

void Buzzer::clear()
{
    for(int i=0; i<5; i++)
    {
        melodyVec_[i] = -1;
    }
}
