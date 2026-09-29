# Microcontroller Moisture Project

Chip: ESP32-D0WD-V3
CPU: Dual-Core Xtensa, up to 240 MHz
Flash: 4MB
Logic Voltage: 3.3V
Platform target: esp32dev

The env file should be:
```
[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino
monitor_speed = 115200
```

Utilize GPIO:
```
constexpr uint8_t MOISTURE_PIN = 34;
```
can also use 32 through 39


Monitor the device using:
```
pio device monitor -b 115200
```
