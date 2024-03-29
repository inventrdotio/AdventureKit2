
// From: https://www.youtube.com/watch?v=KZMkGDyGjxQ
//       https://github.com/VolosR/SpaceWars

// Use board: ESP32 Dev Module
#include <TFT_eSPI.h>
#if USER_SETUP_ID != 25
#error "This sketch is for TFT_eSPI config 25 (TTGO_T_Display)."
#error "Edit libraries/TFT_eSPI/User_Setup_Select.h file and uncomment #include for Setup25_TTGO_T_Display.h"
#endif

#include "splash_screen.h"
#include "targets.h"
#include "sensor_dish.h"
#include "explosion.h"
#include "bullet_explosion.h"
#include "rocket_explosion.h"

#include "rocket.h"
#include "brod1.h"
#include "bulet.h"
#include "ebullet.h"
#include "life.h"
#include "rover.h"
#include "ricon.h"
#include "gameOver.h"
#include "pitches.h"

#define TFT_GREY 0x5AEB
#define lightblue 0x2D18
#define orange 0xFB60
#define purple 0xFB9B

TFT_eSPI tft = TFT_eSPI();

int score = 0;  // Invoke custom library

float bulletX[10] = { -20, -20, -20, -20, -20, -20, -20, -20, -20, -20 };
float bulletY[10] = { -20, -20, -20, -20, -20, -20, -20, -20, -20, -20 };

float EbulletX[10] = { -20, -20, -20, -20, -20, -20, -20, -20, -20, -20 };
float EbulletY[10] = { -20, -20, -20, -20, -20, -20, -20, -20, -20, -20 };

float rocketX[10] = { -20, -20, -20, -20, -20, -20, -20, -20, -20, -20 };
float rocketY[10] = { -20, -20, -20, -20, -20, -20, -20, -20, -20, -20 };

float rocketSpeed = 0.22;
int rockets = 3;

int counter = 0;
int rcounter = 0;
int Ecounter = 0;
int level = 1;
float player_x = 10;
float player_y = 20;

float enemy_y = 18;
float enemy_x = 170;

float enemy_speed = 0.1;

int pom = 0;   // press debounce for fire
int pom2 = 0;  // press debounce for rockets
float speed = 0.42;     // Initial speed for our ship
int blinkTime = 0;
int eHealth = 50;
int mHealth = eHealth;
int lives = 4;
int ly[4] = { 0, 0, 0, 0 };
int ri[3] = { 0, 0, 0 };
int fireTime = 100;
int fireCount = 0;
float EbulletSpeed = 0.42;
int rDamage = 8;  //rocket damage
int tr = 0;

int pom3 = 0;
bool sound = 1;  //sound on or off

int phase = 0;  // phase 0=start screen, phase 1=playing phase, phase 3=game over

float spaceX[30];
float spaceY[30];

const uint8_t BUZZER_PIN = 27;
const uint8_t BUZZER_CHANNEL = 0;

// Simple joystick with up/down/left/right/press_down buttons
const uint8_t UP_BUTTON = 22;     // Ship move UP button
const uint8_t DOWN_BUTTON = 21;   // Ship move DOWN button
const uint8_t LEFT_BUTTON = 2;    // Ship move LEFT button
const uint8_t RIGHT_BUTTON = 17;  // Ship move RIGHT button
const uint8_t CENTER_BUTTON = 15;

const uint8_t FIRE_1_A_BUTTON = 0;   // Fire 1 / A Button
const uint8_t FIRE_2_B_BUTTON = 12;  // Fire 2 / B Button

// T-Display constants
const uint8_t T_DISPLAY_LEFT_BUTTON = 0;  // Buttons on T-Display itself
const uint8_t T_DISPLAY_RIGHT_BUTTON = 35;

const uint8_t LED_1 = 33;  // Red LED
const uint8_t LED_2 = 25;  // Red LED
const uint8_t LED_3 = 26;  // Red LED

// #define FIRE_1_PRESSED (digitalRead(FIRE_1_A_BUTTON) == 0)
#define FIRE_1_PRESSED (digitalRead(T_DISPLAY_LEFT_BUTTON) == 0)
#define FIRE_2_PRESSED (digitalRead(FIRE_2_B_BUTTON) == 0)

