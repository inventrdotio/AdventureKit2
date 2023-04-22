/*
 * Day 0 - AI Apocalypse by inventr.io
 * Learn more at https://inventr.io/PLACEHOLDER
 *
 * Alex Eschenauer
 * David Schmidt
 */

/*
 * Arduino language concepts introduced in this lesson.
 *
 * - Potentiometer
 * - Pulse Width Modulation (PWM)
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

const uint8_t ON = HIGH;
const uint8_t OFF = LOW;

bool previous_motion = false;  // previous state of motion sensor's pin

void setup() {
  Serial.begin(9600);             // initialize serial
  pinMode(MOTION_SENSOR, INPUT);  // set arduino pin to input mode
  pinMode(FLOOD_LIGHTS, OUTPUT);  // set arduino pin to output mode
}

unsigned long start_time;
unsigned long delay_start = 0;
const uint8_t DELAY_SECONDS = 5;

void loop() {
  bool motion_detected = digitalRead(MOTION_SENSOR);  // read new state

  if (motion_detected && !previous_motion) {  // New motion detected
    Serial.println("Motion detected!");
    digitalWrite(FLOOD_LIGHTS, ON);  // turn on flood lights!
    delay_start = 0;                 // stop delay timer when motion detected
    start_time = millis();
  } else if (!motion_detected && previous_motion) {  // motion delay expired
    float seconds = (millis() - start_time) / 1000.0;
    Serial.print("Motion stopped after ");
    Serial.print(seconds);
    Serial.println(" seconds.");
    delay_start = millis();  // Start delay timer
  }

  // If flood lights are on and our timer expires then turn off the lights
  if (delay_start && (millis() - delay_start) / 1000 >= DELAY_SECONDS) {
    float seconds = (millis() - start_time) / 1000.0;
    Serial.print("Lights out after ");
    Serial.print(seconds);
    Serial.println(" seconds.");
    digitalWrite(FLOOD_LIGHTS, OFF);  // turn off the flood lights
    delay_start = 0;
  }

  previous_motion = motion_detected;
  delay(10);
}