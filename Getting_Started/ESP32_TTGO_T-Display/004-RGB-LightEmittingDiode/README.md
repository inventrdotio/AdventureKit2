# Light Emitting Diode (LED)

An RGB LED is a light-emitting diode (LED) that can produce a wide range of colors by adjusting the intensity of its red, green, and blue components. This allows for a wide range of colors to be produced by the LED, rather than just a single color as with traditional LEDs.

# Coding
An RGB LED can be easily controlled in an Arduino Mega circuit by connecting the common pin (longest) to GND and each color pin to a digital output pin, using the digitalWrite() function to turn each color on or off. Here is an example of how an RGB LED can be connected and controlled in an Arduino Mega circuit:

# Code
```
constexpr int redPin   = 7;
constexpr int greenPin = 6;
constexpr int bluePin  = 5;

void setup() {
  pinMode(redPin,   OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin,  OUTPUT);
}

void loop() {
  digitalWrite(redPin,   255);  // Red brightness, 0-255
  digitalWrite(greenPin, 255);  // Green brightness, 0-255
  digitalWrite(bluePin,  255);  // Blue brightness, 0-255
}
```

It's important to note that the value of the resistors are important to avoid overloading the LED and burning it out. Usually a value around 220 ohm is a good starting point for a standard LED.

### Wiring
| Arduino | LED |
| --- | --- |
| 7 | RED lead (alone next to GND) |
| GND | common pin (longest) |
| 6 | GREEN lead (between GND and BLUE) |
| 5 | BLUE lead (next to GREEN) |

<img src="RGB-LightEmittingDiode.png" width="350">

### Installation
No libraries or includes required.
