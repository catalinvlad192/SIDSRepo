#include "Thermometer.h"

Thermometer::Thermometer(int analogPin)
    : analogPin_(analogPin)
    , bodyTemperature_(0.0f)
{}

float Thermometer::getTemperature()
{
    int Vo;
    float R1 = 100000;
    float logR2, R2;
    float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

    Vo = analogRead(analogPin_);
    R2 = R1 * (1023.0 / (float)Vo  - 1.0);
    logR2 = log(R2);
    bodyTemperature_ = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
    bodyTemperature_ = bodyTemperature_ - 273.15;

    return bodyTemperature_;
}
