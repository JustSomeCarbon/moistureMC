#pragma once

extern uint8_t SD_CS;
extern char* LOG_FILE;

File openFile(char* mode);
void createFile();
void closeFile(File f);

void initialize(String cols);
void write(String data, String tag, unsigned long currentTime);
void write(String data, String tag, CallbackString timestamp);
String readLine();
std::vector<String> readRows(int rows);
std::vector<String> readRowsWithTag(const String& targetTag);