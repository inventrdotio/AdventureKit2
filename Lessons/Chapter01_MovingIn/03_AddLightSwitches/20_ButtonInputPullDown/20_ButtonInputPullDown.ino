/*
 * Day 0 - AI Apocalypse by inventr.io
 * Learn more at https://inventr.io/PLACEHOLDER
 *
 * Well, we obviously cannot have our lights flashing intermittently when we want them
 * off.  To make sure we always have a stable value on our input pin we use
 * a pull-down or pull-up resistor.  This sketch will demonstrate using a
 * pull-down resistor.
 *
 * Here's how the pull-down resistor works.
 *
 * Imagine you have a digital input pin on your HERO XL that you want to use to
 * read the state of a button—whether it's being pressed or not. But there's a
 * catch: when the button is not pressed, the input pin isn't connected to
 * anything. It's left "floating." Just like a boat without an anchor, this
 * floating pin can drift high or low without warning, giving unpredictable
 * readings.
 *
 * This is where a pull-down resistor comes to the rescue. It's like giving that
 * boat a hefty anchor. We connect one end of the resistor to our input pin and
 * the other end to ground. Now, when the button isn't pressed, the resistor
 * "pulls" the pin towards ground (0V), ensuring it reads a steady LOW.
 *
 * But when the button is pressed, it makes a connection to +5V, and the pin
 * reads HIGH, clear as day. The resistor is strong enough to keep the pin steady
 * when the button isn't pressed, but also gentle enough to step aside when the
 * button is pressed, allowing the pin to read HIGH.
 *
 * This pull-down resistor ensures our input readings are reliable and prevents
 * the digital pin from floating and giving us random data. It's a simple
 * solution to keep our inputs in check and our readings accurate.
 *
 * The HERO XL does NOT have a built-in pull-down resistor, so we will use an external
 * 10K resistor as our pull-down resistor.  There are a number reasons why we use
 * a 10K resistor for this purpose.
 *
 * 1) 10K is high enough that when the button is not pressed, the voltage read at
 *    the input pin is very close to 0V and will be reliably read as "LOW".
 * 2) When the button is pressed, there's a direct connection from 5V to ground
 *    through the resistor.  The resistor limits the amount of current that "leaks"
 *    to ground, preventing damage to our microcontroller.
 * 3) Power consumption.  10K is high enough to limit the amount of "wasted" current
 *    passing to ground when the button is pressed.
 *
 * Alex Eschenauer
 * David Schmidt
 */

/*
 * Arduino language concepts introduced in this lesson:
 *  - if-else statements - provide alternate code to run when condition is false
 *                         (https://www.arduino.cc/reference/en/language/structure/control-structure/else/)
 *
 * Hardware concepts introduced in this lesson:
 *  - pull-down resistors - these connect an input pin to ground, but only when no
 *    other connection exists
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
 *       D13 (this pin controls the built in LED on the HERO XL board (LED_BUILTIN)),
 *       D2-D13, D44-D46 (used for Pulse Width Modulation (PWM))
 *       D50 (MISO), D51 (MOSI), D52 (SCK), D53 (SS).  (used for SPI communication)
 *       D20 (SDA), D21 (SCL).  (used for I2C communication using the Wire library)
 * Recommended for fewest conflicts:
 *    D22-D49
 */
const uint8_t LIGHT_PIN = 22;     // LED on pin 22
const uint8_t LIGHT_BUTTON = 23;  // Button (light switch) on pin 23

// Set up two constants so that we can turn our light "on" or "off".
const uint8_t ON = HIGH;  // HIGH is defined in Arduino.h to output 5 volts to a pin
const uint8_t OFF = LOW;  // LOW is defined to turn a pin "off" (low voltage)

void setup() {
  pinMode(LIGHT_PIN, OUTPUT);    // LED representing our light (output)
  pinMode(LIGHT_BUTTON, INPUT);  // Button controlling light
}

void loop() {
  // Since a digital pin can only have one of two values we can simplify our previous
  // code a bit.  Rather than read the value a second time we can assume that if the
  // light button isn't HIGH, it *must* be LOW.
  // So "if" the value is HIGH then do the FIRST block of code, "else" do the SECOND
  // block of code.
  if (digitalRead(LIGHT_BUTTON) == HIGH) {
    digitalWrite(LIGHT_PIN, ON);
  } else {
    digitalWrite(LIGHT_PIN, OFF);
  }

  delay(50);  // short delay to reduce power consumption
}
