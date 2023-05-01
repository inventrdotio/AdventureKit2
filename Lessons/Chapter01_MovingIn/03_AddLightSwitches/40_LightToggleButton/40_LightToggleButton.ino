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
 * We're using the built-in pull-up resistor in the HERO XL, so our pin connected to the
 * button will read HIGH when button is NOT pressed, and LOW when button is pressed.
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
const uint8_t PRESSED = LOW;       // Button input pin reads LOW when pressed
const uint8_t NOT_PRESSED = HIGH;  // Button input pin reads HIGH when NOT pressed

/*
 * Here we'll declare some variables that will keep track of whether the light is on
 * or off and what our button state was the *previous* time our loop() was executed.
 *
 * Declaring a variable means specifying its data type (such as int, float, or char),
 * and giving it a name. The data type determines what kind of information the variable
 * can hold, and the name is used to refer to the variable in your code.
 *
 * To use the least amount of storage possible, we typically declare variables with
 * the smalledt type that can hold ALL possible values.  uint8_t is defined as an
 * unsigned (can't be negative) number held in 8 bits.  It can hold values from 0 - 255.
 *
 * Variables have "scope", which refers to the area of the program where a variable is
 * accessible or visible.  There are two primary types of variable scope:
 *
 * Local scope: A local variable is declared within a function or a block of code
 * (enclosed by {} braces). It is only accessible within that function or block,
 * and it's created when the function is called and destroyed when the function exits.
 *
 * Global scope: A global variable is declared outside any function or block of code,
 * usually at the top of the program. It is accessible from any part of the program,
 * including functions and blocks. Global variables are created when the program starts.
 *
 * Since these variables need to maintain their state between each execution of loop()
 * we declare them here as Global variables.
 */
bool light_on = NOT_PRESSED;               // we start with the light turned off
bool previous_button_state = NOT_PRESSED;  // start out with button NOT pressed

void setup() {
  pinMode(LIGHT, OUTPUT);               // LED representing our light (output)
  pinMode(LIGHT_BUTTON, INPUT_PULLUP);  // Button controlling light (input with pull-up resistor)
}

/*
 * In the loop we'll check to see if the button has *just* been pressed or released and
 * when it's pressed we'll toggle the light on/off.
 */
void loop() {
  // Since we only use the button state *inside* loop() we declare it here as a local variable.
  uint8_t button_state = digitalRead(LIGHT_BUTTON);  // read current button state and save it
  
  // first check to see if the button state has changed since last loop()
  if (button_state != previous_button_state) {
    if (button_state == PRESSED) {  // if our NEW state is PRESSED this is a new button press
      // then toggle our light, turning it of if it's on, and on if it's off.
      if (light_on) {
        digitalWrite(LIGHT, LOW);   // Light is on, turn it off
        light_on = false;           // ... and save it's new state
      } else {                      // Light must be off
        digitalWrite(LIGHT, HIGH);  // turn on light
        light_on = true;            // ... and save it's new state
      }
    }
    // Since button state changed, let's save its current state for next time through loop()
    previous_button_state = button_state;
  }

  // This delay isn't strictly necessary, but if we let the loop() run as quickly as it can
  // then we will use more power than necessary.  Let's check for a change in the button
  // state ever 20th of a second (1000 milliseconds / 20 = 50 milliseconds).  That is fast
  // enough that it will appear instantaneous to our users.
  delay(50);
}
