#ifndef MM_BUZZER_H_
#define MM_BUZZER_H_

#define NOTE_C5 523
#define NOTE_D5 587
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_G5 784

#if defined(ARDUINO) && ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#include <inttypes.h>

namespace mm{
class Buzzer {
public:

    enum EBuzzType
    {
        EBuzzType_Pulse = 0,
        EBuzzType_OxygenLevel,
        EBuzzType_BodyTemperature,
        EBuzzType_Humidity,
        EBuzzType_AmbientTemperature
    };

    Buzzer(int buzzerPin);
    void sing();
    void clear();
    void addNoteFor(EBuzzType type);

private:
    int buzzerPin_;

    //Notes in the melody:
    int melodyVec_[5] = {-1, -1, -1, -1, -1};
    int duration_ = 500;  // 200 miliseconds
};
} // namespace mm
#endif
