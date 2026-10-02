#include <Arduino.h>
#include <Wire.h>
#include <RTClib.h>

#include "RTClock.h"

uint8_t RTC_SDA_PIN = 21;
uint8_t RTC_SCL_PIN = 22;

void initialize(uint8_t rtc_sqw_pin = -1)
{
    Wire.begin(RTC_SDA_PIN, RTC_SCL_PIN);
    if (!rtc.begin()) {
        Serial.println("Could not find RTC connection");
        Serial.flush();
        delay(1000);
    }

    if (rtc.lostPower())
    {
        Serial.println("RTC lost power, reseting time...");
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }

    if (rtc_sqw_pin != -1)
    {
        pinMode(rtc_sqw_pin, INPUT_PULLUP);
    }

    rtc.writeSqwPinMode(DS3231_OFF);
}

DateTime now()
{
    return rtc.now();
}

uint32_t nowUnix()
{
    DateTime currentTime = now();
    return currentTime.unixtime();
}

String nowToString()
{
    DateTime currentTime = now();
    String year = String(currentTime.year(), DEC);
    String month = (currentTime.month() < 10 ? "0" : "") + String(currentTime.month(), DEC);
    String day = (currentTime.day() < 10 ? "0" : "") + String(currentTime.day(), DEC);
    String hour = (currentTime.hour() < 10 ? "0" : "") + String(currentTime.hour(), DEC);
    String minute = (currentTime.minute() < 10 ? "0" : "") + String(currentTime.minute(), DEC);
    String second = (currentTime.second() < 10 ? "0" : "") + String(currentTime.second(), DEC);
    String dayOfTheWeek = daysOfTheWeek[currentTime.dayOfTheWeek()];

    String formattedTime = dayOfTheWeek + ", " + year + "-" + month + "-" + day + " " + hour + ":" + minute + ":" + second;
    return formattedTime;
}

float RtcTemp()
{
    float temp = rtc.getTemperature();
    float roundedTemp = (int)(temp * 100 + 0.5);
    return roundedTemp;
}

String RtcTempToString()
{
    float temp = RtcTemp();
    char tempString[10];
    sprintf(tempString, "%fC", temp);
    return tempString;
}

void clearAlarm1()
{
    if (rtc.alarmFired(1)) {
        rtc.clearAlarm(1);
    }
}

void clearAlarm2()
{
    if (rtc.alarmFired(2)) {
        rtc.clearAlarm(2);
    }
}

bool setAlarmSeconds(uint8_t seconds)
{
    return rtc.setAlarm1(
        now() + TimeSpan(0, 0, 0, seconds),
        DS3231_A1_Second
    );
}

bool setAlarmMinutes(uint8_t minutes)
{
    return rtc.setAlarm1(
        now() + TimeSpan(0, 0, minutes, 0),
        DS3231_A1_Minute
    );
}