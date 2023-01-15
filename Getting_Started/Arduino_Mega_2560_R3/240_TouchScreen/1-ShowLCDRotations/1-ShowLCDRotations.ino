/*
 Demonstrates rotations for
 TFT LCD - resistive.
*/

#include <MCUFRIEND_kbv.h>

MCUFRIEND_kbv tft;

// Assign human-readable names to some common 16-bit color values:
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

 // Rotations 0,2 = portrait  : 0->USB=right,upper : 2->USB=left,lower
 // Rotations 1,3 = landscape : 1->USB=left,upper  : 3->USB=right,lower

void showZeroZero(byte orientation)
 {
  tft.fillScreen(BLUE);
  tft.setCursor(0, 0);
  tft.print("0,0");
  tft.setCursor(tft.width()/2-12, tft.height()/2-12);
  tft.print(orientation);
 }
 
void setup() {
  tft.begin();
  // tft.setRotation() commonly goes here
  tft.setTextColor(WHITE, BLUE);
  tft.setTextSize(3);
}

void loop() {
  for(byte rotation=0; rotation<4; rotation++) {
  tft.setRotation(rotation);
  showZeroZero(rotation);
  delay(2000);
  }
}