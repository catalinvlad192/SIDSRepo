#ifndef MM_SENSORDATA_H_
#define MM_SENSORDATA_H_

namespace mm{
class SensorData {
public:
    SensorData(unsigned int monthsOfAge);

    void addAbnormality(const char abnormalities[50]);

    //Getters for 'consts'
    int getPulseMin() const;
    int getPulseMax() const;
    float getAmbientTempMin() const;
    float getAmbientTempMax() const;

    void setMonths(int months);

    //Attributes
    int pulse_;
    float oxygenLevel_;
    float bodyTemperature_;
    float smokeLevel_;
    float humidity_;
    float ambientTemperature_;
    int isDeviceRemoved_;

    // Vectors of recorded abmormalities
    char abnormalities_[2][50];

    const float OXYGENLEVEL_MIN = 88.0f;
    const float BODYTEMP_MIN = 36.0f;
    const float BODYTEMP_MAX = 38.0f;
    const float SMOKELEVEL_MIN = 5000.0f;
    const float HUMIDITY_MIN = 28.0f;
    const float HUMIDITY_MAX = 55.0f;

private:
    void init();
    unsigned int monthsOfAge_;

    int abnIndex_ = 0;

    //'Consts'
    int PULSE_MIN = 100;
    int PULSE_MAX = 180;
    float AMBIENTTEMP_MIN = 18.0f;
    float AMBIENTTEMP_MAX = 25.0f;

};
} // namespace mm
#endif
