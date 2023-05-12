/*
    Simple Test for the TTGO T-Display ESP32
    Intent is to mame sure the buttons and the display work.

    Set board to "ESP32 Dev Module"
    If you have upload errors then go to "Tools/Upload Speed" and select the next lowest speed
    until sketch uplaods without errors.

    Original sketch:
      Craig Florin
    Contributors:
      David Schmidt
*/

#include <TFT_eSPI.h>
#if USER_SETUP_ID != 25
#error "This sketch is for TFT_eSPI config 25 (TTGO_T_Display)."
#error "Edit libraries/TFT_eSPI/User_Setup_Select.h file and uncomment #include for Setup25_TTGO_T_Display.h"
#endif

TFT_eSPI tft = TFT_eSPI(135, 240);  // Invoke custom library
void setup() {
  tft.init();
  tft.fillScreen(TFT_BLUE);
  tft.setCursor(3, 2);
  tft.setTextColor(TFT_GREEN, TFT_BLUE);
  tft.setTextSize(2);
  tft.println("Button Test");
  tft.println("   Push a");
  tft.println("   button");
  tft.println("  to Start");
  Serial.begin(9600);
  pinMode(0, INPUT_PULLUP);
  pinMode(35, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(0) == 0) {
    Serial.println("Button 2 Pressed");
    delay(500);
    tft.setCursor(3, 2);
    tft.fillScreen(TFT_RED);
    tft.setTextColor(TFT_GREEN, TFT_RED);
    tft.setTextSize(3);
    tft.println("Left"); 
    tft.println("button");
    tft.println("pressed");
  }
  if (digitalRead(35) == 0) {
    Serial.println("Button 1 Pressed");
    delay(500);
    tft.setCursor(3, 2);
    tft.fillScreen(TFT_GREEN);
    tft.setTextColor(TFT_BLACK, TFT_GREEN);
    tft.setTextSize(3);
    tft.println("Right"); 
    tft.println("button");
    tft.println("pressed");
  }
}
