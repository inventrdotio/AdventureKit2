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

RTClib myRTC;
DS3231 setRTC;

void setup () {
    Serial.begin(115200);
    while(!Serial);
    Wire.begin();
    delay(500);
    printf("To set RTC enter time as YYMMDDwHHMMSS as all digits where:\n");
    printf("YY = last two digits of year.\n");
    printf("MM = month (01-12)\n");
    printf("DD = day (01-31)\n");
    printf("w = Day of Week, Sun-Sat (1-7)\n");
    printf("HH = Hour of day (00-23)\n");
    printf("MM = Minute of hour (00-59)\n");
    printf("SS = Second (00-59)\n\n");
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
        setRTC.setClockMode(false);  // set to 24h
        setRTC.setYear(year);
        setRTC.setMonth(month);
        setRTC.setDate(day);
        setRTC.setDoW(dOW);
        setRTC.setHour(hour);
        setRTC.setMinute(minute);
        setRTC.setSecond(second);
        printf("New time set!\n");
      } else {
        printf("Some values are out of range, try again.\n");
      }
    } else {
      printf("Wrong length for YYMMDDwHHMMSS.  %d characters\n", newDate.length());
    }
  }
//  printf("printf is supported!");

  DateTime now = myRTC.now();

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

  // Serial.print(" since midnight 1/1/1970 = ");
  // Serial.print(now.unixtime());
  // Serial.print("s = ");
  // Serial.print(now.unixtime() / 86400L);
  // Serial.println("d");
  delay(5000);
}

/*
DS3231_set.pde
Eric Ayars
4/11

Test of set-time routines for a DS3231 RTC

*/
/*

#include <DS3231.h>
#include <Wire.h>

DS3231 myRTC;

byte year;
byte month;
byte date;
byte dOW;
byte hour;
byte minute;
byte second;

void getDateStuff(byte& year, byte& month, byte& date, byte& dOW,
                  byte& hour, byte& minute, byte& second) {
    // Call this if you notice something coming in on
    // the serial port. The stuff coming in should be in
    // the order YYMMDDwHHMMSS, with an 'x' at the end.
    boolean gotString = false;
    char inChar;
    byte temp1, temp2;
    char inString[20];
    
    byte j=0;
    while (!gotString) {
        if (Serial.available()) {
            inChar = Serial.read();
            inString[j] = inChar;
            j += 1;
            if (inChar == 'x') {
                gotString = true;
            }
        }
    }
    Serial.println(inString);
    // Read year first
    temp1 = (byte)inString[0] -48;
    temp2 = (byte)inString[1] -48;
    year = temp1*10 + temp2;
    // now month
    temp1 = (byte)inString[2] -48;
    temp2 = (byte)inString[3] -48;
    month = temp1*10 + temp2;
    // now date
    temp1 = (byte)inString[4] -48;
    temp2 = (byte)inString[5] -48;
    date = temp1*10 + temp2;
    // now Day of Week
    dOW = (byte)inString[6] - 48;
    // now hour
    temp1 = (byte)inString[7] -48;
    temp2 = (byte)inString[8] -48;
    hour = temp1*10 + temp2;
    // now minute
    temp1 = (byte)inString[9] -48;
    temp2 = (byte)inString[10] -48;
    minute = temp1*10 + temp2;
    // now second
    temp1 = (byte)inString[11] -48;
    temp2 = (byte)inString[12] -48;
    second = temp1*10 + temp2;
}

void setup() {
    // Start the serial port
    Serial.begin(115200);
    
    // Start the I2C interface
    Wire.begin();
    Serial.println("Input date as YYMMDDwHHMMSS");
}

void loop() {
    
    // If something is coming in on the serial line, it's
    // a time correction so set the clock accordingly.
    if (Serial.available()) {
        Serial.println("Reading new date");
        getDateStuff(year, month, date, dOW, hour, minute, second);
        
        myRTC.setClockMode(false);  // set to 24h
        //setClockMode(true); // set to 12h
        
        myRTC.setYear(year);
        myRTC.setMonth(month);
        myRTC.setDate(date);
        myRTC.setDoW(dOW);
        myRTC.setHour(hour);
        myRTC.setminute(minute);
        myRTC.setSecond(second);
        
        // Test of alarm functions
        // set A1 to one minute past the time we just set the clock
        // on current day of week.
        myRTC.setA1Time(dOW, hour, minute+1, second, 0x0, true,
                        false, false);
        // set A2 to two minutes past, on current day of month.
        myRTC.setA2Time(date, hour, minute+2, 0x0, false, false,
                        false);
        // Turn on both alarms, with external interrupt
        myRTC.turnOnAlarm(1);
        myRTC.turnOnAlarm(2);
        Serial.println("Date/Time set");
    }
    delay(1000);
}
*/