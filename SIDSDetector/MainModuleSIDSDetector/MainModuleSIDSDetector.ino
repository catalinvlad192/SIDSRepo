#include "DataProcessor.h"

const unsigned int TESTPIN = 13;
const unsigned int PULSE_LED = 11;
const unsigned int OXYGEN_LED = 10;
const unsigned int BODY_TEMPERATURE_LED = 9;
const unsigned int SMOKE_LEVEL_LED = 8;
const unsigned int AMBIENT_TEMPERATURE_LED = 7;
const unsigned int BUZZER_PIN = 12;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  Serial.println("TEST");
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(PULSE_LED, OUTPUT);
  pinMode(OXYGEN_LED, OUTPUT);
  pinMode(BODY_TEMPERATURE_LED, OUTPUT);
  pinMode(SMOKE_LEVEL_LED, OUTPUT);
  pinMode(AMBIENT_TEMPERATURE_LED, OUTPUT);

  pinMode(TESTPIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  static DataProcessor dataProcessor = DataProcessor(BUZZER_PIN,
                                PULSE_LED,
                                OXYGEN_LED,
                                BODY_TEMPERATURE_LED,
                                SMOKE_LEVEL_LED,
                                AMBIENT_TEMPERATURE_LED);

  dataProcessor.tick();
  digitalWrite(TESTPIN, HIGH);
  delay(100);
  digitalWrite(TESTPIN, LOW);
  delay(100);
}
