# Ultrasonic Sensor (HC-SR04)

5V part that sends out Ultrasonic pulses on command and measures the time for pulses to return.  This can be
converted to distance using the known speed of sound.

### Documentation
[Datasheet](https://www.digikey.com/htmldatasheets/production/1979760/0/0/1/hc-sr04.html?utm_adgroup=xGeneral&utm_source=google&utm_medium=cpc&utm_campaign=Dynamic%20Search_EN_Product&utm_term=&utm_content=xGeneral&gclid=CjwKCAiA7vWcBhBUEiwAXieItmiV1HisDe1lrC3roUqphgozTWCNb_76oSRSCNBINjhAYC_FHvfOxRoCZW0QAvD_BwE)


```
constexpr uint8_t echoPin = 12  // attach pin D12 Arduino to pin Echo of HC-SR04
constexpr uint8_t trigPin = 13  //attach pin D13 Arduino to pin Trig of HC-SR04

long duration; // variable for the duration of sound wave travel

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
}
```

### Wiring
| Arduino | HC-SR04 |
| --- | -- |
| 5v | Vcc |
| GND | Gnd |
| 13 | Trig |
| 12 | Echo |

<img src="UltrasonicSensor-HC-SR04.png" width="500">

### Installation
No libraries required for use.
