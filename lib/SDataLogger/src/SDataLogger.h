#pragma once

extern uint8_t SD_CS;
extern char* LOG_FILE;

void initialize(String cols);
void write(String data, unsigned long currentTime);
void write(String data, CallbackString timestamp);