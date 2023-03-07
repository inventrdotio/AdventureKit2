/*
  TFT LCD - TFT Touch Coordinate
  Based on Librery Example
  modified on 21 Feb 2019
  by Saeed Hosseini
  https://electropeak.com/learn/
*/

#include <stdint.h>
#include "TouchScreen.h"

#define YP A2  
#define XM A3 
#define YM 8   
#define XP 9   

// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

void setup(void) {
  Serial.begin(115200);
  PinMode(YM, )
  delay(1000);
  Serial.println("Start Touch test");
}

void loop(void) {
  
  TSPoint p = ts.getPoint();
  if (p.z > ts.pressureThreshhold) {
     Serial.print("X = "); Serial.print(p.x);
     Serial.print("\tY = "); Serial.print(p.y);
     Serial.print("\tPressure = "); Serial.println(p.z);
  }
  delay(100);
}
