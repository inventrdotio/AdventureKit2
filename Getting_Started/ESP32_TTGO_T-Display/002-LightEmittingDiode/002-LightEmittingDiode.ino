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
 *
 * Alex Eschenauer
 * David Schmidt
 */
#include <Arduino.h>

// NOTE: T-Display pins 36-39 are INPUT ONLY and 21-22 are for I2C so avoid those.
const int Light = 32; // The T-Display Pin that the LED is wired to

// The setup function runs once when you press reset or power the board
void setup() {
  // Initialize digital pin (LIGHT) as an output.
  pinMode(Light, OUTPUT);
}

// The loop function runs over and over again forever
void loop() {
  digitalWrite(Light, HIGH);
  delay(1000);
  digitalWrite(Light, LOW);
  delay(1000);
}