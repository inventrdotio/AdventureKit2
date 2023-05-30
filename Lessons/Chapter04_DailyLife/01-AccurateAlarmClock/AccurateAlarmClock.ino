#include <Wire.h>
#include "RTClib.h"
#include "SevSeg.h"

// Pins
const int buzzerPin = 45;

// Objects
RTC_DS3231 rtc;
SevSeg sevseg;

// Alarm time
int alarmHour = 6;
int alarmMinute = 30;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  rtc.begin();

  if (!rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // Set RTC time here if needed, e.g.:
    // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

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

void loop() {
  DateTime now = rtc.now();
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

  delay(50); // Update display with a small delay
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
