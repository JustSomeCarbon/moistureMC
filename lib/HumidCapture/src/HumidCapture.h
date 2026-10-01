#pragma once

#define DHT_SENSOR_TYPE DHT11

// Data collection GOIP for humidity sensor
extern uint8_t HUMIDITY_PIN;

// number of times data is read from moisture sensor during sample
extern int SAMPLE_LIMIT;

DHT initialize(uint8_t pin);
float readHumidity(DHT sensor, int limit);
float readTemp(DHT sensor, int limit, bool celcius);