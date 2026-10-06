#include <SD.h>
#include <SPI.h>
#include <vector>

#include "SDataLogger.h"

using CallbackString = String (*)();

uint8_t SD_CS = 5;
char* LOG_FILE = "/log.csv";

File openFile(char* mode)
{
    File f = SD.open(LOG_FILE, mode);
    return f;
}

void createFile(String cols)
{
    File f = openFile(FILE_WRITE);
    f.println("timestamp,"+cols+",tag");
    f.close();
}

void closeFile(File f)
{
    f.close();
}

void initialize(String cols)
{
    if (!SD.begin(SD_CS)) {
        Serial.println("Failed to start SD card module");
        delay(1000);
    }

    if (!SD.exists(LOG_FILE)) {
        createFile(cols);
    }
}

void write(String data, String tag, unsigned long currentTime = -1)
{
    if (currentTime == -1) currentTime = millis();
    File f = openFile(FILE_APPEND);

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
    File f = openFile(FILE_APPEND);

    f.println(currentTime+","+data+","+tag);

    f.close();
}

String readLine()
{
    File f = openFile(FILE_READ);
    if (!f) {
        Serial.println("Failed to open log file, ensure file exists.");
        return "";
    }

    String line = f.readStringUntil('\n');
    line.trim();

    f.close();

    return line;
}

std::vector<String> readRows(int rows)
{
    File f = openFile(FILE_READ);
    std::vector<String> readRows;
    for(int i = 0; i < rows; i++) {
        readRows.push_back(readLine());
    }
    closeFile(f);

    return readRows;
}

std::vector<String> readRowsWithTag(const String& targetTag)
{
    File f = openFile(FILE_READ);
    std::vector<String> rows;

    f.seek(0);

    while(f.available()) {
        String line = readLine();
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
    closeFile(f);

    return rows;
}