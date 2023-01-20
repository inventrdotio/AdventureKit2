#include <BasicEncoder.h>
 
// Rotary Encoder Inputs
constexpr int CLK = 2;  // Intr 5
constexpr int DT = 3;   // Intr 4
constexpr int SW = 18;  // Intr 3

int previousCounter = 0;

// Create RotaryEncoder instance (which initializes counter to 0)
BasicEncoder encoder(CLK, DT);

void setup() {
  pinMode(SW, INPUT_PULLUP);
  // Setup Serial Monitor
  Serial.begin(115200);
  delay(1000);
  Serial.print("Counter: ");
  Serial.println(encoder.get_count());
  // Call Interrupt Service Routine (ISR) updateEncoder() when any high/low change
  // is seen on A (CLK) interrupt  (pin 2), or B (DT) interrupt (pin 3)
  attachInterrupt(digitalPinToInterrupt(CLK), updateEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(DT), updateEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(SW), updateSwitch, CHANGE);
}

void loop() {
  if (encoder.get_change()) {
    int counter = encoder.get_count();
    Serial.print("Counter: ");
    Serial.println(counter);
 
    // Since BasicEncoder can be clicked multiple times per loop via interrupts we
    // track when counter has passed milestones THIS time through the loop.  We do
    // by testing whether the previous counter was less than the milestone and current
    // counter is greater or equal.

    // Here are three spots where we *stop* the count until the rotary button is pressed
    // (press down on stem).
    if(previousCounter < 10 && counter >= 10) {
      Serial.println("---------->STOPPED AT 10!");
    }
 
    if(previousCounter < 20 && counter >= 20) {
      Serial.println("---------->STOPPED AT 20!");
    }
 
    if(previousCounter < 30 && counter >= 30) {
      Serial.println("---------->STOPPED AT 30!");
    }

    previousCounter = counter;  // save counter for next time through the loop
  }
  // Serial.print("  switch: ");
  // Serial.println(digitalRead(SW));
  // delay(1000);
}

void updateEncoder() {
  encoder.service();
}

// Track switch state change 
bool pressed = false;
void updateSwitch() {
  if (pressed && digitalRead(SW) == HIGH) {
    Serial.println("SWITCH RELEASED");
    pressed = false;
    delay(50);  // debounce
  }
  if (!pressed && digitalRead(SW) == LOW) {
    Serial.println("SWITCH PRESSED");
    pressed = true;
    delay(50);  // debounce
  }
}