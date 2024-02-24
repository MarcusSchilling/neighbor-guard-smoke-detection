#ifndef MEASUREMENT_HPP
#define MEASUREMENT_HPP

enum class SensorType: String
{
    MQ135 = "MQ135", // Gas Sensor
    DHT = "DHT", // Hygrometer
};

enum class MeasurementAttributes: String {
    rZero = "rZero: %d Ohm",
    correctedRZero = "Corrected rZero: %d Ohm",
    ppm = "ppm: %d",
    cppm = "cppm: %d",
    resistance = "resistance: %d Ohm",
    temperature = "temperature: %d °C",
    humidity = "humidity: %d %"
};

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
        SensorType s = MQ135,
        float rz = 0.0,
        float crz = 0.0,
        float ppm = 0.0,
        float cppm = 0.0,
        float resistance = 0.0,
        float temp = 0.0,
        float hum = 0.0
        )
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

    String toString(std::list<MeasurementAttributes> printerOptions) {
        String merged = static_cast<String>(sensor) + "\n";
        for (MeasurementAttributes option: printerOptions) {
            merged = merged + static_cast<String>(option) + "\n";
        }
        return merged;
    }
};

#endif