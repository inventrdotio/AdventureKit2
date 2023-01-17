/*
 * Day 0 - AI Apocalypse by inventr.io
 * Learn more at https://inventr.io/PLACEHOLDER
 *
 * Getting Started
 * HiLetgo 2.4" ILI9341 240X320 TFT LCD Display with Touch Panel
 * Touch Switch with Rotation
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

// Define LCD display object
MCUFRIEND_kbv tft;

// Rotations 0,2 = portrait  : 0->upper : 2->lower
// Rotations 1,3 = landscape : 1->upper  : 3->lower
constexpr byte rotation = 1;

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

void setup() {
  Serial.begin(115200);

  tft.begin(tft.readID());
  tft.setRotation(rotation);
  tft.fillScreen(BLACK);
  int BAR_HEIGHT = tft.height() / 16;
  tft.fillRect(0, 0, tft.width(), BAR_HEIGHT, RED); // Top bar
  tft.fillRect(0, tft.height() - BAR_HEIGHT - 1, tft.width(), BAR_HEIGHT, tft.color565(64, 64, 64));  // Bottom bar
  tft.setTextColor(WHITE);
  tft.setTextSize(2);     // System font is 8 pixels.  ht = 8*2=16
  
  // Get size of drawn text so that it can be centered for title
  char title[] = "* * inventr.io * *";
  int size_x, size_y, width, height;
  tft.getTextBounds(title, 0, 0, &size_x, &size_y, &width, &height);
  tft.setCursor((tft.width()-width)/2, 0);
  tft.print(title);

  // draw crosshairs
  tft.drawRect(0, BAR_HEIGHT, tft.width() - 1, tft.height() - (2 * BAR_HEIGHT) - 1, BLUE);
  tft.drawFastHLine(0, tft.height() / 2 - 1, tft.width(), BLUE);
  tft.drawFastVLine(tft.width() / 2, BAR_HEIGHT, tft.height() - (2 * BAR_HEIGHT), BLUE);
  // Add hash marks
  for (int i = BAR_HEIGHT + 8; i < tft.height() - BAR_HEIGHT; i += 8)
    tft.drawFastHLine((tft.width()/2)-4, i, 8, BLUE);
  for (int i = 8; i < tft.width(); i += 8)
    tft.drawFastVLine(i, tft.height()/2 - 4, 8, BLUE);

  tft.setCursor(0, BAR_HEIGHT + 2);
  tft.setTextColor(CYAN);
  tft.println(" Sin");
  tft.setTextColor(RED);
  tft.println(" Cos");
  tft.setTextColor(YELLOW);
  tft.println(" Tan");
  // Sin
  int midline_y = (tft.height() / 2) - 1; // halfway down screen
  int previous_x = 1, previous_y = midline_y;
  for (int i = 2; i < tft.width(); i++) {
    int new_y = midline_y + sin(((i*1.13)*3.14)/180)*95;
    tft.drawLine(previous_x, previous_y, i, new_y, CYAN);
    previous_x = i;
    previous_y = new_y;
  }

  // Cos
  previous_x = 1;
  previous_y = midline_y + cos((1.13*3.14)/180)*95;
  for (int i = 2; i < tft.width(); i++) {
    int new_y = midline_y + cos(((i*1.13)*3.14)/180)*95;
    tft.drawLine(previous_x, previous_y, i, new_y, RED);
    previous_x = i;
    previous_y = new_y;
  }

  // Tan
  previous_x = 1;
  previous_y = midline_y + tan((1.13*3.14)/180);
  for (int i = 2; i < tft.width(); i++) {
    int new_y = midline_y + tan(((i*1.13)*3.14)/180);
    new_y = max(new_y, BAR_HEIGHT + 1); // keep Y within graph boundaries
    new_y = min(new_y, tft.height() - BAR_HEIGHT - 1);
    if (previous_y > midline_y && new_y < midline_y) {  // handle tan asymtope
      tft.drawLine(previous_x, previous_y, i, tft.height()-BAR_HEIGHT-1, YELLOW);
      previous_y = BAR_HEIGHT + 1;  // reset Y to top of graph
    }
    tft.drawLine(previous_x, previous_y, i, new_y, YELLOW);
    previous_x = i;
    previous_y = new_y;
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
