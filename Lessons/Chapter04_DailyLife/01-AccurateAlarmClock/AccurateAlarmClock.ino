/*
 * Real Time Clock
 * by David Schmidt
 * reads the DS3231 RTC and prints the date/time every five seconds
 * If the user inputs a string with the proper number of characters and
 * values matching "YYMMDDwHHMMSS" (year, month, day, day-of-week, hour,
 * minute, sec) then that time/date will be set into the RTC.
 */

#include <Wire.h>
#include <DS3231.h>
#include <LibPrintf.h>
#include "SevSeg.h"

// Pins
const int buzzerPin = 45;

// Objects
DS3231 rtc;
SevSeg sevseg;
RTClib myRTC;

// Alarm time
int alarmHour = 10;
int alarmMinute = 11;


void setup () {
  Serial.begin(115200);
  while(!Serial);
  Wire.begin();
  delay(500);
  printf("To set RTC enter time as YYMMDDwHHMMSS as all digits where:\n"); //3305233101040
  printf("YY = last two digits of year.\n");
  printf("MM = month (01-12)\n");
  printf("DD = day (01-31)\n");
  printf("w = Day of Week, Sun-Sat (1-7)\n");
  printf("HH = Hour of day (00-23)\n");
  printf("MM = Minute of hour (00-59)\n");
  printf("SS = Second (00-59)\n\n");

  // Configure SevSeg
  byte numDigits = 4; // Number of Digits
  byte digitPins[] = {2,3,4,5}; // Connects to Arduino digital pins 2 -> 5
  byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13}; // Segments of the pins Pins
  bool resistorsOnSegments = false;
  byte hardwareConfig = COMMON_CATHODE;
  bool updateWithDelays = false;
  bool leadingZeros = true;

  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments, updateWithDelays, leadingZeros);
  sevseg.setBrightness(100);

  pinMode(buzzerPin, OUTPUT);
}

void loop () {
  // If we have any characters available read them here to see if
  // user wishes to set the time by entering a new time in the format
  // YYMMDDwHHMMSS (year, month, day, day-of-week, hour, minute, sec)
  if (Serial.available()) {
    String newDate = Serial.readStringUntil('\r');
    newDate.trim();
    printf("\nReceived string: >%s<\n\n", newDate.c_str());
    if (newDate.length() == 13) {
      printf("Correct length!  Parsing...\n");
      int year, month, day, dOW, hour, minute, second;
      int count = sscanf(newDate.c_str(), "%2d%2d%2d%1d%2d%2d%2d", &year, &month, &day, &dOW, &hour, &minute, &second);
      printf("scanned in %d values\n", count);
      printf("  Date: %04d/%02d/%02d, dOW: %d, Time: %02d:%02d:%02d\n", year, month, day, dOW, hour, minute, second);
      if (month <= 12 && day <= 31 && hour <= 23 && minute <= 59 && second <= 59) {
        rtc.setClockMode(false);  // set to 24h
        rtc.setYear(year);
        rtc.setMonth(month);
        rtc.setDate(day);
        rtc.setDoW(dOW);
        rtc.setHour(hour);
        rtc.setMinute(minute);
        rtc.setSecond(second);
        printf("New time set!\n");
      } else {
        printf("Some values are out of range, try again.\n");
      }
    } else {
      printf("Wrong length for YYMMDDwHHMMSS.  %d characters\n", newDate.length());
    }
  }

  DateTime now = myRTC.now();

  int currentHour = now.hour();
  int currentMinute = now.minute();
  int currentSecond = now.second();

  int displayTime = (currentHour * 100) + currentMinute;
  sevseg.setNumber(displayTime);
  sevseg.refreshDisplay();

  if (currentHour == alarmHour && currentMinute == alarmMinute) {
    alarmBuzzer();
  } else {
    digitalWrite(buzzerPin, LOW);
  }

  //delay(50); // Update display with a small delay

#ifdef ARDUINO_PRINTF_H_
  printf("%04d/%02d/%02d %02d:%02d:%02d\n", now.year(), now.month(),
    now.day(), now.hour(), now.minute(), now.second());
#else
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(' ');
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
#endif
}

void alarmBuzzer() {
  // Example alarm buzzer sequence
  for (int i = 0; i < 5; i++) {
    digitalWrite(buzzerPin, HIGH);
    delay(200);
    digitalWrite(buzzerPin, LOW);
    delay(200);
  }
}