void setup(void) {
  Serial.begin(9600);

  // "Joystick" buttons
  pinMode(DOWN_BUTTON, INPUT_PULLUP);
  pinMode(UP_BUTTON, INPUT_PULLUP);
  pinMode(RIGHT_BUTTON, INPUT_PULLUP);
  pinMode(LEFT_BUTTON, INPUT_PULLUP);
  pinMode(CENTER_BUTTON, INPUT_PULLUP);  // stisak

  pinMode(FIRE_1_A_BUTTON, INPUT_PULLUP);  // fire 1 / A
  pinMode(FIRE_2_B_BUTTON, INPUT_PULLUP);  // fire 2 / B

  pinMode(LED_1, OUTPUT);  // led1
  pinMode(LED_2, OUTPUT);  // led2
  pinMode(LED_3, OUTPUT);  // led3

  pinMode(T_DISPLAY_LEFT_BUTTON, INPUT_PULLUP);
  pinMode(T_DISPLAY_RIGHT_BUTTON, INPUT_PULLUP);

  digitalWrite(LED_3, HIGH);

  for (int i = 0; i < 30; i++) {
    spaceX[i] = random(5, 235);
    spaceY[i] = random(18, 132);
  }

  tft.init();
  tft.setRotation(1);
  tft.setSwapBytes(true);
  tft.pushImage(0, 0, 240, 135, SPLASH_SCREEN);
  delay(700);
  Serial.println("setup splash screen");

  // Wait for new press of Fire 1
  while (FIRE_1_PRESSED);
  while (!FIRE_1_PRESSED);
  Serial.println("Past button press");

  digitalWrite(LED_3, LOW);
}

void restart() {
  counter = 0;
  rcounter = 0;
  Ecounter = 0;
  level = 1;
  player_x = 10;
  player_y = 20;
  enemy_y = 18;
  enemy_x = 170;
  enemy_speed = 0.1;

  rockets = 3;
  rDamage = 8;
  lives = 4;
  score = 0;
  ri[0] = 0;
  ri[1] = 0;
  ri[2] = 0;
  ly[0] = 0;
  ly[1] = 0;
  ly[2] = 0;
  ly[3] = 0;
  enemy_y = 44;
  // speed = 0.42;
  // eHealth = 50;
  mHealth = eHealth;
  // EbulletSpeed = 0.42;
  // rocketSpeed = 0.22;

  for (int i = 0; i < 10; i++) {
    bulletX[i] = -20;
    EbulletX[i] = -20;
    rocketX[i] = -20;
  }
}

void newLevel() {
  level++;
  speed = speed + 0.05;
  EbulletSpeed = EbulletSpeed + 0.1;
  eHealth = 50 + ((level-1) * 5);
  mHealth = eHealth;
  enemy_speed = 0.05 + (0.035 * (level-1));

  rockets = 3;
  rDamage = 8 + ((level-1) * 2);
  rocketSpeed = 0.22 + ((level-1) * 0.02);
  ri[0] = 0;
  ri[1] = 0;
  ri[2] = 0;

  enemy_y = 44;

  for (int i = 0; i < 10; i++) {
    bulletX[i] = -20;
    EbulletX[i] = -20;
    rocketX[i] = -20;
  }

  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 0, 4);
  tft.print("Level " + String(level));
  tft.setCursor(0, 22, 2);

  tft.println("Enemy speed : " + String(enemy_speed));
  tft.println("Enemy health : " + String(eHealth));
  tft.println("Enemy bullet speed : " + String(EbulletSpeed));
  tft.println("Remaining lives: " + String(lives));
  tft.println("My speed : " + String(speed));
  tft.println("Rocket damage : " + String(rDamage));
  tft.println("Rocket speed : " + String(rocketSpeed));

  tft.pushImage(170, 5, 55, 54, TARGETS[level - 1]);
  tft.pushImage(170, 61, 72, 72, SENSOR_DISH);

  // Wait for new press of Fire 1
  while (FIRE_1_PRESSED);
  while (!FIRE_1_PRESSED);

  tft.fillScreen(TFT_BLACK);

  // Top and bottom borders
  tft.drawLine(0, 16, 240, 16, lightblue);
  tft.drawLine(0, 134, 240, 134, lightblue);

  // Update current score
  tft.setCursor(200, 0, 2);
  tft.print(score);

  // Update enemy health bar
  tft.fillRect(120, 3, 70, 7, TFT_GREEN);
  tft.drawRect(119, 2, 72, 9, TFT_GREY);
}

