/*
 * Day 0 - AI Apocalypse by inventr.io
 * Learn more at https://inventr.io/product/adventure-kit-2/
 *
 * Motion sensor lights
 *
 * Until now we've managed to stay pretty hidden here in the old Inventr.io
 * building.  But now that we have our building lights working I'm afraid that
 * we might start to attract more attention, either from the AI or from other
 * survivors that may wish to take what we have built.  There are also more
 * wild animals that could endanger us.
 *
 * While rumaging through our parts box I think I've found something that can
 * help keep us secure, the PIR Motion Sensor.  The sensor operates by detecting
 * the infrared radiation from humans or animals as they move within its range,
 * triggering a signal output that our HERO XL can read on one of it's digital
 * pins.
 *
 * The  sensor comes with two potentiometers and a jumper that allow you to
 * adjust its sensitivity and the time delay after which the signal returns to
 * low (no motion detected).
 *
 * Let's start by wiring up the sensor as shown in the diagram along with
 * an LED that will represent the flood lights outside our building that we
 * can use to scare away any intruders.
 *
 * First version
 * =============
 * The sensor has a built-in timer that controls the duration that the output
 * signal remains high after motion is detected (even if the motion stops).
 *
 * Let's see how well that works by setting SKETCH_VERSION below to 1 before
 * building and uploading to our HERO XL.  Once uploaded you should see the
 * LED light up if you move in front of the sensor.  Because our loop is
 * executing very quickly, the length of time that the LED is lit will closely
 * match the setting of the time delay adjustment on the sensor.
 *
 * If you hold the sensor with the "dome" facing upwards and the two adjustment
 * potentiometers facing you, the time delay adjustment is the one on the left.
 *
 *    -
 *  /   \
 * -------
 * | X X |
 *   ^
 *   + Timing delay potentiometer
 *
 * Turning that potentiometer clockwise will increase the amount of time the
 * LED remains lit, and counter-clockwise will decrease the time.
 *
 * Alex Eschenauer
 * David Schmidt
 */

/*
 * Arduino language concepts introduced in this lesson.
 *
 * Hardware concepts introduced in this lesson:
 * - PIR Motion Sensor - Detects Infra Red radiation and signals motion
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

void setup() {
  pinMode(MOTION_SENSOR, INPUT);  // Input motion events
  pinMode(FLOOD_LIGHTS, OUTPUT);  // Output for flood light control
}

// Continuously check for motion and turn on lights when motion is detected.
void loop() {
  bool motion_detected = digitalRead(MOTION_SENSOR);  // read motion state

  if (motion_detected) {              // motion detected
    digitalWrite(FLOOD_LIGHTS, ON);   // turn on flood lights!
  } else {                            // motion delay expired
    digitalWrite(FLOOD_LIGHTS, OFF);  // turn off the flood lights
  }
}