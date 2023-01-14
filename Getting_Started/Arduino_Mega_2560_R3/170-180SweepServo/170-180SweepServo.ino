// Set up the servo motor
#include <Servo.h>
Servo myservo;

void setup() {
    myservo.attach(9);
}

void loop() {
  // Make the servo rotate from 0 to 180 degrees, then back
    for (int i = 0; i < 180; i++) {
        myservo.write(i);
        delay(15);
    }
    for (int i = 180; i > 0; i--) {
        myservo.write(i);
        delay(15);
    }
}