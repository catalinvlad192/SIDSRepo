#include "../../pch.h"
#include "../../../MainModuleSIDSDetector/SensorData.h"
#include <string.h>

using namespace mm;

TEST(MMSensorData_Test, AttributesShouldHaveDifferentValuesDependingOnBabysMonths)
{
    SensorData* data = new SensorData(2);
    EXPECT_EQ(110, data->getPulseMin());
    EXPECT_EQ(180, data->getPulseMax());
    EXPECT_EQ(20.0f, data->getAmbientTempMin());
    EXPECT_EQ(25.0f, data->getAmbientTempMax());
    EXPECT_EQ(88.0f, data->OXYGENLEVEL_MIN);
    EXPECT_EQ(35.5f, data->BODYTEMP_MIN);
    EXPECT_EQ(38.0f, data->BODYTEMP_MAX);
    EXPECT_EQ(5000.0f, data->SMOKELEVEL_MIN);
    EXPECT_EQ(28.0f, data->HUMIDITY_MIN);
    EXPECT_EQ(55.0f, data->HUMIDITY_MAX);
    EXPECT_EQ(140, data->pulse_);
    EXPECT_EQ(99.0f, data->oxygenLevel_);
    EXPECT_EQ(37.0f, data->bodyTemperature_);
    EXPECT_EQ(50000.0f, data->smokeLevel_);
    EXPECT_EQ(40.0f, data->humidity_);
    EXPECT_EQ(20.0f, data->ambientTemperature_);
    EXPECT_EQ(0, data->isDeviceRemoved_);
    EXPECT_EQ(0, strcmp(data->abnormalities_[0], ""));
    EXPECT_EQ(0, strcmp(data->abnormalities_[1], ""));
    delete(data);

    data = new SensorData(3);
    EXPECT_EQ(110, data->getPulseMin());
    EXPECT_EQ(180, data->getPulseMax());
    EXPECT_EQ(20.0f, data->getAmbientTempMin());
    EXPECT_EQ(25.0f, data->getAmbientTempMax());
    EXPECT_EQ(88.0f, data->OXYGENLEVEL_MIN);
    EXPECT_EQ(35.5f, data->BODYTEMP_MIN);
    EXPECT_EQ(38.0f, data->BODYTEMP_MAX);
    EXPECT_EQ(5000.0f, data->SMOKELEVEL_MIN);
    EXPECT_EQ(28.0f, data->HUMIDITY_MIN);
    EXPECT_EQ(55.0f, data->HUMIDITY_MAX);
    EXPECT_EQ(140, data->pulse_);
    EXPECT_EQ(99.0f, data->oxygenLevel_);
    EXPECT_EQ(37.0f, data->bodyTemperature_);
    EXPECT_EQ(50000.0f, data->smokeLevel_);
    EXPECT_EQ(40.0f, data->humidity_);
    EXPECT_EQ(20.0f, data->ambientTemperature_);
    EXPECT_EQ(0, data->isDeviceRemoved_);
    EXPECT_EQ(0, strcmp(data->abnormalities_[0], ""));
    EXPECT_EQ(0, strcmp(data->abnormalities_[1], ""));
    delete(data);

    data = new SensorData(5);
    EXPECT_EQ(105, data->getPulseMin());
    EXPECT_EQ(175, data->getPulseMax());
    EXPECT_EQ(19.0f, data->getAmbientTempMin());
    EXPECT_EQ(24.0f, data->getAmbientTempMax());
    EXPECT_EQ(88.0f, data->OXYGENLEVEL_MIN);
    EXPECT_EQ(35.5f, data->BODYTEMP_MIN);
    EXPECT_EQ(38.0f, data->BODYTEMP_MAX);
    EXPECT_EQ(5000.0f, data->SMOKELEVEL_MIN);
    EXPECT_EQ(28.0f, data->HUMIDITY_MIN);
    EXPECT_EQ(55.0f, data->HUMIDITY_MAX);
    EXPECT_EQ(140, data->pulse_);
    EXPECT_EQ(99.0f, data->oxygenLevel_);
    EXPECT_EQ(37.0f, data->bodyTemperature_);
    EXPECT_EQ(50000.0f, data->smokeLevel_);
    EXPECT_EQ(40.0f, data->humidity_);
    EXPECT_EQ(20.0f, data->ambientTemperature_);
    EXPECT_EQ(0, data->isDeviceRemoved_);
    EXPECT_EQ(0, strcmp(data->abnormalities_[0], ""));
    EXPECT_EQ(0, strcmp(data->abnormalities_[1], ""));
    delete(data);

    data = new SensorData(6);
    EXPECT_EQ(105, data->getPulseMin());
    EXPECT_EQ(175, data->getPulseMax());
    EXPECT_EQ(19.0f, data->getAmbientTempMin());
    EXPECT_EQ(24.0f, data->getAmbientTempMax());
    EXPECT_EQ(88.0f, data->OXYGENLEVEL_MIN);
    EXPECT_EQ(35.5f, data->BODYTEMP_MIN);
    EXPECT_EQ(38.0f, data->BODYTEMP_MAX);
    EXPECT_EQ(5000.0f, data->SMOKELEVEL_MIN);
    EXPECT_EQ(28.0f, data->HUMIDITY_MIN);
    EXPECT_EQ(55.0f, data->HUMIDITY_MAX);
    EXPECT_EQ(140, data->pulse_);
    EXPECT_EQ(99.0f, data->oxygenLevel_);
    EXPECT_EQ(37.0f, data->bodyTemperature_);
    EXPECT_EQ(50000.0f, data->smokeLevel_);
    EXPECT_EQ(40.0f, data->humidity_);
    EXPECT_EQ(20.0f, data->ambientTemperature_);
    EXPECT_EQ(0, data->isDeviceRemoved_);
    EXPECT_EQ(0, strcmp(data->abnormalities_[0], ""));
    EXPECT_EQ(0, strcmp(data->abnormalities_[1], ""));
    delete(data);

    data = new SensorData(8);
    EXPECT_EQ(100, data->getPulseMin());
    EXPECT_EQ(170, data->getPulseMax());
    EXPECT_EQ(18.0f, data->getAmbientTempMin());
    EXPECT_EQ(23.0f, data->getAmbientTempMax());
    EXPECT_EQ(88.0f, data->OXYGENLEVEL_MIN);
    EXPECT_EQ(35.5f, data->BODYTEMP_MIN);
    EXPECT_EQ(38.0f, data->BODYTEMP_MAX);
    EXPECT_EQ(5000.0f, data->SMOKELEVEL_MIN);
    EXPECT_EQ(28.0f, data->HUMIDITY_MIN);
    EXPECT_EQ(55.0f, data->HUMIDITY_MAX);
    EXPECT_EQ(140, data->pulse_);
    EXPECT_EQ(99.0f, data->oxygenLevel_);
    EXPECT_EQ(37.0f, data->bodyTemperature_);
    EXPECT_EQ(50000.0f, data->smokeLevel_);
    EXPECT_EQ(40.0f, data->humidity_);
    EXPECT_EQ(20.0f, data->ambientTemperature_);
    EXPECT_EQ(0, data->isDeviceRemoved_);
    EXPECT_EQ(0, strcmp(data->abnormalities_[0], ""));
    EXPECT_EQ(0, strcmp(data->abnormalities_[1], ""));
    delete(data);

    data = new SensorData(9);
    EXPECT_EQ(100, data->getPulseMin());
    EXPECT_EQ(170, data->getPulseMax());
    EXPECT_EQ(18.0f, data->getAmbientTempMin());
    EXPECT_EQ(23.0f, data->getAmbientTempMax());
    delete(data);

    data = new SensorData(11);
    EXPECT_EQ(90, data->getPulseMin());
    EXPECT_EQ(160, data->getPulseMax());
    EXPECT_EQ(18.0f, data->getAmbientTempMin());
    EXPECT_EQ(23.0f, data->getAmbientTempMax());
    delete(data);

    data = new SensorData(12);
    EXPECT_EQ(90, data->getPulseMin());
    EXPECT_EQ(160, data->getPulseMax());
    EXPECT_EQ(18.0f, data->getAmbientTempMin());
    EXPECT_EQ(23.0f, data->getAmbientTempMax());
    delete(data);

    data = new SensorData(13);
    EXPECT_EQ(90, data->getPulseMin());
    EXPECT_EQ(160, data->getPulseMax());
    EXPECT_EQ(18.0f, data->getAmbientTempMin());
    EXPECT_EQ(23.0f, data->getAmbientTempMax());
    delete(data);
}

