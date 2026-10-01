#pragma once

bool connectWifi();
bool sendMoistureReading(int raw, uint32_t mullivolts, int moisturePercentage);