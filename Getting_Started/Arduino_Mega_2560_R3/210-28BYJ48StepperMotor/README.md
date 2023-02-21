# 28BYJ-48 Stepper Motor and ULN2003 Stepper Motor Driver

The 28BYJ-48 is a small, low-cost, unipolar stepper motor widely used in hobbyist and DIY projects. It has a step angle of 5.625 degrees and can operate at a voltage of 5VDC. The motor has a total of 5 wires. The red wire is the common wire and is usually connected to the positive terminal, while the other four wires are connected to the ULN2003 driver board.

The ULN2003 driver board is a popular stepper motor driver board that is often used to control the 28BYJ-48 motor. The board contains a ULN2003 integrated circuit, which is a high-voltage, high-current Darlington transistor array. The board has four output pins, which are connected to the 28BYJ-48 motor wires. The board is also equipped with a 5VDC power supply and a set of control pins that are used to send signals to the integrated circuit, controlling the speed and direction of the motor.

### Documentation
* [28BYJ-48 Datasheet](https://www.digikey.com/en/htmldatasheets/production/1839399/0/0/1/28byj-48.html)
* [ULN2003 Datasheet](https://www.electronicoscaldas.com/datasheet/ULN2003A-PCB.pdf)

### Sample Program
```
// Includes the Arduino Stepper Library
#include <Stepper.h>

// Defines the number of steps per rotation
const int stepsPerRevolution = 2038;

// Creates an instance of stepper class
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
Stepper myStepper = Stepper(stepsPerRevolution, 8, 10, 9, 11);

void setup() {
    // Nothing to do (Stepper Library sets pins as outputs)
}

void loop() {
	// Rotate CW slowly at 5 RPM
	myStepper.setSpeed(5);
	myStepper.step(stepsPerRevolution);
	delay(1000);
	
	// Rotate CCW quickly at 10 RPM
	myStepper.setSpeed(10);
	myStepper.step(-stepsPerRevolution);
	delay(1000);
}
```

### Wiring (simplified with no potentiometer or resistor)
| Arduino | ULN2003 |
| -- | -- |
| GND | - |
| 8 | IN1 |
| 9 | IN2 |
| 10 | IN3 |
| 11 | IN4 |


| External +5 supply  | ULN2003 |
| -- | -- |
| GND | - |
| 5v | + |

<img src="28BYJ48StepperMotor.png" width="500">

### Installation
Uses built in Arduino Stepper library