TEST(MMSensorData_Test, AttributesShouldUpdateValueIfNewAgeGiven)
{
    SensorData* data = new SensorData(2);
    EXPECT_EQ(110, data->getPulseMin());
    EXPECT_EQ(180, data->getPulseMax());
    EXPECT_EQ(20.0f, data->getAmbientTempMin());
    EXPECT_EQ(25.0f, data->getAmbientTempMax());

    data->setMonths(11);
    EXPECT_EQ(90, data->getPulseMin());
    EXPECT_EQ(160, data->getPulseMax());
    EXPECT_EQ(18.0f, data->getAmbientTempMin());
    EXPECT_EQ(23.0f, data->getAmbientTempMax());
    delete(data);
}

TEST(MMSensorData_Test, ShouldUpdateAbnormalityVectorProperly)
{
    char abn1[] = "P: 90, Ox: 87.3. T: 35.8";
    char abn2[] = "P: 140, Ox: 95.3. T: 38.8";
    char abn3[] = "P: 190, Ox: 99.3. T: 40.8";
    char abn4[] = "P: 50, Ox: 82.3. T: 34.8";
    char abn5[] = "P: 120, Ox: 88.3. T: 37.8";

    SensorData* data = new SensorData(2);
    EXPECT_EQ(0, strcmp(data->abnormalities_[0], ""));
    EXPECT_EQ(0, strcmp(data->abnormalities_[1], ""));

    data->addAbnormality(abn1);
    EXPECT_EQ(0, strcmp(data->abnormalities_[0], abn1));
    EXPECT_EQ(0, strcmp(data->abnormalities_[1], ""));

    data->addAbnormality(abn2);
    EXPECT_EQ(0, strcmp(data->abnormalities_[0], abn1));
    EXPECT_EQ(0, strcmp(data->abnormalities_[1], abn2));

    data->addAbnormality(abn3);
    EXPECT_EQ(0, strcmp(data->abnormalities_[0], abn3));
    EXPECT_EQ(0, strcmp(data->abnormalities_[1], abn2));

    data->addAbnormality(abn4);
    EXPECT_EQ(0, strcmp(data->abnormalities_[0], abn3));
    EXPECT_EQ(0, strcmp(data->abnormalities_[1], abn4));

    data->addAbnormality(abn5);
    EXPECT_EQ(0, strcmp(data->abnormalities_[0], abn5));
    EXPECT_EQ(0, strcmp(data->abnormalities_[1], abn4));

    delete(data);
}

