/*
  We'd best begin by making sure this device will even power up and accept programs.  Let's tell the
  board to blink it's built in Light Emitting Diode (LED) to check to see if everything is OK.
*/
#include <arduino.h>

// HIGH and LOW are defined by the Arduino IDE, but let's use ON and OFF for our LED lights.
constexpr uint8_t ON  = HIGH;  // Set our "ON" state to a HIGH voltage
constexpr uint8_t OFF = LOW;   // Set "OFF" to be a LOW voltage

// the setup function runs once when you press reset or power the board
void setup() {
  // LED_BUILTIN is defined by the IDE when you select your Arduino type
  // This LED is considered an OUTPUT device, so let's configure that during setup()
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);
  delay(2000);
  Serial.print("Blink built in LED, located on pin ");
  Serial.print(LED_BUILTIN);
  Serial.println(".");
}

// the loop function runs over and over again forever

// Now that setup() has completed, let's make the built in LED blink repeatedly by turning it on
// for one second and then off for one second in our program loop
void loop() {
   digitalWrite(LED_BUILTIN, ON); // turn the LED on (HIGH is the voltage level)
   delay(1000); // delay() takes a value in milliseconds (thousandths of a second).  1000 milliseconds is 1 second.
   digitalWrite(LED_BUILTIN, OFF); // turn the LED off by making the voltage LOW
   delay(1000); // wait for a second
}
