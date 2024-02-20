/*
 * Day 0 - AI Apocalypse by inventr.io
 * Learn more at https://inventr.io/product/adventure-kit-2/
 *
 * Motion sensor lights
 *
 * Second Version
 * ==============
 * We can hope that turning on the flood lights will frighten away anything
 * that approaches, I'd really like to know when this happens, even if I'm
 * in the building and can't see the lights.
 *
 * Let's use the Arduino IDE serial console to print a message whenever motion
 * is detected.  The Arduino IDE has a setting that will add a time stamp to
 * each message so even if we're asleep we can look at the Serial Console the
 * next morning to see when motion was detected.
 *
 * We *could* just add Serial.println() messages where we turn on the LED, but
 * this could cause problems.  First of all, this code could be executing
 * thousands of times per second and our log would have all those repeated
 * messages.  Second, the act of printing messages actually takes time so the
 * loop would end up repeating fewer times per second.
 *
 * What we really want is to print a message every time the sensor first
 * detects motion, and perhaps another when the motion stops.
 *
 * We've done something similar in our previous sketches so let's use that
 * technique again.  Let's create a variable that will save the value of the
 * sensor from the *previous* execution of the loop, and only print our message
 * (and turn on the lights) when motion is FIRST detected.  In other words,
 * when the previous value was OFF and the current value is ON.
 *
 * Build, upload and then open the Serial Console. You can click the small
 * "clock" symbol above the baud setting to see timestamps for each message.
 *
 * Alex Eschenauer
 * David Schmidt
 */

/*
 * Arduino language concepts introduced in this lesson.
 * - timestamps for Arduino IDE Serial Console
 *
 * Hardware concepts introduced in this lesson:
 */
#include "Arduino.h"

/* Choosing what pin to use.
 * This project only needs digital pins.  So, on the Hero XL we *could* use any digital or analog pin
 * (D0-D53, A0-A15).  However, some pins support specialized functions and in later lessons we will be
 * using multiple parts, some of which will use some of those special functions.  So, let's start out
 * on the right foot by trying to use the most basic pin we can for each of our parts.
 *
 * Skip: A0-A15 (save for Analog),
 *       D0/D1 (used by USB and Serial)
 *       D14-D19 (used by Serial 1-3)
 *       D2/D3, D18-D21 (used for external interrupts)
 *       D13 (this pin controls the build in LED on the HERO XL board (LED_BUILTIN)),
 *       D2-D13, D44-D46 (used for Pulse Width Modulation (PWM))
 *       D50 (MISO), D51 (MOSI), D52 (SCK), D53 (SS).  (used for SPI communication)
 *       D20 (SDA), D21 (SCL).  (used for I2C communication using the Wire library)
 * Recommended for fewest conflicts:
 *    D22-D43, D47-D49, A8-A15
 */
const int FLOOD_LIGHTS = 22;   // Flood lights attached to pin 22
const int MOTION_SENSOR = 23;  // PIR motion sensor pin

// constants for turning lights on/off
const uint8_t ON = HIGH;
const uint8_t OFF = LOW;

bool previous_motion = false;  // previous state of motion sensor's pin

void setup() {
  Serial.begin(9600);             // initialize serial console
  pinMode(MOTION_SENSOR, INPUT);  // Input motion events
  pinMode(FLOOD_LIGHTS, OUTPUT);  // Output for flood light control
}

// Check for motion status repeatedly.  Turn on flood lights and add a message
// on the Serial Console when motion is FIRST detected.  Turn off flood lights
// and print another message when motion detection ceases.
void loop() {
  bool motion_detected = digitalRead(MOTION_SENSOR);  // read motion state

  if (motion_detected && !previous_motion) {  // New motion detected
    Serial.println("Motion detected!");
    digitalWrite(FLOOD_LIGHTS, ON);                  // turn on flood lights!
  } else if (!motion_detected && previous_motion) {  // motion delay expired
    Serial.println("Motion stopped!");
    digitalWrite(FLOOD_LIGHTS, OFF);  // turn off the flood lights
  }
  previous_motion = motion_detected;
}