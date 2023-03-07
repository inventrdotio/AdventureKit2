// L293D
// Motor A
const int motorPin1 = 5;  // Pin 14 of L293
const int motorPin2 = 6;  // Pin 10 of L293

// This will run only one time.
void setup() {
  // Set pins as outputs
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
}

void loop() {
  for (int i = 0; i < 5; i++) {
    // Motor Control - Motor A: motorPin1,motorpin2
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
    delay(1000);
  }
}