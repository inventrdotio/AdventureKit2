/*
 * Day 0 - AI Apocalypse by inventr.io
 * Learn more at https://inventr.io/product/adventure-kit-2/
 *
 * Our last design used a pull-down resistor to provide a stable input when
 * the button isn't pressed.  Now let's switch our design to use a pull-up
 * resistor and explain the differences.
 *
 * When we switch from using a pull-down to a pull-up resistor in our circuit, 
 * we gain several benefits but also encounter a potential source of confusion.
 *
 * The pull-up resistor is connected between the input pin and +5V. This setup
 * ensures that our input pin defaults to a HIGH state when the button is not
 * pressed, providing a stable signal without floating. The pin is "pulled up"
 * to a known voltage, preventing random fluctuations and making sure it reads
 * HIGH consistently in the absence of a press.
 *
 * The benefit of using a pull-up resistor, especially the built-in ones on the
 * HERO XL, is that it simplifies the circuit. There's no need for an additional
 * external resistor, saving space and components. Additionally, using the internal
 * pull-up allows for a neater setup and can reduce issues with wiring and
 * breadboard contact resistance that might affect the circuit stability.
 *
 * However, this approach inverts the logic of our button press. With a pull-down,
 * a pressed button results in a HIGH signal. With a pull-up, a pressed button
 * connects the input pin to ground, resulting in a LOW signal. This logical
 * inversion might be counterintuitive because we usually associate a button press
 * with a HIGH signal, not LOW.
 *
 * It's essential to account for this inverted logic in our code. We define a 
 * constant like "PRESSED" to equal LOW. This way, when we check the button state 
 * in the code, we can use our "PRESSED" constant, which makes the code more 
 * intuitive and easier to read.
 *
 * Alex Eschenauer
 * David Schmidt
 */

/*
 * Arduino language concepts introduced in this lesson:
 * - INPUT_PULLUP parameter for pinMode() function
 * - Setting a constant to represent PRESSED
 *
 * Hardware concepts introduced in this lesson:
 * - pull-up resistors
 * - built-in pull-up resistor in our HERO-XL
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

/*
 * NOTE: Using a pull-up resistor can cause some confusion because the input pin connected
 *       to our button will read HIGH when the button is NOT pressed, and LOW when the
 *       button IS pressed.  We can reduce this confusion a little by defining a
 *       new constant for the state of our button: "PRESSED"
 */
const uint8_t PRESSED = LOW;  // Button input pin reads LOW when pressed

void setup() {
  pinMode(LIGHT_PIN, OUTPUT);           // LED representing our light (output)
  pinMode(LIGHT_BUTTON, INPUT_PULLUP);  // Button controlling light (input with pull-up resistor)
}

void loop() {
  // now the code tests to see if the pin is PRESSED, which makes more sense!
  if (digitalRead(LIGHT_BUTTON) == PRESSED) {
    digitalWrite(LIGHT_PIN, ON);
  } else {
    digitalWrite(LIGHT_PIN, OFF);
  }

  delay(50);  // short delay to reduce power consumption
}
