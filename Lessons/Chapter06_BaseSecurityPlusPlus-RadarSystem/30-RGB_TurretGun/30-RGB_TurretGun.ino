/*
 * Day 0 - AI Apocalypse by inventr.io
 * Learn more at https://inventr.io/PLACEHOLDER
 *
 * Intruders seem to be approaching our safe haven more and more lately.  While the
 * motion sensors seem to be working, we need something better to see exactly what's
 * approaching our building.
 *
 * We can use an ultrasonic distance sensor to determine distance to objects near us
 * and if we rotate the sensor around we can protect a wide area.
 *
 * Let's use the HC-SR04 Ultrasonic Ranging Module for distance to objects, and we can
 * use an SG90 Servo to rotate the sensor 180 degrees back and forth.  We can put one
 * on each side of our building to warn us of anything approaching.
 *
 * Let's use the Touch LCD 240x320 display shield to display our results.  We can display
 * the distance to objects as dots in a display similar to a 180 degree radar screen.
 *
 * Alex Eschenauer
 * David Schmidt
 */

#include <Stepper.h>          // Servo library for controlling our stepper motor
// #include <MCUFRIEND_kbv.h>  // Graphics library used to draw our "radar" screen

// MCUFRIEND_kbv tft;  // Instantiate the graphics object to be used for drawing.

// Joystick
const uint8_t JOYSTICK_X = A8;
const uint8_t JOYSTICK_Y = A9;
const uint8_t TRIGGER_PIN = 30;  // Arduino pin to Joystick button

// Stepper
const uint8_t STEPPER_IN1 = 22;
const uint8_t STEPPER_IN2 = 24;
const uint8_t STEPPER_IN3 = 26;
const uint8_t STEPPER_IN4 = 28;
const int STEPS_PER_REVOLUTION = 2038;
const int STEPS_PER_DEGREE = STEPS_PER_REVOLUTION / 360;

// RGB LED (must use PWM pins)
const uint8_t RED_PIN = 44;
const uint8_t GREEN_PIN = 45;
const uint8_t BLUE_PIN = 46;
uint8_t red_value;
uint8_t green_value;
uint8_t blue_value;
#define FIRE_LED (!digitalRead(TRIGGER_PIN))

// Configure stepper pins in this order: IN1, IN3, IN2, IN4
Stepper my_stepper = Stepper(STEPS_PER_REVOLUTION, STEPPER_IN1, STEPPER_IN3, STEPPER_IN2, STEPPER_IN4);

const uint8_t LOOP_DELAY = 10;

void setup() {
  Serial.begin(9600);

  // Joystick Trigger button
  pinMode(TRIGGER_PIN, INPUT_PULLUP);  // Trigger pin used to fire LED

  // Stepper
  my_stepper.setSpeed(15);

  // RGB LED
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  randomSeed(analogRead(A3) * millis());
  uint8_t red_value = map(random(), 0, RANDOM_MAX, 0, 255);
  uint8_t green_value = map(random(), 0, RANDOM_MAX, 0, 255);
  uint8_t blue_value = map(random(), 0, RANDOM_MAX, 0, 255);
  setColor(255, 0, 0);
  delay(500);
  setColor(0, 255, 0);
  delay(500);
  setColor(0, 0, 255);
  delay(500);
}

int scan_count = 0;  // How many sweeps have we made.

void loop() {
  long loop_start = millis();   // note when loop starts

  if (analogRead(JOYSTICK_X) < 400) {   // Rotate counter clockwise
    my_stepper.step(-STEPS_PER_DEGREE);
  }

  if (analogRead(JOYSTICK_X) > 600) {
    my_stepper.step(+STEPS_PER_DEGREE);
  }

  if (FIRE_LED) {
    fireLed();
  } else {
    setColor(0, 0, 0);  // Turn off LED
  }

  long time_so_far = millis() - loop_start;
  if (time_so_far < LOOP_DELAY) delay(LOOP_DELAY - time_so_far);
  Serial.println(millis() - loop_start);
}

void fireLed() {
  setColor(red_value, green_value, blue_value);
  red_value -= 1;
  green_value += 2;
  blue_value += 3;
  Serial.println("RGB: " + String(red_value) + "/" + String(green_value) + "/" + String(blue_value));
}

void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(RED_PIN,   redValue);
  analogWrite(GREEN_PIN, greenValue);
  analogWrite(BLUE_PIN,  blueValue);
}
