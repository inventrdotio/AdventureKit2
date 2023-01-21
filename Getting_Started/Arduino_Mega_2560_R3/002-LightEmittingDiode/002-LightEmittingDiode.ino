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
 * Alex Eschenauer
 * David Schmidt
 */

int Light = 13; // The HERO Board Pin that the LED is wired to

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(Light, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(Light, HIGH);
  delay(1000);
  digitalWrite(Light, LOW);
  delay(1000);
}