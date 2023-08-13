#ifndef MEASUREMENT
#define MEASUREMENT

enum class SensorType
{
    MQ135,
};

class Measurement
{
private:
    SensorType sensor;
    float PM;
    float resistance;

public:
    Measurement(SensorType s, float pm, float resistance) : sensor(s), PM(pm), resistance(resistance) {}

    SensorType getSensor() const
    {
        return sensor;
    }

    float getPM() const
    {
        return PM;
    }

    float getResistance() const
    {
        return resistance;
    }
};

#endif