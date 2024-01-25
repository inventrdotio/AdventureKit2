/* [Any text between a slash/asterisk and an asterisk/slash is a comment 
 *  that does not affect the code generated.]
 *
 * Day 0 - AI Apocalypse by inventr.io
 * Learn more at https://inventr.io/product/adventure-kit-2/
 *
 * While the walls at the old inventr.io site will give us better security,
 * there aren't as many windows here so some of the rooms get pretty dark.
 *
 * The solar panels on the roof appear to be producing current so I've wired
 * them directly into the building electrical system. They'll only give us power
 * during the day, but it's a start.
 *
 * I've disabled the light switches that the office AI used to operate so
 * we'll have to use the HERO XL to control the lights.
 *
 * Let's get started.
 *
 * The lights in the building are all efficient LED lights (can you believe
 * they used to used to produce light by making a piece of wire glow?).
 *
 * Let's wire up one of these small LED's we found as we build our new light
 * controller.  Then we can wire the HERO XL directly to our building lights
 * once we have it working.
 *
 * A light-emitting diode (LED) is a semiconductor device that emits light
 * when an electric current is passed through it. LEDs are small, efficient,
 * cool and long-lasting, making them ideal for a wide range of applications such
 * as indicator lights, digital displays, and lighting. They are available
 * in a variety of colors and sizes.
 *
 * Alex Eschenauer
 * David Schmidt
 */

/* 
 * Parts List:
 * 1. Inventrio HERO XL: A variant of the Arduino MEGA 2560, providing numerous I/O pins 
 *    for complex projects.
 * 2. Breadboard: A platform for constructing a temporary prototype electronic circuit 
 *    and experimenting without the need for soldering.
 * 3. Jumper Wires: Wires that are used to make connections between the components 
 *    on the breadboard and the Arduino HERO XL.
 * 4. LED: A light-emitting diode (any color LED with two leads)
 * 5. Resistor: A 220 ohm resistor to limit the current through the LED, thereby
 *    protecting it. 
 */

/*
 * Arduino language concepts introduced in this lesson:
 * - Arduino language.  Based on C++.  Optimized for use with microcontrollers
 *   and providing a simplified programming interface for hardware-specific tasks.
 * - Block Comments (like this one)
 *   (https://www.arduino.cc/reference/en/language/structure/further-syntax/blockcomment/)
 * - Single Line comments
 *   (https://www.arduino.cc/reference/en/language/structure/further-syntax/singlelinecomment/)
 * - #include
 *   (https://www.arduino.cc/reference/en/language/structure/further-syntax/include/)
 * - #define - defines a constant or creates a short macro
 *             (https://www.arduino.cc/reference/en/language/structure/further-syntax/define/)
 * - '=' - Assignment operator which evaluates the right side and assigns it to name on the left
 *         (https://www.arduino.cc/reference/en/language/structure/arithmetic-operators/assignment/)
 * - const - newer and recommended way to define constants
 *           (https://www.arduino.cc/reference/en/language/variables/variable-scope-qualifiers/const/)
 * - unsigned char - an 8 bit, positive value large enough to store an ASCII character or
 *                   a numeric value from 0-255
 * - uint8_t - another name for "unsigned char".  A better name when the value will be
 *             used as a number instead of an alphanumeric character.
 * - pinMode() - instruct program how a pin will be used and whether it will be written to
 *               or read from.
 *               (https://www.arduino.cc/reference/en/language/functions/digital-io/pinmode/)
 * - digitalWrite() - write a value to an output pin
 *                    (https://www.arduino.cc/reference/en/language/functions/digital-io/digitalwrite/)
 * - delay() - pause execution of the program for a set period of time
 *             (https://www.arduino.cc/reference/en/language/functions/time/delay/)
 *
 * Hardware concepts introduced in this lesson:
 * - Breadboard - Used to easily create circuits without permanent soldering
 * - Jumper wires - used to create connections between HERO XL and other devices
 * - LEDs (Light Emitting Diodes)
 */

/*
 * #include is used to include code and defines from other files.  While Arduino automtically
 * includes "Arduino.h", other IDEs do not so it's a good idea to include it at the top of
 * all of your Arduino sketches.
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

/*
 * We *could* just use a number in our code whenever we need to control a pin, but
 * that would make it very tedius if the pin number needs to change.  We'd have to
 * go through all of our code and change each line that contained that pin number.
 *
 * We'd also risk accidently changing code that happened to use the SAME number, but
 * for something other than a pin number.
 *
 * The Arduino Language (C++) provides a way to avoid these issues by letting us
 * define a name in our code and assign it a value.  Then we just use the name instead
 * of that value whenever we need that value.  If the value changes, we only have
 * to change it in ONE place.
 *
 * This also makes our code more understandable.  Which of these commands is easier to
 * understand, "digitalWrite(22, 1)" or "digitalWrite(LIGHT_PIN, ON)"?
 *
 * We can assign (using the '=' operator) values to constants (values that cannot change
 * during program execution) or variables (names that can be assigned new values during
 * program execution).
 *
 * To indicate a value that cannot change we preface the name with "const" to indicate
 * that this is a constant that will not change.
 *
 * While "#define" is often used for this type of naming it can sometimes have some
 * bad side effects.  Because of this, const is the preferred way to define constants.
 *  
 * Constants are often in all capital letters to emphasize that they are constants (though
 * this isn't required).
 */
const uint8_t LIGHT_PIN = 22;  // Create the constant "LIGHT_PIN" defining pin connected to our LED

// Set up two constants so that we can turn our light "on" or "off".
const uint8_t ON = HIGH;  // HIGH is defined in Arduino.h to output 5 volts to a pin
const uint8_t OFF = LOW;  // LOW is defined to turn a pin "off" (low voltage)

// The setup function runs once when the sketch is run.  This is usually used for
// one time initialization.
void setup() {
  pinMode(LIGHT_PIN, OUTPUT);  // instruct HERO XL that LIGHT_PIN will be used for output
}

// The loop function runs over and over again forever
// This loop turns our light on (HIGH voltage), delays one second, turns it off (LOW voltage)
// and then delays one second.  This loop will repeat forever, blinking our LED on/off.
void loop() {                   // Blocks of code are contained between open and close braces ("{}")
  digitalWrite(LIGHT_PIN, ON);  // Turn our designated LIGHT_PIN pin ON ("HIGH", or 5V)
  delay(1000);                  // Wait for 1 second (1000 microseconds)

  digitalWrite(LIGHT_PIN, OFF);  // Now turn our pin to OFF ("LOW" or 0V)
  delay(1000);                   // Wait one second.
}  // When we reach the end of the block of code the loop will repeat
