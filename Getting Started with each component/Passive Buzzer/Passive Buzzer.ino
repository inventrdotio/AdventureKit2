// Passive Buzzer: sample code for Arduino Uno & Arduino Mega
//
// Play 440 Hz tone for 1 second, then no tone for 1 second, and repeat.

const byte          BUZZER_PIN   =    2;  // PWM not needed
const unsigned int  TONE_PITCH   =  440;  // Hz
const unsigned long TONE_LENGTH  = 1000;  // ms
const unsigned long CYCLE_LENGTH = 2000;  // ms

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
}
  
void loop() {
  // Turn buzzer on for TONE_LENGTH ms, off for (CYCLE_LENGTH - TONE_LENGTH) ms.
  tone(BUZZER_PIN, TONE_PITCH, TONE_LENGTH);
  delay(CYCLE_LENGTH);
}