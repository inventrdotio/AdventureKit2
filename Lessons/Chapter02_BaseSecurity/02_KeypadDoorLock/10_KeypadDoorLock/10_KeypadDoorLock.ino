/*
 * Day 0 - AI Apocalypse by inventr.io
 * Learn more at https://inventr.io/PLACEHOLDER
 *
 * The door locks work, but again they were controlled by the building AI that’s been
 * disabled.  We can lock the doors when we’re here, but it takes too long to have
 * someone come open the door, and what do we if we all have to go out at the same
 * time?  Let’s work on a way to unlock the doors from the outside using the keypads
 * next to each door.
 *
 * The 4x4 Matrix Array Membrane Switch Keypad used in the sketches is a simple and
 * cost-effective input device for Arduino projects. It consists of a 4x4 grid of buttons,
 * providing a total of 16 keys. Each key is labeled with a number, letter, or symbol,
 * such as 0-9, A-D, *, and #.
 *
 * The keypad has an 8-pin interface that simplifies connecting it to an Arduino board.
 * Internally, the keys are arranged in rows and columns, with one side of each button
 * connected to a row line and the other side connected to a column line. When a button
 * is pressed, it connects a specific row and column, creating a closed circuit.
 *
 * Here's a brief overview of the keypad's features:
 *
 * 1) 4 rows and 4 columns, providing a total of 16 keys.
 * 2) Compact and flexible membrane design, making it easy to integrate into various projects.
 * 3) 8-pin interface, simplifying connection to an Arduino board.
 * 4) Can be easily programmed using the pre-loaded Keypad library.
 *
 * Alex Eschenauer
 * David Schmidt
 */

/*
 * Arduino language concepts introduced in this lesson.
 *
 * - Potentiometer
 * - Pulse Width Modulation (PWM)
 */
#include "Arduino.h"
/*
 * The Keypad library is built using classes, which are a core concept in object-oriented
 * programming (OOP). Classes provide a way to bundle data and functions that operate on
 * that data within a single unit, making it easier to design, develop, and maintain code.
 */
#include <Keypad.h>  // Keypad library is already included with the Arduino IDE

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
 *    D22-D43, D47-D49, A8-A15
 */

// Define number of ROWS and COLUMNS to use on our 4x4 keypad
const byte ROWS = 4;
const byte COLS = 4;

// Define all pins used by our keypad.  For ease of wiring use pins in a single line
// on the end of our HERO XL.
byte rowPins[ROWS] = { 23, 25, 27, 29 };
byte colPins[COLS] = { 31, 33, 35, 37 };

// Define which characters will be returned to the sketch when each button
// is pressed.  These values just match the labels for minimum confusion.
char buttons[ROWS][COLS] = {
  { '1', '2', '3', 'A' },  // 1st row
  { '4', '5', '6', 'B' },  // 2nd row
  { '7', '8', '9', 'C' },  // 3rd row
  { '*', '0', '#', 'D' }   // 4th row
};

/*
 * In the context of the Keypad library, the main class is the Keypad class. This class
 * encapsulates the functionality required to interface with a keypad, including reading
 * key presses and handling the keypad's rows and columns. When you create an instance of
 * the Keypad class, you need to provide the key mapping, row pins, column pins, and the
 * number of rows and columns as parameters.
 */
Keypad securityKeypad = Keypad(makeKeymap(buttons), rowPins, colPins, ROWS, COLS);

// Define our unlock combination here.  For testing we'll use a 4 digit code, but
// the code will automatically use whatever length set here.  We will use the String
// class as it provides a convenient way to handle, manipulate, and store sequences of
// characters, such as the entered code in this sketch.  The String class is part of
// the Arduino library.
const String correctCode = "1234";

String enteredCode = "";

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Get a key if one has been pressed (returns 0/false when no key pressed)
  char key = securityKeypad.getKey();

  // If a keypad button has been pressed, handle it here
  if (key) {
    enteredCode += key;   // Add key to the end of our entered combination
    Serial.print("Key entered: ");
    Serial.println(key);

    // Log when someone begins to enter a combination
    if (enteredCode.length() == 1) {
      Serial.println("A code has begun to be entered");
    }

    // If we have collected enough characters compare to the unlock code
    if (enteredCode.length() == correctCode.length()) {
      Serial.println("Entry complete - validating combination");

      if (enteredCode == correctCode) {   // Correct code entered!
        Serial.println("Entered code matches - unlock door for 2 seconds");
        delay(2000);
        Serial.println("Re-lock door");
      } else {
        Serial.println("Wrong combination entered");
      }
      enteredCode = "";   // clear code so user can try again
    }
  }
}