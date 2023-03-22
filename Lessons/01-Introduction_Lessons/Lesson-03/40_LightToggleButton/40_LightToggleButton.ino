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
 * If we connect our input pin to ground through a pull-down resistor then the pin will
 * read LOW when not pressed, and HIGH when pressed.
 *
 * The HERO XL does NOT have a built-in pull-down resistor, so we will use an external
 * 10K resistor as our pull-down resistor.  The pinMode will be set to INPUT because the
 * external resistor will be our pull-down resistor.
 *
 * Alex Eschenauer
 * David Schmidt
 */

/*
 * Arduino language concepts introduced in this lesson.
 *
 *  * Variables
 *  * Variable types
 *  * Variable scope
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
 * NOTE: While HIGH/LOW now make more sense when using a pull-down resistor, it still
 *       makes even MORE clear using PRESSED / NOT_PRESSED.  However, now we set
 *       PRESSED equal to HIGH.
 */
const uint8_t PRESSED = HIGH;     // Button input pin reads LOW when pressed
const uint8_t NOT_PRESSED = LOW;  // Button input pin reads HIGH when NOT pressed

void setup() {
  pinMode(LIGHT, OUTPUT);               // LED representing our light (output)
  pinMode(LIGHT_BUTTON, INPUT_PULLUP);  // Button controlling light (input with pull-up resistor)
}

bool light_on = false;
bool previous_button_state = NOT_PRESSED;

/*
 * In the loop we'll check to see if the button is pressed, and when it's pressed we'll
 * turn on the light.  When released we turn off the light.
 */
void loop() {
  int button_state = digitalRead(LIGHT_BUTTON);
  
  if (button_state != previous_button_state) {
    if (button_state == PRESSED) {
      if (light_on) {
        digitalWrite(LIGHT, LOW);
        light_on = false;
      } else {
        digitalWrite(LIGHT, HIGH);
        light_on = true;
      }
    }
  }
  previous_button_state = button_state;        

  delay(50);
}
