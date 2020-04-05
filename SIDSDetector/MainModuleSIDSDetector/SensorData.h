#ifndef SENSORDATA_H_
#define SENSORDATA_H_

class SensorData {
public:
  SensorData(unsigned int monthsOfAge);

  //Getters for 'consts'
  int getPulseMin() const;
  int getPulseMax() const;
  float getAmbientTempMin() const;
  float getAmbientTempMax() const;
  float getOxygenLevelMin() const;
  float getBodyTempMin() const;
  float getBodyTempMax() const;
  float getSmokeLevelMax() const;

  //Attributes
  unsigned int monthsOfAge_;
  int pulse_;
  float oxygenLevel_;
  float bodyTemperature_;
  float smokeLevel_;
  float humidity_;
  float ambientTemperature_;

  //
  bool isDeviceProperlyAttached;

  // Vectors of recorded abmormalities

private:
  //'Consts'
  int PULSE_MIN = 100;
  int PULSE_MAX = 180;
  float AMBIENTTEMP_MIN = 18.0f;
  float AMBIENTTEMP_MAX = 25.0f;
  float OXYGENLEVEL_MIN = 88.0f;
  float BODYTEMP_MIN = 36.0f;
  float BODYTEMP_MAX = 38.0f;
  float SMOKELEVEL_MAX = 100.0f;
};
#endif
