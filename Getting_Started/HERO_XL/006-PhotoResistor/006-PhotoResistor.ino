/*
 * Day 0 - AI Apocalypse by inventr.io
 * Learn more at https://inventr.io/PLACEHOLDER
 *
 * Getting Started
 * A photo resistor, also known as a light-dependent resistor (LDR), is a type of
 * resistor whose resistance varies based on the amount of light it is exposed to.
 *
 * Photo resistors are typically made from a semiconductor material, such as cadmium
 * sulfide, that changes its electrical conductivity when exposed to light. They are
 * often used in light-sensitive applications, such as street lights and camera flash
 * units, to control the amount of electrical current flowing through a circuit.
 *
 * Adapted for Inventr.io by David Schmidt
 */

int sensorPin  = A0;          // select an Analog input pin for reading the photo resistor value
int onboardLED = LED_BUILTIN; // select the pin for the HERO's built-in LED

void setup() {
  Serial.begin(115200);
  pinMode(onboardLED, OUTPUT);
}

void loop() {
  // Read and save the analog sensor value
  int sensorValue = analogRead(sensorPin);
  // Print value to console
  Serial.println(sensorValue);

  // Pulse the builtin LED for a time determined by the sensor
  digitalWrite(onboardLED, HIGH);
  delay(sensorValue);
  digitalWrite(onboardLED, LOW);
  delay(sensorValue);
}