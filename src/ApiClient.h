#pragma once

bool connectWifi();
bool sendMoistureReading(int raw, uint32_t millivolts, int moisturePercentage);