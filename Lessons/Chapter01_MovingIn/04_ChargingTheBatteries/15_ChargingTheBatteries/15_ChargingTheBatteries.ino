/*
 * Day 0 - AI Apocalypse by inventr.io
 * Learn more at https://inventr.io/product/adventure-kit-2/
 *
 * Charging the Batteries
 *
 * OK, we can see our simulated charge coming in. However, it's not very easy to
 * read because of the way that the Serial Plotter keeps adjusting its minimum
 * and maximum values to keep all the data on the screen.
 *
 * I have an idea. The Serial Plotter can plot *multiple* values at the same
 * time by separating them with commas. Why don't we plot the minimum and
 * maximum values at the same time? That way, each set of values will always
 * have the same minimum and maximum and won't be changing the scale every time.
 *
 * That's MUCH better! Now, we can see our actual charge rate moving somewhere
 * between the minimum (when covered) and the maximum (if we shine a light on
 * the photoresistor).
 *
 * Though we'd like to see the rate of charge in our final display, we'll also
 * be adding in a value to represent the current charge level of our batteries,
 * from 0% to 100%. If our rate of charge was a percentage, then both of the
 * values would fit into the same range.
 *
 * We could convert our charge rate into a percentage, but there's an easier way
 * to "map" a value in one range (0-1023) to the appropriate value in a
 * different range (1-100). The Arduino language provides the "map" function for
 * this purpose. Let's convert the print statements to display our charge rate
 * as a percentage.
 *
 * Great. The plot looks the same, but if you look at the numbers on the left
 * they now show that our values are from 0 to 100, which will allow us to
 * combine the charge rate with our battery level.
 *
 * Once we have more than one number though, how can we tell what each number
 * represents? The only hint we currently have are the labels on the top of the
 * plot that show the color for "value 1", "value 2", etc.
 *
 * The Arduino IDE has solved that problem by allowing you to configure labels
 * for each of the values by adding label text before each value and separating
 * the label from the value with a colon (':').
 *
 * So, instead of each line looking like "0, 100, 43" (but with our actual value
 * at the end) it will look like "0%:0, 100%:100, ChargeRate:43"
 *
 * Alex Eschenauer
 * David Schmidt
 */

/*
 * Arduino language concepts introduced in this lesson:
 * - Analog input pins - Reads values from 0 to 1023
 * - Serial Console - used to display messages from the HERO XL inside the Arduino IDE
 * - Serial Plotter - Can be used to plot values displayed on Serial Console
 * - #define for conditional compilation
 * - #if, #elif, #else, #end - Choosing what code to compile using #define
 * - Placing quotation marks inside strings.
 *
 * Hardware concepts introduced in this lesson:
 */
#include "Arduino.h"

/*
 * Choosing what pin to use.
 * This project uses two digital pins and one analog pin. On the Hero XL we
 * *could* use any digital or analog pin (D0-D53, A0-A15). However, some pins
 * support specialized functions and in later lessons we will be using multiple
 * parts, some of which will use some of those special functions. So, let's start
 * out on the right foot by trying to use the most basic pin we can for each of
 * our parts.
 *
 * Skip: A0-A15 (save for Analog),
 *       D0/D1 (used by USB and Serial)
 *       D14-D19 (used by Serial 1-3)
 *       D2/D3, D18-D21 (used for external interrupts)
 *       D13 (this pin controls the build in LED on the HERO XL board (LED_BUILTIN)),
 *       D2-D13, D44-D46 (used for Pulse Width Modulation (PWM))
 *       D50 (MISO), D51 (MOSI), D52 (SCK), D53 (SS).  (used for SPI communication)
 *       D20 (SDA), D21 (SCL).  (used for I2C communication using the Wire library)
 *
 * Recommended for fewest conflicts:
 *    D22-D43, D47-D49, A8-A15
 */
const uint8_t LIGHT_PIN = 22;      // LED on pin 22
const uint8_t LIGHT_BUTTON = 23;   // Button (light switch) on pin 23
const uint8_t CHARGING_RATE = A8;  // Photoresistor input simulating battery charge rate

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
  // Intialize Serial class, used to communicate with the Arduino IDE Serial Monitor
  Serial.begin(9600);  // Initialize Serial, set speed to 9600 bits/second (baud)
  while (!Serial) {
    ;  // wait for serial port to connect.
  }
  pinMode(LIGHT_PIN, OUTPUT);           // LED representing our light (output)
  pinMode(LIGHT_BUTTON, INPUT_PULLUP);  // Button controlling light (input with pull-up resistor)
  pinMode(CHARGING_RATE, INPUT);        // Photoresistor analog input
}

bool light_on = false;                     // we start with the light turned off
bool previous_button_state = NOT_PRESSED;  // start out with button NOT pressed

/*
 * Earlier in this course we explained that there were two ways of defining
 * constants in the Arduino Language and explained that the older "#define"
 * could sometimes cause problems and that we'd be using "const" instead.
 *
 * However, there are times when #define is appropriate and here we'll show
 * one of them.  #define and const do their jobs at different points while
 * building our code. #define is like an editor.  It operates during the first
 * phase of compiling and modifies the text before the compiler starts.
 *
 * We use this here to decide which version of the print statements we'll
 * use when we build.  Simply change the #define below to set which version
 * of our prints will be used.
 */
#define WHICH_PRINT 1  // Set to 1, 2 or 3 then build/upload the sketch again

void loop() {
  int current_charging_rate = analogRead(CHARGING_RATE);  // Read "charging rate" from our photoresistor (0-1023)

  /*
   * Output the numbers we wish to plot using the Serial Plotter.
   * The first two numbers are just to show the 0% and 100% charged points
   * so the plotter won't continuously change the scale.
   */
#if WHICH_PRINT == 1
  // Print something like "0, 1023, 432" on each line
  Serial.print(0);
  Serial.print(", ");
  Serial.print(1023);
  Serial.print(", ");
  Serial.println(current_charging_rate);  // .println() will add a "newline" on the end
#elif WHICH_PRINT == 2
  // Print something like "0, 100, 43" on each line
  Serial.print(0);
  Serial.print(", ");
  Serial.print(100);
  Serial.print(", ");
  Serial.println(map(current_charging_rate, 0, 1023, 0, 100));
#else
  /*
   * Create a plot label by placing it immediately before its value and separating
   * the label from the value with a ':'. There can be no spaces next to the ':' or
   * between words in the label (use '_' to separate words).
   *
   * This gives us a line like "0%:0, 100%:100, Charge_Rate:43"
   */
  Serial.print("0%:");  // Label for  0% charge
  Serial.print(0);
  Serial.print(", 100%:");  // Label for  100% charge
  Serial.print(100);
  Serial.print(", Charge_Rate:");  // Label for battery_charge_percentage
  Serial.println(map(current_charging_rate, 0, 1023, 0, 100));
#endif

  uint8_t button_state = digitalRead(LIGHT_BUTTON);  // read current button state and save it

  // first check to see if the button state has changed since last loop()
  if (button_state != previous_button_state) {
    if (button_state == PRESSED) {  // if our NEW state is PRESSED this is a new button press
      // then toggle our light, turning it of if it's on, and on if it's off.
      if (light_on) {
        digitalWrite(LIGHT_PIN, OFF);  // Light is on, turn it off
        light_on = false;              // ... and save it's new state
      } else {                         // Light must be off
        digitalWrite(LIGHT_PIN, ON);   // turn on light
        light_on = true;               // ... and save it's new state
      }
    }
    // Since button state changed, let's save its current state for next time through loop()
    previous_button_state = button_state;
  }

  delay(50);
}
