/*
 * Day 0 - AI Apocalypse by inventr.io
 * Learn more at https://inventr.io/PLACEHOLDER
 *
 * Our homebuilt sonar is showing that, yes, there are AI "scouts" checking us out.
 *
 * It appears that they are receiving their commands via light based communications,
 * so we can't use a radio jammer to disrupt them, but it appears that if we shine
 * a focused beam of variable colored light at the intruders they seem to lock up.
 *
 * Let's set up a turret that we can remote control with our new "light gun" and see
 * if we can deal with these intruders!
 *
 * Alex Eschenauer
 * David Schmidt
 */

#include <Stepper.h>  // Servo library for controlling our stepper motor

// Joystick constants
const uint8_t JOYSTICK_X = A8;
// const uint8_t JOYSTICK_Y = A9;     // Just using X-Axis for our turret
const uint8_t TRIGGER_PIN = 30;  // Pushing down on the top of the joystick fires our "gun"

// Stepper motor controller constants.  We use the ULN2003 module to control our stepper motor
const uint8_t STEPPER_IN1 = 22;
const uint8_t STEPPER_IN2 = 24;
const uint8_t STEPPER_IN3 = 26;
const uint8_t STEPPER_IN4 = 28;
const int STEPS_PER_REVOLUTION = 2038;                    // Motor requires 2038 pulses to go one revolution
const int STEPS_PER_DEGREE = STEPS_PER_REVOLUTION / 360;  // So this many steps to move one degree

// RGB LED (must use PWM pins)
const uint8_t RED_PIN = 44;
const uint8_t GREEN_PIN = 45;
const uint8_t BLUE_PIN = 46;
// Our button is INPUT_PULLUP, so it will be LOW when pressed.  This macro makes it easy to tell
// when the fire button is pressed.
#define FIRE_NOW (!digitalRead(TRIGGER_PIN))

// Configure stepper pins in this order: IN1, IN3, IN2, IN4
Stepper my_stepper = Stepper(STEPS_PER_REVOLUTION, STEPPER_IN1, STEPPER_IN3, STEPPER_IN2, STEPPER_IN4);

const uint8_t LOOP_DELAY = 20;  // Each time through the loop sho8uld be 20 ms

void setup() {
  Serial.begin(9600);

  // Joystick Trigger button
  pinMode(TRIGGER_PIN, INPUT_PULLUP);  // Trigger pin used to fire LED

  // Stepper speed in RPM.  Faster speeds may cause stepper to buzz and not work.  15 RPM
  // is fastest recommened.
  my_stepper.setSpeed(15);

  // RGB LED pins.
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  // Try and pick some random seed value to give us different random numbers each time
  randomSeed(analogRead(A3) * millis());
  // Set our initial RGB values to random values, 0-255
  uint8_t red_value = map(random(), 0, RANDOM_MAX, 0, 255);
  uint8_t green_value = map(random(), 0, RANDOM_MAX, 0, 255);
  uint8_t blue_value = map(random(), 0, RANDOM_MAX, 0, 255);

  // Confirm that RGB is wired correctly by briefly flashing Red, Green and then Blue
  setColor(255, 0, 0);
  delay(500);
  setColor(0, 255, 0);
  delay(500);
  setColor(0, 0, 255);
  delay(500);
}

// int scan_count = 0;  // How many sweeps have we made.

void loop() {
  long loop_start = millis();  // note when loop starts

  // Joystick values are analog from 0-1023.  The "idle" spot in the middle is somewhere around
  // 500.  Since we only need a left/right indication we'll just make sure the joystick has moved
  // left or right far enough from center.
  if (analogRead(JOYSTICK_X) < 400) {    // Rotate counter clockwise with left joystick
    my_stepper.step(-STEPS_PER_DEGREE);  // Step counter-clockwise 1 degree
  }

  if (analogRead(JOYSTICK_X) > 600) {    // Rotate clockwise with right joystick
    my_stepper.step(+STEPS_PER_DEGREE);  // Step clockwise 1 degree
  }

  // We will fire our "weapon" when the top of the joystick is pressed down.
  if (FIRE_NOW) {
    fireLed();
  } else {
    setColor(0, 0, 0);  // Turn off weapon when not firing
  }

  // The loop can run slower when firing (expecially if the Serial.prinln below is uncommented)
  // so we'll check to see how long loop has run until now, and then delay if there's still time
  // left before our desired LOOP_DELAY.
  long time_so_far = millis() - loop_start;   // How long has loop taken so far
  if (time_so_far < LOOP_DELAY) {
     delay(LOOP_DELAY - time_so_far); // Delay for however long is left before LOOP_DELAY is reached
  }
}

// Use these variables to hold the current RGB values
// NOTE: we use a uint8_t here because the RGB values set set are between
//       0-255, which is 8 bits.  This way when we go past 255 the values
//       automatically wrap around back to zero.
uint8_t red_value;
uint8_t green_value;
uint8_t blue_value;

void fireLed() {
  setColor(red_value, green_value, blue_value);
  // Change RGB values at different rates/directions so our lights 
  red_value -= 1;
  green_value += 2;
  blue_value += 3;
  //  Serial.println("RGB: " + String(red_value) + "/" + String(green_value) + "/" + String(blue_value));
}

void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(RED_PIN, redValue);
  analogWrite(GREEN_PIN, greenValue);
  analogWrite(BLUE_PIN, blueValue);
}
