#include "SevSeg.h"
SevSeg sevseg; 

int i = 0;

void setup() {
    byte numDigits = 1;
    byte digitPins[] = {};
    byte segmentPins[] = {2, 3, 4, 5, 6, 7, 8, 9};
    bool resistorsOnSegments = true;

    byte hardwareConfig = COMMON_CATHODE; 
    sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
    sevseg.setBrightness(90);
}

void loop() {
    if (++i > 9) i=0;
    sevseg.setNumber(i);
    sevseg.refreshDisplay();   
    delay(1000);     
}
