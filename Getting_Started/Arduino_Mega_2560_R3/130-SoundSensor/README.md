# Sound Sensor - KY-038

The KY-038 Sound sensor module provides an easy way to detect sound and is generally
used for detecting sound intensity.

### Documentation
[Project Page](https://docs.sunfounder.com/projects/vincent-kit/en/latest/arduino/2.28_sound_sensor_module.html)


```
void loop() {
  int sensorAnalogValue = analogRead(A0);
  Serial.println(sensorAnalogValue);
  delay(1); 
}

```

### Wiring
| Arduino | HC-SR04 |
| --- | -- |
| A0 | A0 |
| GND | GND |
| 5v | VCC |
| 2 | S |

<img src="SoundSensor - KY-038.png" width="500">

### Installation
No libraries required for use.
