// Original code from: https://github.com/VolosR/RotateSpritesTutorial
// YouTube tutorial: https://www.youtube.com/watch?v=oqBa_ptBmLU

// Refactored by David Schmidt
// Originally for T-Display-S3 (170x320 pixels)
// Refactored to scale display based on display size.  T-Display is 135x240 for example

#include <TFT_eSPI.h>
#if USER_SETUP_ID != 25
#error "This sketch is for TFT_eSPI config 25 (TTGO_T_Display)."
#error "Edit libraries/TFT_eSPI/User_Setup_Select.h file and uncomment #include for Setup25_TTGO_T_Display.h"
#endif

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite back = TFT_eSprite(&tft);
TFT_eSprite needle = TFT_eSprite(&tft);

// Needle width = 12% of display width
const unsigned TFT_NEEDLE_WIDTH = (TFT_WIDTH * 12) / 100;
const unsigned TFT_NEEDLE_HEIGHT = TFT_NEEDLE_WIDTH * 4;

void setup() {
  tft.init();
  tft.fillScreen(TFT_BLACK);
  // We'll draw rotated sprites around the center of a square at the top of the display
  tft.setPivot(TFT_WIDTH / 2, TFT_WIDTH / 2);
  needle.createSprite(TFT_NEEDLE_WIDTH, TFT_NEEDLE_HEIGHT);
  back.createSprite(TFT_WIDTH, TFT_WIDTH);
}

int angle = 0;

void loop() {
  back.fillSprite(TFT_BLACK);
  back.fillCircle(TFT_WIDTH / 2, TFT_WIDTH / 2, TFT_WIDTH / 2, TFT_SILVER);
  needle.fillSprite(TFT_BLACK);
  needle.drawWedgeLine(TFT_NEEDLE_WIDTH/2, 0, TFT_NEEDLE_WIDTH/2, TFT_NEEDLE_HEIGHT/2, 1, TFT_NEEDLE_WIDTH/2, TFT_RED);
  needle.drawWedgeLine(TFT_NEEDLE_WIDTH/2, TFT_NEEDLE_HEIGHT/2, TFT_NEEDLE_WIDTH/2, TFT_NEEDLE_HEIGHT, TFT_NEEDLE_WIDTH/2, 1, TFT_BLUE);
  needle.fillCircle(TFT_NEEDLE_WIDTH/2, TFT_NEEDLE_HEIGHT/2, TFT_NEEDLE_WIDTH/2, TFT_WHITE);

  // push with optional transparent color
  needle.pushRotated(&back, angle, TFT_BLACK);
  back.pushSprite(0, 0);

  // Rotate sprite angle
  if (++angle == 360)
    angle = 0;
}
