/*
 * Day 0 - AI Apocalypse by inventr.io
 * Learn more at https://inventr.io/PLACEHOLDER
 *
 * A momentary on button, also known as a momentary push button or momentary switch, is
 * a type of switch that closes the electrical connection only when it's being pressed. 
 * When you release the button, the connection opens again.
 *
 * Button state is read on a digital input pin.  However, when the button is not pressed
 * the voltage level on the input pin will *float* and will randomly read HIGH or LOW.
 *
 * We can connect our input pin to 5V so that when the button isn't pressed it will read
 * a constant value, just connecting it would cause our circuit to always draw significant
 * current.  By adding a resistor we can "pull" the voltage high without excessive current
 * draw.  This resistor is called a pull-up resistor.
 *
 * When the button is pressed we connect our input pin to ground.  Since that path
 * does NOT have a resistor, the input pin will read LOW when the button is pressed.
 *
 * The HERO XL has a built-in pull-up resistor and we can instruct the HERO XL to add it
 * using the INPUT_PULLUP mode in our pinMode() command.
 *
 * Alex Eschenauer
 * David Schmidt
 */

/*
 * Arduino language concepts introduced in this lesson.
 *
 *  * Pull-up resistors
 *  * pinMode INPUT_PULLUP parameter
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

// The setup function runs once when the sketch is run.  This is usually used for
// one time initialization.
void setup() {
  pinMode(LIGHT, OUTPUT);               // LED representing our light (output)
  pinMode(LIGHT_BUTTON, INPUT_PULLUP);  // Button controlling light (input with pull-up resistor)
}

/*
 * In the loop we'll check to see if the button is pressed, and when it's pressed we'll
 * turn on the light.  When released we turn off the light.
 */
void loop() {
  if (digitalRead(LIGHT_BUTTON) == LOW) {   // button is LOW when pressed
    digitalWrite(LIGHT, HIGH);
  }
  if (digitalRead(LIGHT_BUTTON) == HIGH) {  // button is HIGH when NOT pressed
    digitalWrite(LIGHT, LOW);
  }
  delay(50);
}