void loop() {
  if (phase == 0) {
    restart();
    tft.pushImage(0, 0, 240, 135, SPLASH_SCREEN);
    Serial.println("loop splash screen");
    // Wait for new press of Fire 1
    while (FIRE_1_PRESSED);
    while (!FIRE_1_PRESSED);
    Serial.println("Past button press");

    tft.fillScreen(TFT_BLACK);
    tft.setCursor(0, 0, 4);
    tft.print("Level " + String(level));
    tft.setCursor(0, 22, 2);

    tft.println("Enemy speed : " + String(enemy_speed));
    tft.println("Enemy health : " + String(eHealth));
    tft.println("Enemy bullet speed : " + String(EbulletSpeed));
    tft.println("Remaining lives: " + String(lives));
    tft.println("My speed : " + String(speed));
    tft.println("Rocket damage : " + String(rDamage));
    tft.println("Rocket speed : " + String(rocketSpeed));

    tft.pushImage(170, 5, 55, 54, TARGETS[level - 1]);
    tft.pushImage(170, 61, 72, 72, SENSOR_DISH);

  // Wait for new press of Fire 1
  while (FIRE_1_PRESSED);
  while (!FIRE_1_PRESSED);

    tft.fillScreen(TFT_BLACK);

    tft.drawLine(0, 16, 240, 16, lightblue);
    tft.drawLine(0, 134, 240, 134, lightblue);

    tft.setCursor(200, 0, 2);
    tft.print(score);

    tft.fillRect(120, 3, 70, 7, TFT_GREEN);
    tft.drawRect(119, 2, 72, 9, TFT_GREY);

    phase = 1;
  }

  const uint8_t PLAYER_Y_MAX = 94;    // Farthest down to move (DJS: compute this)
  const uint8_t PLAYER_Y_MIN = 18;
  const uint8_t PLAYER_X_MAX = 125;
  const uint8_t PLAYER_X_MIN = 0;

  if (phase == 1) {                                // playing phase
    if (digitalRead(DOWN_BUTTON) == 0 and player_y < PLAYER_Y_MAX)  // Move down
      player_y += speed;

    if (digitalRead(UP_BUTTON) == 0 and player_y > PLAYER_Y_MIN)  // Move up
      player_y -= speed;

    if (digitalRead(RIGHT_BUTTON) == 0 and player_x < PLAYER_X_MAX)  // Move right
      player_x += speed;

    if (digitalRead(LEFT_BUTTON) == 0 and player_x > PLAYER_X_MIN)  // Move right
      player_x -= speed;

    // Fire 1 button just pressed (uses "pom" to debounce button)
    if (FIRE_1_PRESSED) {  // fire button A button
      if (pom == 0) {
        pom = 1;

        bulletX[counter] = player_x + 34;
        bulletY[counter] = player_y + 15;
        counter = counter + 1;
      }
    } else
      pom = 0;

    // Check for rocket fire if Fire 2 just got pressed (debounce using "pom")
    if (FIRE_2_PRESSED && rockets > 0) { // Rocket button B button
      if (pom2 == 0) {
        pom2 = 1;
        rockets--;
        rocketX[rcounter] = player_x + 34;
        rocketY[rcounter] = player_y + 14;
        rcounter += 1;
        ri[rockets] = -100;
        // Clear fired rocket from status bar.
        tft.fillRect(70 + (rockets * 14), 0, 8, 14, TFT_BLACK);
      }
    } else
      pom2 = 0;

    if (digitalRead(35) == 0)  // buton 35 , on and off sound
    {
      if (pom3 == 0) {
        pom3 = 1;
        sound = !sound;
      }
    } else
      pom3 = 0;

    for (int i = 0; i < 30; i++) {  //drawStars..........................................
      tft.drawPixel(spaceX[i], spaceY[i], TFT_BLACK);
      spaceX[i] = spaceX[i] - 0.5;
      tft.drawPixel(spaceX[i], spaceY[i], TFT_GREY);
      if (spaceX[i] < 0) {
        tft.drawPixel(spaceX[i], spaceY[i], TFT_BLACK);

        spaceX[i] = 244;
      }
    }

    tft.pushImage(player_x, player_y, 49, 40, brod1);
    tft.pushImage(enemy_x, enemy_y, 55, 54, TARGETS[level - 1]);

    for (int i = 0; i < 10; i++) {  //firing buletts
      if (bulletX[i] > 0) {
        tft.pushImage(bulletX[i], bulletY[i], 8, 8, bulet);
        bulletX[i] = bulletX[i] + 0.6;
      }
      if (bulletX[i] > 240)
        bulletX[i] = -30;
    }

    for (int i = 0; i < 10; i++) {  // firing rockets
      if (rocketX[i] > 0) {
        tft.pushImage(rocketX[i], rocketY[i], 24, 12, rocket);
        rocketX[i] = rocketX[i] + rocketSpeed;
      }
      if (rocketX[i] > 240)
        rocketX[i] = -30;
    }

    for (int j = 0; j < 10; j++)  // did my bulet hit enemy
    {
      if (bulletX[j] > enemy_x + 20 && bulletY[j] > enemy_y + 2 && bulletY[j] < enemy_y + 52) {
        tft.pushImage(bulletX[j], bulletY[j], 12, 12, BULLET_EXPLOSION);
        if (sound == 1) {
          tone(BUZZER_PIN, NOTE_C5, 12);  //, BUZZER_CHANNEL);
          noTone(BUZZER_PIN);             //, BUZZER_CHANNEL);
        } else {
          delay(12);
        }
        tft.fillRect(bulletX[j], bulletY[j], 12, 12, TFT_BLACK);
        bulletX[j] = -50;
        score += 1;
        tft.setCursor(200, 0, 2);
        tft.print(score);
        eHealth--;
        tr = map(eHealth, 0, mHealth, 0, 70);
        tft.fillRect(120, 3, 70, 7, TFT_BLACK);
        tft.fillRect(120, 3, tr, 7, TFT_GREEN);

        if (eHealth <= 0) {
          tft.pushImage(enemy_x, enemy_y, 55, 55, EXPLOSION);
          tone(BUZZER_PIN, NOTE_E4, 100);  //, BUZZER_CHANNEL);
          tone(BUZZER_PIN, NOTE_D4, 80);   //, BUZZER_CHANNEL);
          tone(BUZZER_PIN, NOTE_G5, 100);  //, BUZZER_CHANNEL);
          tone(BUZZER_PIN, NOTE_C3, 80);   //, BUZZER_CHANNEL);
          tone(BUZZER_PIN, NOTE_F4, 280);  //, BUZZER_CHANNEL);
          noTone(BUZZER_PIN);              //, BUZZER_CHANNEL);
          delay(700);
          newLevel();
        }
        digitalWrite(25, 1);
        blinkTime = 1;
      }
    }

    for (int j = 0; j < 10; j++)  // did my ROCKET hit enemy
    {
      if (rocketX[j] + 18 > enemy_x && rocketY[j] > enemy_y + 2 && rocketY[j] < enemy_y + 52) {
        tft.pushImage(rocketX[j], rocketY[j], 24, 24, ROCKET_EXPLOSION);
        if (sound == 1) {
          tone(BUZZER_PIN, NOTE_C3, 40);  //, BUZZER_CHANNEL);
          noTone(BUZZER_PIN);             //, BUZZER_CHANNEL);
        } else {
          delay(40);
        }
        tft.fillRect(rocketX[j], rocketY[j], 24, 24, TFT_BLACK);
        //delay(30);

        rocketX[j] = -50;
        score += 12;
        tft.setCursor(200, 0, 2);
        tft.print(score);
        eHealth = eHealth - rDamage;
        tr = map(eHealth, 0, mHealth, 0, 70);
        tft.fillRect(120, 3, 70, 7, TFT_BLACK);
        tft.fillRect(120, 3, tr, 7, TFT_GREEN);

        if (eHealth <= 0) {
          tft.pushImage(enemy_x, enemy_y, 55, 55, EXPLOSION);
          tone(BUZZER_PIN, NOTE_E4, 100);  //, BUZZER_CHANNEL);
          tone(BUZZER_PIN, NOTE_D4, 80);   //, BUZZER_CHANNEL);
          tone(BUZZER_PIN, NOTE_G5, 100);  //, BUZZER_CHANNEL);
          tone(BUZZER_PIN, NOTE_C3, 80);   //, BUZZER_CHANNEL);
          tone(BUZZER_PIN, NOTE_F4, 280);  //, BUZZER_CHANNEL);
          noTone(BUZZER_PIN);              //, BUZZER_CHANNEL);
          delay(700);
          newLevel();
        }
        digitalWrite(25, 0);
        blinkTime = 1;
      }
    }

    for (int j = 0; j < 10; j++) { // Am I hit
      if (EbulletX[j] < player_x + 30 && EbulletX[j] > player_x + 4 &&
          EbulletY[j] > player_y + 4 && EbulletY[j] < player_y + 36) {
        EbulletX[j] = -50;
        ly[lives - 1] = -40;
        tft.fillRect((lives - 1) * 14, 0, 14, 14, TFT_BLACK);
        lives--;
        if (lives == 0) {
          tft.pushImage(player_x, player_y, 55, 55, EXPLOSION);
          tone(BUZZER_PIN, NOTE_G4, 100);  //, BUZZER_CHANNEL);
          tone(BUZZER_PIN, NOTE_B4, 80);   //, BUZZER_CHANNEL);
          tone(BUZZER_PIN, NOTE_C5, 100);  //, BUZZER_CHANNEL);
          tone(BUZZER_PIN, NOTE_A4, 80);   //, BUZZER_CHANNEL);
          tone(BUZZER_PIN, NOTE_F4, 280);  //, BUZZER_CHANNEL);
          noTone(BUZZER_PIN);              //, BUZZER_CHANNEL);
          delay(500);
          tft.fillScreen(TFT_BLACK);
          phase = 2;
        }

        digitalWrite(33, 1);
        blinkTime = 1;
        if (sound == 1) {
          tone(BUZZER_PIN, NOTE_C6, 4);  //, BUZZER_CHANNEL);
          noTone(BUZZER_PIN);            //, BUZZER_CHANNEL);
        } else {
          delay(4);
        }
      }
    }

    // Move enemy ship up/down
    enemy_y += enemy_speed;
    // Reverse direction at top/bottom
    if (enemy_y < 18 || enemy_y > 80)
      enemy_speed *= -1;

    if (blinkTime > 0)
      blinkTime++;

    if (blinkTime > 2) {
      digitalWrite(25, 0);
      digitalWrite(33, 0);
      blinkTime = 0;
    }

    for (int i = 0; i < 10; i++) {  // enemy shoots
      if (EbulletX[i] > -10) {
        tft.pushImage(EbulletX[i], EbulletY[i], 7, 7, ebullet);
        EbulletX[i] = EbulletX[i] - EbulletSpeed;
      }
    }

    for (int i = 0; i < 4; i++)  // draw lifes
      tft.pushImage(i * 14, ly[i], 12, 11, life);
    for (int i = 0; i < 3; i++)  // draw lifes
      tft.pushImage(70 + (i * 14), ri[i], 8, 14, ricon);

    fireCount++;
    if (fireTime == fireCount) {
      EbulletX[Ecounter] = enemy_x + 5;
      EbulletY[Ecounter] = enemy_y + 24;
      fireCount = 0;
      fireTime = random(110 - (level * 15), 360 - (level * 30));
      Ecounter++;
    }
    if (counter == 9)
      counter = 0;

    if (rcounter == 3)
      rcounter = 0;

    if (Ecounter == 9)
      Ecounter = 0;
  }

  if (phase == 2) {  // game over phase
    tft.fillScreen(TFT_BLACK);
    tft.pushImage(0, 0, 240, 135, gameOver);
    tft.setCursor(24, 54, 2);
    tft.print("Score : " + String(score));
    tft.setCursor(24, 69, 2);
    tft.print("Level : " + String(level));
    // Wait for new press of Fire 1
    while (FIRE_1_PRESSED);
    while (!FIRE_1_PRESSED);
    phase = 0;
  }
}
