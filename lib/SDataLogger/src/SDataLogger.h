#pragma once

extern uint8_t SD_CS;
extern char* LOG_FILE;

void initialize(String cols);
void write(String data, String tag, unsigned long currentTime);
void write(String data, String tag, CallbackString timestamp);
String readLine(File f);
std::vector<String> readRows(File f, int rows);
std::vector<String> readRowsWithTag(File f, const String& targetTag);