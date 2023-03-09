/* [Any text between a slash/asterisk and an asterisk/slash is a comment and does not affect the code generated.]
 *
 * Day 0 - AI Apocalypse by inventr.io
 * Learn more at https://inventr.io/PLACEHOLDER
 *
 * A light-emitting diode (LED) is a semiconductor device that emits light
 * when an electric current is passed through it. LEDs are small, efficient,
 * and long-lasting, making them ideal for a wide range of applications such
 * as indicator lights, digital displays, and lighting. They are available
 * in a variety of colors and sizes.
 *
 * Alex Eschenauer
 * David Schmidt
 */

/*
 * Arduino language concepts introduced in this lesson.
 * - Arduino language.  Based on C++.  Optimized for use with microcontrollers and providing a simplified programming
 *   interface for hardware-specific tasks.
 * - Block Comments (like this one)  (https://www.arduino.cc/reference/en/language/structure/further-syntax/blockcomment/)
 * - Single Line comments (https://www.arduino.cc/reference/en/language/structure/further-syntax/singlelinecomment/)
 * - #include (https://www.arduino.cc/reference/en/language/structure/further-syntax/include/)
 * - #define (https://www.arduino.cc/reference/en/language/structure/further-syntax/define/)
 * - const (https://www.arduino.cc/reference/en/language/variables/variable-scope-qualifiers/const/)
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
 *       D13 (this pin controls the build in LED on the HERO XL board (LED_BUILTIN)),
 *       D2-D13, D44-D46 (used for Pulse Width Modulation (PWM))
 *       D50 (MISO), D51 (MOSI), D52 (SCK), D53 (SS).  (used for SPI communication)
 *       D20 (SDA), D21 (SCL).  (used for I2C communication using the Wire library)
 * Recommended for fewest conflicts:
 *    D22-D49
 */

/*
 * Rather than use the same number throughout the sketch we can define the value
 * to a name and use the name wherever we would have used the value.  To indicate
 * that these are read-only, we add the "const" qualifier to the variable declaration.
 * 
 * While "#define" is often used for this type of naming it can sometimes have some
 * bad side effects.  Because of this, const is the preferred way to define constants.
 *  
 * Constants are often in all capital letters to emphasize that they are constants (though
 * this isn't required).
 */ 
const int LIGHT = 22; // Set "LIGHT" to the HERO XL pin connected to the LED cathode (+) lead

// The setup function runs once when the sketch is run.  This is usually used for
// one time initialization.
void setup() {
  // initialize digital pin defined by "LIGHT" as an output pin.
  pinMode(LIGHT, OUTPUT);
}

// The loop function runs over and over again forever
// This loop turns our LIGHT on (HIGH voltage), delays one second, turns it off (LOW voltage)
// and then delays one second.  This loop will repeat forever, blinking our LED on/off.
void loop() {                 // Blocks of code are contained between open and close braces ("{}")
  digitalWrite(LIGHT, HIGH);  // Set our designated LIGHT pin to HIGH value (5V), or "on"
  delay(1000);                // Wait for 1 second (1000 microseconds)

  digitalWrite(LIGHT, LOW);   // Now set our pin to LOW voltage (0V), or "off".
  delay(1000);                // Wait one second.
}                             // When we reach the end of the block of code the loop will repeat
