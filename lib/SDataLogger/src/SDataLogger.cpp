#include <SD.h>
#include <SPI.h>

#include "SDataLogger.h"

using CallbackString = String (*)();

uint8_t SD_CS = 5;
char* LOG_FILE = "/log.csv";

void initialize(String cols)
{
    if (!SD.begin(SD_CS)) {
        Serial.println("Failed to start SD card module");
        delay(1000);
    }

    if (!SD.exists(LOG_FILE)) {
        File f = SD.open(LOG_FILE, FILE_WRITE);
        f.println("timestamp,"+cols);
        f.close();
    }
}

void write(String data, unsigned long currentTime = -1)
{
    if (currentTime == -1) currentTime = millis();
    File f = SD.open(LOG_FILE, FILE_APPEND);

    f.print(currentTime);
    f.println(data);
    
    f.close();
}

/**
 * Writes data to the sd card. takes a string of data and a
 * callback function that is expected to return the timestamp.
 */
void write(String data, CallbackString timestamp)
{
    String currentTime = timestamp();
    File f = SD.open(LOG_FILE, FILE_APPEND);

    f.println(currentTime + "," + data);

    f.close();
}