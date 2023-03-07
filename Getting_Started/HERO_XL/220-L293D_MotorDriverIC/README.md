# L293D Motor Driver IC chip

The L293D is a popular integrated circuit (IC) that is commonly used to drive DC motors or stepper motors in a variety of applications. It is a dual H-bridge motor driver, which means it can drive two DC motors or one stepper motor bi-directionally. The L293D IC is designed to handle a wide range of voltages (up to 36V) and can supply a maximum current of 600mA per channel (1.2A peak).

The L293D has 16 pins and comes in a 16-pin dual in-line package (DIP). The pins are divided into two sets, one for each H-bridge, and each set includes an enable pin, two input pins, and two output pins. The enable pin is used to turn the H-bridge on or off, while the input pins control the direction and speed of the motor. The output pins are connected to the motor and provide the power needed to turn it.

The L293D IC also has built-in protection features such as thermal shutdown and over-current protection to prevent damage to the IC or the motors. It is a versatile and widely used motor driver IC that can be found in many hobbyist and industrial applications.

### Documentation
* [L293D Datasheet](https://www.ti.com/lit/ds/symlink/l293.pdf)

### Sample Program
```
const int motorPin1 = 5;  // Pin 14 of L293
const int motorPin2 = 6;  // Pin 10 of L293

void setup() {
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
}

void loop() {
    // This code  will turn Motor A clockwise for 2 sec.
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
    delay(2000);

    // This code will turn Motor A counter-clockwise for 2 sec.
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, HIGH);
    delay(2000);

    // And this code will stop motors
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
    delay(2000);
  }
}
```

### Wiring (simplified with no potentiometer or resistor)
| Arduino | L293D |
| -- | -- |
| GND | 1 |
| 8 | 2 |
| 8 | 3 |
| GND | 4 |
| GND | 5 |
| 8 | 6 |
| 8 | 7 |
| 8 | 8 |


| External +5 supply  | ULN2003 |
| -- | -- |
| GND | - |
| 5v | + |

<img src="L293D_MotorDriverIC.png" width="500">

### Installation
Uses built in Arduino Stepper library
