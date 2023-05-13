
//240x135
// Use board: ESP32 Dev Module
#include <TFT_eSPI.h>
#if USER_SETUP_ID != 25
#error "This sketch is for TFT_eSPI config 25 (TTGO_T_Display)."
#error "Edit libraries/TFT_eSPI/User_Setup_Select.h file and uncomment #include for Setup25_TTGO_T_Display.h"
#endif
TFT_eSPI tft = TFT_eSPI();  // Invoke custom library
#include "bmp.h"
#define TFT_GREY 0x5AEB
#define lightblue 0x2D18
#define orange 0xFB60
#define purple 0xFB9B
float ys = 1;

float x = random(30, 100);  //coordinates of ball
float y = 70;
int ny = y;  //coordinates of previous position
int nx = x;

float px = 45;  //67 je sredina    pozicija igrača
int pxn = px;
int vrije[2] = { 1, -1 };
int enx[16] = { 8, 33, 58, 83, 108, 8, 33, 58, 83, 108, 22, 47, 72, 97, 47, 72 };
int eny[16] = { 37, 37, 37, 37, 37, 45, 45, 45, 45, 45, 53, 53, 53, 53, 61, 61 };
int enc[16] = { TFT_RED, TFT_RED, TFT_RED, TFT_RED, TFT_RED, TFT_GREEN, TFT_GREEN, TFT_GREEN, TFT_GREEN, TFT_GREEN, orange, orange, orange, orange, lightblue, lightblue };
int score = 0;
int level = 1;
float amount[4] = { 0.25, 0.50, 0.75, 1 };
float xs = amount[random(4)] * vrije[random(2)];
int fase = 0;
void setup(void) {
  pinMode(0, INPUT);
  pinMode(35, INPUT);
  tft.init();
  tft.setRotation(0);

  tft.setSwapBytes(true);
  tft.pushImage(0, 0, 135, 240, bootlogo);
}

float xstep = 1;
int spe = 0;
int pom = 0;
int gameSpeed = 7000;
void loop() {

  if (fase == 0) {
    if (digitalRead(0) == 0 || digitalRead(35) == 0) {
      if (pom == 0) {
        tft.fillScreen(TFT_BLACK);
        tft.drawLine(0, 17, 0, 240, TFT_GREY);
        tft.drawLine(0, 17, 135, 17, TFT_GREY);
        tft.drawLine(134, 17, 134, 240, TFT_GREY);

        tft.setCursor(3, 3, 2);
        tft.setTextColor(TFT_WHITE, TFT_BLACK);
        tft.setTextSize(1);
        tft.setCursor(0, 0, 2);
        tft.println("SCORE " + String(score));

        tft.setCursor(99, 0, 2);
        tft.println("LVL" + String(level));
        fase = fase + 1;
        pom = 1;
      }
    } else {
      pom = 0;
    }
  }

  if (fase == 1) {
    if (y != ny) {
      tft.fillEllipse(nx, ny, 2, 2, TFT_BLACK);  //brisanje loptice
      ny = y;
      nx = x;
    }

    if (int(px) != pxn) {
      tft.fillRect(pxn, 234, 24, 4, TFT_BLACK);  //briasnje igraca
      pxn = px;
    }

    if (px >= 2 && px <= 109) {
      if (digitalRead(0) == 0)
        px = px - 1;
      if (digitalRead(35) == 0)
        px = px + 1;
    }

    if (px <= 3)
      px = 4;

    if (px >= 108)
      px = 107;

    if (y > 232 && x > px && x < px + 24) {  ///brisati kasnije
      ys = ys * -1;

      xs = amount[random(4)] * vrije[random(2)];
    }

    for (int j = 0; j < 16; j++) {
      if (x > enx[j] && x < enx[j] + 20 && y > eny[j] && y < eny[j] + 5) {
        tft.fillRect(enx[j], eny[j], 20, 4, TFT_BLACK);
        enx[j] = 400;
        ys = ys * -1;
        xs = amount[random(4)] * vrije[random(2)];

        score = score + 1;

        tft.setCursor(0, 0, 2);
        tft.println("SCORE " + String(score));
      }
    }

    if (y < 21)
      ys = ys * -1.00;

    if (y > 240)
      fase = fase + 1;

    if (x >= 130)
      xs = xs * -1.00;

    if (x <= 4)
      xs = xs * -1.00;

    for (int i = 0; i < 16; i++)  //draw enemies
      tft.fillRect(enx[i], eny[i], 20, 4, enc[i]);

    tft.fillEllipse(int(x), y, 2, 2, TFT_WHITE);  // draw ball

    y = y + ys;
    x = x + xs;

    tft.fillRect(px, 234, 24, 4, TFT_WHITE);

    if (score == 16 || score == 33 || score == 50 || score == 67 || score == 84 || score == 101 || score == 118 || score == 135 || score == 152 || score == 169)
      newLevel();

    delayMicroseconds(gameSpeed);
  }

  if (fase == 2) {
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(13, 103, 2);

    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextSize(1);

    tft.println("GAME OVER");
    tft.setCursor(13, 123, 4);
    tft.println("SCORE:" + String(score));

    tft.setCursor(13, 153, 4);
    tft.println("LEVEL:" + String(level));

    tft.setCursor(13, 123, 4);
    tft.println("SCORE:" + String(score));

    delay(3000);
  }
}

void newLevel() {
  score = score + 1;
  delay(3000);
  gameSpeed = gameSpeed - 500;
  level = level + 1;
  tft.setCursor(99, 0, 2);
  tft.println("LVL" + String(level));
  y = 75;
  ys = 1;
  x = random(30, 100);

  int enx2[16] = { 8, 33, 58, 83, 108, 8, 33, 58, 83, 108, 22, 47, 72, 97, 47, 72 };
  for (int n = 0; n < 16; n++) {
    enx[n] = enx2[n];
  }
}
