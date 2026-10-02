#pragma once

RTC_DS3231 rtc;

extern uint8_t RTC_SDA_PIN;
extern uint8_t RTC_SCL_PIN;

constexpr char daysOfTheWeek[7][12] = {
    "Sunday",
    "Monday",
    "Tuesday",
    "Wednesday",
    "Thursday",
    "Friday",
    "Saturday"
};

void initialize(uint8_t rtc_sqw_pin);
DateTime now();
uint32_t nowUnix();
String nowToString();
float RtcTemp();
String RtcTempToString();
void clearAlarm1();
void clearAlarm2();
bool setAlarmSeconds(uint8_t seconds);
bool setAlarmMinutes(uint8_t minutes);