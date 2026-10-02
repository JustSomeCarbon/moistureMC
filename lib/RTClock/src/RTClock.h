#pragma once

RTC_DS3231 rtc;

constexpr char daysOfTheWeek[7][12] = {
    "Sunday",
    "Monday",
    "Tuesday",
    "Wednesday",
    "Thursday",
    "Friday",
    "Saturday"
};

void initialize();
DateTime now();
uint32_t nowUnix();
String nowToString();
float RtcTemp();
String RtcTempToString();
void clearAlarm1();
void clearAlarm2();
bool setAlarmSeconds(uint8_t seconds);
bool setAlarmMinutes(uint8_t minutes);