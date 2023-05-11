/*
Hello!, Here is my color Picker. I am using TTGO T-Display board (ESP32), custom PCB and few components for this project. PCB is made by pcbway.com I always use their service because speed, price and quality.
I will use this device to chose colors for my other projects. This way i can check diferent combinations of colors.

You can buy TTGO T-Display here: 
https://www.banggood.com/custlink/mvm...

Here is code:
https://github.com/VolosR/ColorPicker...

You can order these pcbs here:
https://www.pcbway.com/project/sharep...

YOU CAN SUPPORT THIS CHANNEL BY BUYING ME COFFE HERE:
https://ko-fi.com/volosprojects
Thank you :)
*/

#include <TFT_eSPI.h>
#if USER_SETUP_ID != 25
#error "This sketch is for TFT_eSPI config 25 (TTGO_T_Display)."
#error "Edit libraries/TFT_eSPI/User_Setup_Select.h file and uncomment #include for Setup25_TTGO_T_Display.h"
#endif

#include "orbitron20.h"
TFT_eSPI tft = TFT_eSPI();  // Create object "tft"
TFT_eSprite img = TFT_eSprite(&tft);

#define gray 0x94B2

const int pwmFreq = 5000;
const int pwmResolution = 8;
const int pwmLedChannelTFT = 0;
int brightnes = 80;

uint16_t color2 = TFT_WHITE;
uint16_t color1 = TFT_BLACK;

void setup() {
  pinMode(35, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  pinMode(27, INPUT_PULLUP);
  pinMode(26, INPUT_PULLUP);
  pinMode(0, INPUT_PULLUP);
  tft.init();
  tft.fillScreen(TFT_WHITE);
  tft.setRotation(1);
  img.setFreeFont(&Orbitron_Medium_18);
  img.setTextColor(color1, color2);
  img.createSprite(240, 135);
  ledcSetup(pwmLedChannelTFT, pwmFreq, pwmResolution);
  ledcAttachPin(TFT_BL, pwmLedChannelTFT);
  ledcWrite(pwmLedChannelTFT, brightnes);
}

void loop() {
  drawS();
}

void drawS() {
  img.setTextColor(color1, color2);
  img.fillSprite(color2);
  int r = map(analogRead(2), 4095, 0, 0, 255);
  int g = map(analogRead(15), 4095, 0, 0, 255);
  int b = map(analogRead(13), 4095, 0, 0, 255);

  img.drawRect(4, 24, 132, 20, gray);
  img.drawRect(4, 68, 132, 20, gray);
  img.drawRect(4, 112, 132, 20, gray);

  img.drawString("RED: " + String(r), 6, 0);
  img.fillRect(6, 26, r / 2, 16, TFT_RED);
  img.drawString("GREEN: " + String(g), 6, 44);
  img.fillRect(6, 70, g / 2, 16, TFT_GREEN);
  img.drawString("BLUE: " + String(b), 6, 88);
  img.fillRect(6, 114, b / 2, 16, TFT_BLUE);

  if (digitalRead(26) == 0) {
    brightnes = map(analogRead(13), 4095, 0, 0, 255);
    ledcWrite(pwmLedChannelTFT, brightnes);
  }





  uint16_t chosen = tft.color565(r, g, b);
  img.drawString("COLOR", 148, 0);
  img.drawString("0x" + String(chosen, HEX), 148, 90, 4);
  img.drawString("BRIGHT: " + String(brightnes), 148, 118, 2);
  img.fillRect(148, 24, 80, 62, chosen);
  img.drawRect(146, 22, 84, 66, gray);

  if (digitalRead(12) == 0)
    color1 = chosen;

  if (digitalRead(27) == 0)
    color2 = chosen;

  if (digitalRead(0) == 0) {
    color1 = TFT_BLACK;
    color2 = TFT_WHITE;
  }

  if (digitalRead(35) == 0) {
    img.fillScreen(color2);
    img.drawString("text:0x" + String(color1, HEX), 6, 10, 4);
    img.drawString("back:0x" + String(color2, HEX), 6, 30, 4);
    img.drawString("select:0x:" + String(chosen, HEX), 6, 50, 4);
  }

  img.pushSprite(0, 0);
}
