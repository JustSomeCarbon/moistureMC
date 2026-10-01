#pragma once

// Data collection GIOP for moisture sensor
extern uint8_t MOISTURE_PIN;

// floor dry value for moisture sensor
extern int DRY_RAW;

// ceiling wet value for moisture sensor
extern int WET_RAW;

// number of times data is read from moisture sensor during sample
extern int SAMPLE_LIMIT;

int averageSample(int limit);
int moisturePercentage(int raw_value);