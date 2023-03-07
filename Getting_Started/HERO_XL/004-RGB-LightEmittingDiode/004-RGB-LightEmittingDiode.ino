/*
 * Day 0 - AI Apocalypse by inventr.io
 * Learn more at https://inventr.io/PLACEHOLDER
 *
 * Getting Started
 * An RGB LED is a light-emitting diode (LED) that can produce a wide
 * range of colors by adjusting the intensity of its red, green, and
 * blue components. This allows for a wide range of colors to be produced
 * by the LED, rather than just a single color as with traditional LEDs.
 *
 * Adapted for Inventr.io by David Schmidt
 */

constexpr int redPin   = 7;
constexpr int greenPin = 6;
constexpr int bluePin  = 5;

void setup() {
  pinMode(redPin,   OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin,  OUTPUT);
}

void loop() {
  setColor(255, 0, 0); // Red Color
  delay(1000);
  setColor(0, 255, 0); // Green Color
  delay(1000);
  setColor(0, 0, 255); // Blue Color
  delay(1000);
  setColor(255, 255, 255); // White Color
  delay(1000);
  setColor(170, 0, 255); // Purple Color
  delay(1000);
}

void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(redPin,   redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin,  blueValue);
}
