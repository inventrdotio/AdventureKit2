/*
 * Day 0 - AI Apocalypse by inventr.io
 * Learn more at https://inventr.io/PLACEHOLDER
 *
 * Getting Started
 * A light-emitting diode (LED) is a semiconductor device that emits light
 * when an electric current is passed through it. LEDs are small, efficient,
 * and long-lasting, making them ideal for a wide range of applications such
 * as indicator lights, digital displays, and lighting. They are available
 * in a variety of colors and sizes.
 *
 * Most of our controllers have a built in LED (LED_BUILTIN) that can be controlled.
 * This program flashes that built in LED to verify that we are able to write, build
 * and run programs on our board.
 *
 * Alex Eschenauer
 * David Schmidt
 */

#include <arduino.h>

// HIGH and LOW are defined by the Arduino IDE, but let's use ON and OFF for our LED lights.
// This is often done using "#define", but a cleaner way is to define a "constant" variable;
// one that cannot be changed once it is defined.
// Here we define them as unsigned 8 bit integers (which is the type used by digitalWrite() below)
const uint8_t ON  = HIGH;  // Set our "ON" state to a HIGH voltage
const uint8_t OFF = LOW;   // Set "OFF" to be a LOW voltage

// The setup function runs once when you press reset or power the board
void setup() {
  // LED_BUILTIN is defined by the IDE when you select your Arduino type
  // This LED is considered an OUTPUT device, so let's configure that during setup()
  pinMode(LED_BUILTIN, OUTPUT);
}

// The loop function is executed repeatedly until the board is turned off, reset or until
// another program is uploaded.
void loop() {
  // Now that setup() has completed, let's make the built in LED blink repeatedly by turning it on
  // for one second and then off for one second in our program's loop() function.

  // digitalWrite() sets a pin's voltage to either 0 (LOW/OFF) or 5v (HIGH/ON).  If you hover
  // your mouse cursor over "digitalWrite" a popup will appear describing the function's required
  // input and output parameters.  If you hover your mouse over "LED_BUILTIN" you will see which
  // pin the current board uses for the builtin LED.  If you hover your mouse over "ON", you will
  // see that ON is defined as 1 and our comment from the line above is shown!
   digitalWrite(LED_BUILTIN, ON); // turn the built in LED on

   // Our goal is to "blink" the LED.  Turning it on for 1 second and then off for one second.
   // for this we use the delay() function.  This function causes progress to be suspended
   // for a period of time specified in milliseconds (thousandths of a second).  In order to
   // delay for one second, we delay 1000 milliseconds.
   delay(1000);   // program pauses 1 second (1000 milliseconds)

   // The LED was turned on with the first digitalWrite().  After leaving it on one second
   // we will turn it off here.
   digitalWrite(LED_BUILTIN, OFF); // turn the LED off, using our constant defined above

   delay(1000);   // Leave LED off for 1 second (1000 milliseconds)
}
