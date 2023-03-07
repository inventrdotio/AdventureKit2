/*
 * Day 0 - AI Apocalypse by inventr.io
 * Learn more at https://inventr.io/PLACEHOLDER
 *
 * Getting Started
 * HiLetgo 2.4" ILI9341 240X320 TFT LCD Display with Touch Panel
 * Show LCD Rotations
 *
 * The LCD display can be rotated so that any of it's four sides are designated
 * as "top".  Rotations are numbered 0-4 with rotation 0 used when the display
 * is oriented with the white reset button on top.  The remaining rotations
 * proceed in a clockwise direction (as will be demonstrated with our first test
 * program).
 *
 * Rotations:
 *
 * 0. Portrait rotation (white button on top)
 * 1. Landscape rotation (white button on left)
 * 2. Portrait rotation (white button on bottom)
 * 3. Landscape rotation (white button on right)
 *
 * Adapted for Inventr.io by David Schmidt
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

// Rotations 0,2 = portrait  : 0->button on top : 2->button on bottom
// Rotations 1,3 = landscape : 1->button on left  : 3->button on right

// Show location of coordinate 0, 0 for current rotation
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

// Show origin and rotation number for each rotation (0-3) for two seconds
void loop() {
  for (byte rotation=0; rotation<4; rotation++) {
  tft.setRotation(rotation);
  showZeroZero(rotation);
  delay(2000);
  }
}