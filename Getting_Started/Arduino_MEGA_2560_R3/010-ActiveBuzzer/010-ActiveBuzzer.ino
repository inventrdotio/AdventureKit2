// Active Buzzer: sample code for Arduino Uno & Arduino Mega
//
// Turn buzzer on for 1 second, then off for 1 second, and repeat.

const byte          BUZZER_PIN =    2;  // PWM not needed
const unsigned long ON_LENGTH  = 1000;  // ms
const unsigned long OFF_LENGTH = 1000;  // ms

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
}
  
void loop() {
  // Turn buzzer on for ON_LENGTH ms.
  digitalWrite(BUZZER_PIN, HIGH);
  delay(ON_LENGTH);
  // Turn buzzer off for OFF_LENGTH ms.
  digitalWrite(BUZZER_PIN, LOW);
  delay(OFF_LENGTH);
}