TEST(MMSensorData_Test, ShouldNotUpdateAbnirmalityVectorIfStringIsEmpty)
{
    const char abn1[] = "P: 90, Ox: 87.3. T: 35.8";
    const char abn2[] = "P: 140, Ox: 95.3. T: 38.8";
    const char abn3[] = "";

    SensorData* data = new SensorData(2);
    EXPECT_EQ(0, strcmp(data->abnormalities_[0], ""));
    EXPECT_EQ(0, strcmp(data->abnormalities_[1], ""));

    data->addAbnormality(abn1);
    EXPECT_EQ(0, strcmp(data->abnormalities_[0], abn1));
    EXPECT_EQ(0, strcmp(data->abnormalities_[1], ""));

    data->addAbnormality(abn2);
    EXPECT_EQ(0, strcmp(data->abnormalities_[0], abn1));
    EXPECT_EQ(0, strcmp(data->abnormalities_[1], abn2));

    data->addAbnormality(abn3);
    EXPECT_EQ(0, strcmp(data->abnormalities_[0], abn1));
    EXPECT_EQ(0, strcmp(data->abnormalities_[1], abn2));

    data->addAbnormality(abn3);
    EXPECT_EQ(0, strcmp(data->abnormalities_[0], abn1));
    EXPECT_EQ(0, strcmp(data->abnormalities_[1], abn2));

    delete(data);
}
