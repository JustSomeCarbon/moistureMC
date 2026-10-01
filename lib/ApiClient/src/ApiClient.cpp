#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

#include "ApiClient.h"

constexpr char WIFI_SSID[] = "HIVE-TEST-NETWORK";
constexpr char WIFI_PASSWORD[] = ""; // ender wifi password
constexpr char API_URL[] = ""; // web api url

bool connectWifi() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    const unsigned long startedAt = millis();

    while (WiFi.status()  != WL_CONNECTED) {
        if (millis() - startedAt > 15000) {
            return false;
        }
        delay(250);
    }

    return true;
}

bool sendMoistureReading(
    const int raw,
    const uint32_t millivolts,
    const int moisturePercentage
) {
    if (WiFi.status() != WL_CONNECTED && !connectWifi()) {
        return false;
    }

    String payload;
    payload.reserve(160);

    payload = "{\"deviceId\":\"sensor-1\",\"raw\":";
    payload += raw;
    payload += ",\"millivolts\":";
    payload += millivolts;
    payload += ",\"moisturePercentage\":";
    payload += moisturePercentage;
    payload += "}";

    WiFiClient client;
    HTTPClient http;

    http.begin(client, API_URL);
    http.addHeader("Content-Type", "application/json");

    const int statusCode = http.POST(payload);
    http.end();

    return statusCode >= 200 && statusCode < 300;
}