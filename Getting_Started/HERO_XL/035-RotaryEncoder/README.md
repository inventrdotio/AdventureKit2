# Rotary Encoder (KY-040)

A rotary encoder is a type of position sensor that converts the angular position (rotation) of a knob into an output signal that is used to determine which direction the knob is being turned.

### Code Example

```
#include <BasicEncoder.h>
 
// Rotary Encoder Inputs
constexpr int CLK = 2;
constexpr int DT = 3;
constexpr int SW = 4;

// Create RotaryEncoder instance (which initializes counter to 0)
BasicEncoder encoder(CLK, DT);

void setup() {
  pinMode(CLK, INPUT);
  pinMode(DT,  INPUT);
  pinMode(SW,  INPUT);
}

void loop() {
  if (encoder.get_change()) {
    int counter = encoder.get_count();
    ...
  }
  if (digitalRead(SW) == LOW) {
    // Button was pressed
  }
}
```

### Wiring
| Arduino | Potentiometer |
| --- | --- |
| GND | GND |
| 5v | + |
| 4 | SW |
| 3 | DT |
| 2 | CLK |

<img src="RotaryEncoder.png" width="350">

### Installation
Install RotaryEncoder library from Arduino IDE Library Manager
