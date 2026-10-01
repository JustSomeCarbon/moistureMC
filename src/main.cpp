#include <Arduino.h>
#include <ApiClient.h>

constexpr uint8_t MOISTURE_PIN = 34;
constexpr int DRY_RAW = 3240;
constexpr int WET_RAW = 1100;

bool connected = false;
unsigned long lastSent = 0;
constexpr unsigned long SEND_INTERVAL_MS = 60000;

// put function declarations here:
int myFunction(int, int);

int moisturePercentage() {
  long total = 0;

  // average sample to reduce ADC noise
  for (int i = 0; i < 16; ++i) {
    total += analogRead(MOISTURE_PIN);
    delay(5);
  }

  const int raw = total / 16;

  const int percent = map(raw, DRY_RAW, WET_RAW, 0, 100);
  return constrain(percent, 0, 100);
}

void setup() {
  Serial.begin(115200);

  analogReadResolution(12);
  analogSetPinAttenuation(MOISTURE_PIN, ADC_11db);

  if (!connectWifi()) {
    Serial.println("Wi-Fi connection failed.");
  }
  connected = true;
}

void loop() {
  if (connected && (millis() - lastSent < SEND_INTERVAL_MS)) {
    return;
  }

  const uint16_t raw = analogRead(MOISTURE_PIN);
  const uint32_t millivolts = analogReadMilliVolts(MOISTURE_PIN);
  const int moisture = moisturePercentage();

  Serial.printf("raw=%u, voltage=%lu mV, moisture=%d%%\n", raw, millivolts, moisture);
  
  if (connected) {
    lastSent = millis();
    if (sendMoistureReading(raw, millivolts, moisture)) {
      Serial.println("Reading sent.");
    } else {
      Serial.println("Failed to send reading.");
    }
  } else {
    delay(2000);
  }
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}