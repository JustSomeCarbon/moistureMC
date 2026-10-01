#include <Arduino.h>
#include <DHT.h>
#include "HumidCapture.h"

uint8_t HUMIDITY_PIN = 21;
int SAMPLE_LIMIT = 20;

DHT initialize(uint8_t pin)
{
    DHT sensor(pin, DHT_SENSOR_TYPE);
    return sensor;
}

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