/*
Library https://github.com/Arduino-IRremote/Arduino-IRremote
IRremote by shirriff, z3t0, ArminJo
v3.8.0
*/
#include <IRremote.hpp>

int RECV_PIN = 11;

void setup() {
  Serial.begin(115200);
  delay(200);
  Serial.println("Beginning IrReceiver...");
  IrReceiver.begin(RECV_PIN, ENABLE_LED_FEEDBACK);
  Serial.println("IrReceiver started...");
}

void loop() {
  if (IrReceiver.decode()) {
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
    IrReceiver.printIRResultShort(&Serial);
    IrReceiver.resume();  // Receive the next value
  }
}