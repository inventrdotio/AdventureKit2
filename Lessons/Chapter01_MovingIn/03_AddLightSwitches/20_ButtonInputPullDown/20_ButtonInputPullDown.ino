/*
 * Day 0 - AI Apocalypse by inventr.io
 * Learn more at https://inventr.io/PLACEHOLDER
 *
 * A momentary on button, also known as a momentary push button or momentary switch, is
 * a type of switch that closes the electrical connection only when it's being pressed. 
 * When you release the button, the connection opens again.
 *
 * Button state is read on a digital input pin.  However, when the button is not pressed
 * the input pin has NO connection to either +5V or Ground.  If you read a digital input pin
 * with no connection the pin will randomly read HIGH or LOW.  This is called a floating
 * pin.
 *
 * If we connect our input pin to ground through a pull-down resistor then the pin will
 * read LOW when not pressed, and HIGH when pressed.
 *
 * The HERO XL does NOT have a built-in pull-down resistor, so we will use an external
 * 10K resistor as our pull-down resistor.
 *
 * Alex Eschenauer
 * David Schmidt
 */

/*
 * Arduino language concepts introduced in this lesson.
 *
 *  - pull-down resistors
 *  - if-else statements
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
 *    D22-D49
 */
const uint8_t LIGHT = 22;         // LED on pin 22
const uint8_t LIGHT_BUTTON = 23;  // Button (light switch) on pin 23

void setup() {
  pinMode(LIGHT, OUTPUT);        // LED representing our light (output)
  pinMode(LIGHT_BUTTON, INPUT);  // Button controlling light (with EXTERNAL pull-down resistor)
}

void loop() {
  // Since a digital pin can only have one of two values we can simplify our previous
  // code a bit.  Rather than read the value a second time we can assume that if the
  // light button isn't HIGH, it *must* be LOW.
  // So "if" the value is HIGH then do the FIRST block of code, "else" do the SECOND
  // block of code.
  if (digitalRead(LIGHT_BUTTON) == HIGH) {
    digitalWrite(LIGHT, HIGH);
  } else {
    digitalWrite(LIGHT, LOW);
  }
  delay(50);
}
