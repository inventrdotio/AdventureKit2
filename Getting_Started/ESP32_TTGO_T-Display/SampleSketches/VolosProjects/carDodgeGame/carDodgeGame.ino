#include <TFT_eSPI.h>
#include "player.h"
#include "enemy.h"
TFT_eSPI tft = TFT_eSPI();

int px = 0;    // player car X coordinate
int py = 213;  // player car Y coordinate;
int carSize = 27;

int debounce = 0;
int debounce2 = 0;

int ex[5];  //enemy X coordinate
int ey[5] = { 24, -3, -30, -57, -84 };

bool gameRun = true;

long t = 0;
long gameSpeed = 500000;
int score = 0;
void setup() {
  pinMode(35, INPUT_PULLUP);
  pinMode(0, INPUT_PULLUP);
  tft.init();
  tft.setSwapBytes(true);
  tft.fillScreen(TFT_BLACK);

  for (int n = 0; n < 5; n++)
    ex[n] = random(0, 5) * 27;

  tft.pushImage(ex[0], ey[0], carSize, carSize, enemy);
  tft.pushImage(px, py, carSize, carSize, player);
  tft.drawLine(0, 23, 135, 23, TFT_WHITE);
  tft.drawString("SCORE:", 4, 4, 2);
}

void loop() {

  if (gameRun == true) {
    t++;
    if (t > gameSpeed) {
      drawEnemy();
      t = 0;
    }
    drawPlayer();
    checkColision();
  }
}

void drawPlayer() {
  if (digitalRead(35) == 0 && px < 108) {
    if (debounce == 0) {
      debounce = 1;
      tft.fillRect(px, py, carSize, carSize, TFT_BLACK);
      px = px + 27;
      tft.pushImage(px, py, carSize, carSize, player);
    }
  } else debounce = 0;

  if (digitalRead(0) == 0 && px > 0) {
    if (debounce2 == 0) {
      debounce2 = 1;
      tft.fillRect(px, py, carSize, carSize, TFT_BLACK);
      px = px - 27;
      tft.pushImage(px, py, carSize, carSize, player);
    }
  } else debounce2 = 0;
}

void drawEnemy() {

  for (int n = 0; n < 5; n++) {
    if (ey[n] > -3) {
      tft.fillRect(ex[n], ey[n], 27, 27, TFT_BLACK);
      ey[n] = ey[n] + 27;
      tft.pushImage(ex[n], ey[n], 27, 27, enemy);
    } else {
      ey[n] = ey[n] + 27;
    }
    if (ey[n] >= 240) {
      ey[n] = 24;
      ex[n] = random(0, 5) * 27;
      score++;
      gameSpeed = gameSpeed - 4000;
      tft.drawString(String(score), 50, 4, 2);
      tft.drawString(String(gameSpeed), 70, 4, 2);
    }
  }
}

void checkColision() {
  for (int n = 0; n < 5; n++) {
    if (px == ex[n] && py == ey[n])
      gameRun = false;
  }
}
