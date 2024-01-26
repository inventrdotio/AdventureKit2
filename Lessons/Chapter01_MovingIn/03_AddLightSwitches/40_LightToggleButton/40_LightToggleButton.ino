/*
 * Day 0 - AI Apocalypse by inventr.io
 * Learn more at https://inventr.io/PLACEHOLDER
 *
 * While our prevous sketches show how we can control the light, we obviously
 * cannot stand and hold the button down to provide our light.  We need a way to
 * turn the light on and LEAVE it on until we turn it off.
 *
 * In our final sketch, we've added an interactive twist to our circuit's behavior.
 * Now, instead of just turning the LED on when the button is pressed, we're going
 * to "toggle" the LED's state each time the button is pressed. This means if the
 * LED is off and the button is pressed, the LED will turn on. If the LED is on and
 * the button is pressed again, it will turn off.
 *
 * This toggle functionality mimics how a traditional light switch works, making our
 * circuit more intuitive and interactive. It's a simple yet effective way to control
 * the LED and also serves as a foundational concept for creating more complex
 * interactions in future projects.
 *
 * To achieve this, we use a boolean variable to remember the current state of the
 * LED. Each time the button is pressed, we check this state: if the LED is on, we
 * turn it off; if it's off, we turn it on. This state is then updated to reflect
 * the new status of the LED, ready for the next button press.
 *
 * This type of control is not only useful for LEDs but can be extended to control
 * other devices, making it a versatile pattern for interactive projects.
 *
 * Alex Eschenauer
 * David Schmidt
 */

/*
 * Arduino language concepts introduced in this lesson:
 * - Variables - a name that points to a storage location where the value can be
 *               both read AND written.
 * - Variable types - variables can have different types which define the range
 *                    of values that can be stored
 * - Variable scope - WHERE in the code that the variables can be read or written.
 *                    Variables are only usable when they "in scope" and are unavailable
 *                    outside of those areas.
 * - boolean values - Only two values allowed, "true" or "false"
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
const uint8_t PRESSED = LOW;       // Button input pin reads LOW when pressed
const uint8_t NOT_PRESSED = HIGH;  // Button input pin reads HIGH when NOT pressed

void setup() {
  pinMode(LIGHT_PIN, OUTPUT);           // LED representing our light (output)
  pinMode(LIGHT_BUTTON, INPUT_PULLUP);  // Button controlling light (input with pull-up resistor)
}

/*
 * Here we'll declare some variables that will keep track of whether the light is on
 * or off and what our button state was the *previous* time our loop() was executed.
 *
 * Declaring a variable means specifying its data type (such as int, float, or char),
 * and giving it a name. The data type determines what kind of information the variable
 * can hold, and the name is used to refer to the variable in your code.
 *
 * To use the least amount of storage possible, we typically declare variables with
 * the smallest type that can hold ALL possible values.  uint8_t is defined as an
 * unsigned (can't be negative) number held in 8 bits.  It can hold values from 0 - 255.
 *
 * Variables have "scope", which refers to the area of the program where a variable is
 * accessible or visible.  There are different types of variable scope:
 *
 * Local scope: A local variable is declared within a function or a block of code
 *              (enclosed by {} braces). It is only accessible within that function
 *              or block, and it's created when the function is called and destroyed
 *              when the function exits.
 *
 * Static local scope: A "static" variable has the same scope as a local variable, but
 *                     the value is kept when the program leaves the scope instead of
 *                     being destroyed.  If execution returns to that local scope the
 *                     previous value can be read.  We don't use a static local in this
 *                     sketch.
 *
 * Global scope: A global variable is declared outside any function or block of code,
 *               usually at the top of the program. It is accessible from any part of
 *               the program, including functions and blocks. Global variables are created
 *               when the program starts.
 *
 * Since these variables need to maintain their state between each execution of loop()
 * we declare them here as Global variables.
 *
 * Variable are named using the same rules as for constant names.  HOWEVER, to make it
 * easier to tell a variable from a constant we will use all LOWER case for variables in
 * this course.  So, when you see capital letters you may assume the value may not change
 * and if in lower case the value *could* be changed.
 */

// Boolean values can be true or false.  The HIGH/LOW constants can also be interpreted
// as booleans (true or false)
bool light_is_on = false;                  // is the light on at first?  false
bool previous_button_state = NOT_PRESSED;  // start out with button NOT pressed

/*
 * In the loop we will check to see if the button has been *changed* since the last
 * time we checked and when the button is first pressed we will "toggle" our light,
 * turning it on if it is off and turning it off if it is on.
 */
void loop() {
  // Since we only use the button state *inside* loop() we declare it here as a local variable.
  uint8_t button_state = digitalRead(LIGHT_BUTTON);  // read current button state and save it

  // first check to see if the button state has changed since last loop()
  if (button_state != previous_button_state) {
    if (button_state == PRESSED) {  // if our NEW state is PRESSED this is a new button press
      // then toggle our light, turning it off if it's on, and on if it's off.
      if (light_is_on) {
        digitalWrite(LIGHT_PIN, OFF);  // Light is on, turn it off
        light_is_on = false;           // ... and save it's new state
      } else {                         // Light must be off
        digitalWrite(LIGHT_PIN, ON);   // turn on light
        light_is_on = true;            // ... and save it's new state
      }
    }
    // Since button state changed, let's save its current state for next time through loop()
    previous_button_state = button_state;
  }

  delay(50);  // short delay to reduce power consumption
}
