/*
 * PIR HCSR501 or HW-416-B
 */

int pirPin = 2;   // PIR Out pin

bool detected = false;

void setup() {
  Serial.begin(115200);
  pinMode(pirPin, INPUT);
}

int counter = 0;
void loop() {
  int pirStat = digitalRead(pirPin);
  if (pirStat == HIGH && !detected) {   // if motion detected (output LOW!)
    detected = true;
    counter = 0;
    Serial.println("\nMotion Detected!!!");
  }
  if (pirStat == LOW && detected) {     // Previous detection has timed out
    detected = false;
    Serial.println("  All quiet now...");
    Serial.println();
  }
  if (detected) {
    Serial.print("status: ");
    Serial.print(pirStat);
    Serial.print(" at ");
    Serial.println(counter++);
  }
  delay(1000);
}
