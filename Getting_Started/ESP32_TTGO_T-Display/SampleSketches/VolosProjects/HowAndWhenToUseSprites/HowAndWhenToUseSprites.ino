// Original code from: https://www.youtube.com/watch?v=sRGXQg7028A

// Refactored by David Schmidt
// Originally for T-Display-S3 (170x320 pixels)
// Refactored to scale display based on display size.  T-Display is 135x240 for example

#include <TFT_eSPI.h>
#if USER_SETUP_ID != 25
#error "This sketch is for TFT_eSPI config 25 (TTGO_T_Display)."
#error "Edit libraries/TFT_eSPI/User_Setup_Select.h file and uncomment #include for Setup25_TTGO_T_Display.h"
#endif

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite img = TFT_eSprite(&tft);

void setup() {
  tft.init();
  tft.setRotation(1);
  img.createSprite(TFT_HEIGHT, TFT_WIDTH);
  tft.fillScreen(TFT_BLACK);
}

int x_location = 0;
const int Y_LOCATION = 36;

void loop() {
  img.fillCircle(x_location, Y_LOCATION, 30, TFT_BLACK);
  if (x_location++ == TFT_HEIGHT)
    x_location = 0;
  img.fillCircle(x_location, 36, 30, TFT_RED);

  img.fillRect(18, 70, 100, 100, TFT_BLACK);
  img.drawString(String(x_location), 20, 74, 7);
  img.pushSprite(0, 0);
}
