#include <Arduino.h>
#include "MoistureCapture.h"

uint8_t MOISTURE_PIN = 34;
int DRY_RAW = 3240;
int WET_RAW = 1100;
int SAMPLE_LIMIT = 20;

/**
 * Takes moisture samples up to the given limit.
 * Returns an average.
 */
int averageSample(int limit)
{
    long total = 0;

    for (int i = 0; i < limit; ++i) {
        total += analogRead(MOISTURE_PIN);
        delay(5);
    }

    return total / limit;
}

/**
 * Takes a raw value read from the sensor and translates
 * the value to a moisture percentage. The returned value is
 * constrained between 0 to 100 percent.
 */
int moisturePercentage(int raw_value)
{
    return constrain(
        map(raw_value, DRY_RAW, WET_RAW, 0, 100),
        0,
        100
    );
}