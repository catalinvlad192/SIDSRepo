#include "DataProcessor.h"

const int tempPin = A0;
const int pulsePin = A2;
const int ledPin = 13;

const int BOARD_TX = 10;
const int BOARD_RX = 9;
const int BOARD_EN = 8;
const int BOARD_VCC = 7;

#ifndef USE_ARDUINO_INTERRUPTS
    #define USE_ARDUINO_INTERRUPTS true
    #include "PulseSensorPlayground.h"
#endif

//---------------------------------------------------------------------------------------------------------
class PulseOx
{
public:
    PulseOx(int pulsePin, int ledPin)
        : pulse_(0)
        , oxygenLevel_(95.0f)
        , pulsePin_(pulsePin)
        , ledPin_(ledPin)
    {}
    void begin()
    {
        pulseSensor_.analogInput(pulsePin_);
        pulseSensor_.blinkOnPulse(ledPin_);
        pulseSensor_.setThreshold(THRESHOLD);

        if (!pulseSensor_.begin())
        {
            Serial.println("PulseSensorProblem");
        }
    }

    void performReading()
    {
        int sign = analogRead(pulsePin);
        if (pulseSensor_.sawStartOfBeat() && (sign < 750 && sign > THRESHOLD))
        {
            pulse_ = pulseSensor_.getBeatsPerMinute();
            oxygenLevel_ = 95.0f;

            //Serial.print("MINE---");
            //Serial.print(sign);
            //Serial.print("   ");
            //Serial.println(pulse_);
        }
    }

    int getPulse()
    {
        return pulse_;
    }

    float getOxygenLevel()
    {
        return oxygenLevel_;
    }

private:
    int pulse_;
    float oxygenLevel_;
    int pulsePin_;
    int ledPin_;

    PulseSensorPlayground pulseSensor_;

    static const int THRESHOLD;
};
const int PulseOx::THRESHOLD = 600;
//---------------------------------------------------------------------------------------------------------

DataProcessor proc(tempPin ,BOARD_TX, BOARD_RX, BOARD_EN, BOARD_VCC);
PulseOx pulse(pulsePin, ledPin);

void setup()
{
    pinMode(BOARD_EN, OUTPUT);
    pinMode(BOARD_VCC, OUTPUT);
    digitalWrite(BOARD_EN, LOW);
    digitalWrite(BOARD_VCC, HIGH);

    Serial.begin(9600);
    pulse.begin();
}

void loop()
{
    pulse.performReading();
    int p = pulse.getPulse();
    float ox = pulse.getOxygenLevel();

    proc.setPulseOx(p, ox);
    proc.tick();

    delay(18);
}
