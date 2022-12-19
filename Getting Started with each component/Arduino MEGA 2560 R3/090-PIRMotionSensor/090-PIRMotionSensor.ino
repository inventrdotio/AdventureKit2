/*
PIR HCSR501 or HW-416-B
modified on 5 Feb 2019
by Saeed Hosseini @ ElectroPeak
https://electropeak.com/learn/guides/
*/
int pirPin = 2;   // PIR Out pin
int pirStat = 0;  // PIR status
long startTime;
bool idle = true;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(pirPin, INPUT);
  Serial.begin(115200);
  startTime = millis();
}
void loop() {
  float seconds = float(millis() - startTime) / 1000.0;
  Serial.print(seconds);
  Serial.print(" seconds.");
  pirStat = digitalRead(pirPin);
  if (pirStat == HIGH && !idle) {         // if motion detected
    digitalWrite(LED_BUILTIN, HIGH);  // turn LED ON
    digitalWrite(12, HIGH);
    Serial.println(" Hey I got you!!!");
  } else {
    idle = false;
    startTime = millis();
    Serial.println();
    digitalWrite(LED_BUILTIN, LOW);  // turn LED OFF if we have no motion
    digitalWrite(12, LOW);
  }
  Serial.print("\r");
  delay(200);
}