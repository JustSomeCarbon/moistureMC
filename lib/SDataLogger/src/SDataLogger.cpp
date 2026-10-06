#include <SD.h>
#include <SPI.h>
#include <vector>

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
        f.println("timestamp,"+cols+",tag");
        f.close();
    }
}

void write(String data, String tag, unsigned long currentTime = -1)
{
    if (currentTime == -1) currentTime = millis();
    File f = SD.open(LOG_FILE, FILE_APPEND);

    f.print(currentTime);
    f.println(","+data+","+tag);
    
    f.close();
}

/**
 * Writes data to the sd card. takes a string of data and a
 * callback function that is expected to return the timestamp.
 */
void write(String data, String tag, CallbackString timestamp)
{
    String currentTime = timestamp();
    File f = SD.open(LOG_FILE, FILE_APPEND);

    f.println(currentTime+","+data+","+tag);

    f.close();
}

String readLine(File f)
{
    if (!f) {
        Serial.println("Failed to open log file, ensure file exists.");
        return "";
    }

    String line = f.readStringUntil('\n');
    line.trim();

    return line;
}

std::vector<String> readRowsWithTag(File f, const String& targetTag)
{
    std::vector<String> rows;

    f.seek(0);

    while(f.available()) {
        String line = readLine(f);
        if (line.length() == 0) {
            continue;
        }

        int lastComma = line.lastIndexOf(',');

        String tag = (lastComma > 0)
        ? line.substring(lastComma + 1)
        : line;
        tag.trim();

        if (targetTag == tag) {
            rows.push_back(line);
        }
    }

    return rows;
}