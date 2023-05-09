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
 * cost-effective input device for Arduino projects. It consists of a 4x4 grid of BUTTONS,
 * providing a total of 16 keys. Each key is labeled with a number, letter, or symbol,
 * such as 0-9, A-D, *, and #.
 *
 * Let's make the feedback even better by adding an LCD1602 LCD character display.  That
 * will allow us to give better instructions and feedback as the user enters the secret
 * code.
 *
 * LCD stands for "Liquid Crystal Display." You might have seen these types of screens on
 * calculators, microwaves, or digital clocks. The "1602" part means that this display has
 * 16 columns and 2 rows, so you can show a total of 32 characters at once.
 *
 * The LCD1602 is like a tiny TV screen that shows letters, numbers, and symbols. It has a
 * special controller that helps us communicate with it using our Arduino board. We can
 * send messages to the screen and tell it what to display.
 *
 * Alex Eschenauer
 * David Schmidt
 */

/*
 * Arduino language concepts introduced in this lesson.
 *
 */
#include "Arduino.h"

#include <Keypad.h>         // Library for 4x4 membrane keypad
#include <LiquidCrystal.h>  // LCD1602 library

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

const byte ROWS = 4;
const byte COLS = 4;

const byte ROW_PINS[ROWS] = { 23, 25, 27, 29 };
const byte COL_PINS[COLS] = { 31, 33, 35, 37 };

char BUTTONS[ROWS][COLS] = {
  { '1', '2', '3', 'A' },  // 1st row
  { '4', '5', '6', 'B' },  // 2nd row
  { '7', '8', '9', 'C' },  // 3rd row
  { '*', '0', '#', 'D' }   // 4th row
};

Keypad security_keypad = Keypad(makeKeymap(BUTTONS), ROW_PINS, COL_PINS, ROWS, COLS);

LiquidCrystal lcd(22, 24, 26, 28, 30, 32);

const String SECRET_CODE = "1234";
const int code_indent = (16 - SECRET_CODE.length()) / 2;
String entered_code = "";
String prompt = "Enter Pass Code";

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);   // Set LCD resolution (16 columns, 2 rows)
  lcd.clear();
  showPrompt(prompt);
}

void loop() {
  char key = security_keypad.getKey();

  if (key) {
    Serial.print("Key entered: ");
    Serial.println(key);

    // Reset key
    if (key == '*') {
      Serial.println("Reset: starting over");
      lcd.clear();
      showPrompt(prompt);
      entered_code = "";   // Reset back to starting point (nothing entered yet)
      return;             // exits loops here
    }

    // Delete key
    if (key == '#') {
      Serial.println("Delete last character entered");
      lcd.setCursor(code_indent + entered_code.length() - 1, 1);
      lcd.print(" ");
      entered_code = entered_code.substring(0, entered_code.length() - 1);
      Serial.print("  Current entered code: ");
      Serial.println(entered_code);
      return;
    }

    entered_code += key;

    if (entered_code.length() == 1) {
      Serial.println("A code has begun to be entered");
      lcd.clear();
      showPrompt("Complete code");
    }
    lcd.setCursor(code_indent + entered_code.length() - 1, 1);
    lcd.print("*");

    Serial.print("  Current entered code: ");
    Serial.println(entered_code);

    if (entered_code.length() == SECRET_CODE.length()) {
      Serial.println("Entry complete - validating combination");
      lcd.clear();

      if (entered_code == SECRET_CODE) {
        Serial.println("Entered code matches - unlock door for 2 seconds");
        lcd.print("Door Unlocked");
        delay(2000);
        Serial.println("Re-lock door");
      } else {
        lcd.print("No match");
        lcd.setCursor(0, 1);
        lcd.print("Door is locked");
        Serial.println("Wrong combination entered");
        delay(2000);
        Serial.println("Door locked");
      }
      lcd.clear();
      showPrompt(prompt);
      entered_code = "";
    }
  }
}

void showPrompt(String prompt) {
  int prompt_length = prompt.length();
  Serial.println(prompt.c_str());
  if (prompt_length > 16) {
    Serial.println("Prompt is too long and will be truncated");
    prompt.substring(0, 16);
  }
  int centering_offset = (16 - prompt_length) / 2;
  lcd.setCursor(centering_offset, 0);
  lcd.print(prompt.c_str());
}