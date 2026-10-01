#include <Arduino.h>
#include <DHT.h>
#include "HumidCapture.h"

uint8_t HUMIDITY_PIN = 21;
const int SAMPLE_LIMIT = 10;

/**
 * Initialize the DHT sensor; begin reading values.
 */
DHT initialize(uint8_t pin)
{
    DHT sensor(pin, DHT_SENSOR_TYPE);
    sensor.begin();

    return sensor;
}

/**
 * Read the humidity from sensor. Requires the sensor and an optional
 * sample limit.
 * Returns an average.
 */
float readHumidity(DHT sensor, int limit = SAMPLE_LIMIT)
{
    long total = 0;

    for (int i = 0; i < limit; ++i) {
        float humidity = sensor.readHumidity();
        if (isnan(humidity)) return -1;
        total += humidity;
        delay(5);
    }

    return total / limit;
}

/**
 * Read the temperature from the sensor. Requires the sensor, an optional
 * sample limit, and if reading is in celcius or fahrenheit.
 * Returns an average.
 */
float readTemp(DHT sensor, int limit = SAMPLE_LIMIT, bool celcius = false)
{
    long total = 0;

    for (int i = 0; i < limit; ++i) {
        float temp = sensor.readTemperature(celcius);
        if (isnan(temp)) return -1;
        total += temp;
        delay(5);
    }

    return total / limit;
}