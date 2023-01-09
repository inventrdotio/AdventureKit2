#include "SevSeg.h" //Will need to install this library from arduino manage libraries

SevSeg sevseg; //Instantiate a seven segment controller object

void setup() {
    byte numDigits = 4; // Number of Digits
    byte digitPins[] = {2,3,4,5}; // Connects to Arduino digital pins 2 -> 5
    byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13}; // Segments of the pins Pins

    sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins); // This seven segment display is a common cathode type 
    //If you are running this and your display is all light up then you should change the COMMON_CATHODE to COMMON_ANODE
} 

void loop() {
    static unsigned long timer = millis();
    static int deciSeconds = 0;
    
    if (millis() >= timer) {
        deciSeconds++; // 100 milliSeconds is equal to 1 deciSecond
        timer += 100; 
        if (deciSeconds == 10000) { // Reset to 0 after counting for 1000 seconds.
        deciSeconds=0;
        }
        sevseg.setNumber(deciSeconds, 1);
    }

    sevseg.refreshDisplay(); // Must run repeatedly
}