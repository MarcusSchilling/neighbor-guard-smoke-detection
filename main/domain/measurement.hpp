#ifndef MEASUREMENT_HPP
#define MEASUREMENT_HPP
#include <list>
#include <map>

enum class SensorType
{
    mq135, // Gas Sensor
    dht    // Hygrometer
};

std::map<SensorType, String> sensorTypeStrings{
    {SensorType::mq135, "MQ135"},
    {SensorType::dht, "DHT"}};

enum class MeasurementAttributes
{
    rZero,
    correctedRZero,
    ppm,
    cppm,
    resistance,
    temperature,
    humidity
};

std::map<MeasurementAttributes, String> measurementAttributeText{
    {MeasurementAttributes::rZero, "rZero: %d Ohm"},
    {MeasurementAttributes::correctedRZero, "Corrected rZero: %d Ohm"},
    {MeasurementAttributes::ppm, "ppm: %d"},
    {MeasurementAttributes::cppm, "cppm: %d"},
    {MeasurementAttributes::resistance, "resistance: %d Ohm"},
    {MeasurementAttributes::temperature, "temperature: %d °C"},
    {MeasurementAttributes::humidity, "humidity: %d %"}};

class Measurement
{
private:
    SensorType sensor;
    float RZero;
    float correctedRZero;
    float PPM;
    float cPPM;
    float resistance;
    float temperature;
    float humidity;

public:
    Measurement(
        SensorType s = SensorType::mq135,
        float rz = 0.0,
        float crz = 0.0,
        float ppm = 0.0,
        float cppm = 0.0,
        float resistance = 0.0,
        float temp = 0.0,
        float hum = 0.0)
        : sensor(s), RZero(rz), correctedRZero(crz), PPM(ppm), cPPM(cppm), resistance(resistance), temperature(temp), humidity(hum) {}

    SensorType getSensor() const
    {
        return sensor;
    }

    float getRZero() const
    {
        return RZero;
    }

    float getCorrectedRZero() const
    {
        return correctedRZero;
    }

    float getCorrectedPPM() const
    {
        return cPPM;
    }

    float getPPM() const
    {
        return PPM;
    }

    float getResistance() const
    {
        return resistance;
    }

    float readTemperature() const
    {
        return temperature;
    }

    float readHumidity() const
    {
        return humidity;
    }

    String toString(std::list<MeasurementAttributes> printerOptions)
    {
        String merged = sensorTypeStrings[sensor] + "\n";
        for (MeasurementAttributes option : printerOptions)
        {
            merged = merged + measurementAttributeText[option] + "\n";
        }
        return merged;
    }
};

#endif