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
 * We can also connect our input pin through a pull-up resistor to +5V to use as a default
 * value.  Our HERO XL even provides an internal pull-up resistor that does just that, so
 * if we enable the build-in pull-up resistor we no longer need an external resistor connected
 * to our button.
 *
 * Now, when the button isn't pressed our input pin will read a HIGH value.  We will connect
 * our buttons other side to GND so that when our button is pressed it will show a LOW value.
 *
 * We enable the built-in pull-up resistor by setting our mode in the pinMode() statement
 * to INPUT_PULLUP.
 *
 * Alex Eschenauer
 * David Schmidt
 */

/*
 * Arduino language concepts introduced in this lesson.
 *
 *  - pull-up resistors
 *  - pinMode INPUT_PULLUP parameter
 *  - Setting a constant to represent PRESSED
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

/*
 * NOTE: Using a pull-up resistor can cause some confusion because the input pin connected
 *       to our button will read HIGH when the button is NOT pressed, and LOW when the
 *       button IS pressed.  We can reduce this confusion a little by defining a
 *       new constant for the state of our button: "PRESSED"
 */
const uint8_t PRESSED = LOW;       // Button input pin reads LOW when pressed

void setup() {
  pinMode(LIGHT, OUTPUT);               // LED representing our light (output)
  pinMode(LIGHT_BUTTON, INPUT_PULLUP);  // Button controlling light (input with pull-up resistor)
}

void loop() {
  // now the code tests to see if the pin is PRESSED, which makes more sense!
  if (digitalRead(LIGHT_BUTTON) == PRESSED) {
    digitalWrite(LIGHT, HIGH);
  } else {
    digitalWrite(LIGHT, LOW);
  }
  delay(50);
}
