#include "Arduino.h"

void setup() {
  pinMode(2,INPUT);
  Serial.begin(115200);
}
int max = 0;
void loop() {
  int sensorDigitalValue= digitalRead(2);
  int sensorAnalogValue = analogRead(A0);
  if (sensorAnalogValue > max) max = sensorAnalogValue > 100 ? 100 : sensorAnalogValue;
//  Serial.print("Digital Reading: ");
  Serial.print(sensorDigitalValue);
  Serial.print(", ");
  Serial.print(sensorAnalogValue);
  Serial.print(", ");
  Serial.println(max);
  delay(1); 
}
