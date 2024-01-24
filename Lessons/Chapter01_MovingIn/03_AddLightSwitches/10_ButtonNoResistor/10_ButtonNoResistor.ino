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
 * Alex Eschenauer
 * David Schmidt
 */

/*
 * Arduino language concepts introduced in this lesson:
 * - pinMode() INPUT parameter
 * - digitalRead() - Read a binary value from a digital or analog pin
 *                   (https://www.arduino.cc/reference/en/language/functions/digital-io/digitalread/)
 * - "if" statement - test a condition and a decision based on the result
 *                    (https://www.arduino.cc/reference/en/language/structure/control-structure/if/)
 *
 * Hardware concepts introduced in this lesson:
 * - Digital input pins
 * - "Floating" inputs.  An input pin will read random values when not connected
 *    to 5V or Ground.
 * - momentary on push button - connects input to output pins only while pressed
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

// The setup function runs once when the sketch is run.  This is usually used for
// one time initialization.
void setup() {
  pinMode(LIGHT_PIN, OUTPUT);    // LED representing our light (output)
  pinMode(LIGHT_BUTTON, INPUT);  // Button representing our light switch (input)
}

// In the loop we'll check to see if the button is pressed, and when it's pressed we'll
// turn on the light.  When released we turn off the light.
void loop() {
  // Button reads HIGH when pressed (as 5V passes to the input pin).  However,
  // when the button is NOT pressed the button pin isn't connected to either 5v
  // or ground it will "float" and sometimes read HIGH and sometimes read LOW.
  if (digitalRead(LIGHT_BUTTON) == HIGH) {  // Button pin reads HIGH when pressed
    digitalWrite(LIGHT_PIN, ON);
  }

  if (digitalRead(LIGHT_BUTTON) == LOW) {  // Button *may* read LOW when button isn't pressed
    digitalWrite(LIGHT_PIN, OFF);
  }

  // This delay isn't strictly necessary, but if we let the loop() run as quickly as it can
  // then we will use more power than necessary.  Let's check for a change in the button
  // state ever 20th of a second (1000 milliseconds / 20 = 50 milliseconds).  That is fast
  // enough that it will appear instantaneous to our users.
  delay(50);
}
