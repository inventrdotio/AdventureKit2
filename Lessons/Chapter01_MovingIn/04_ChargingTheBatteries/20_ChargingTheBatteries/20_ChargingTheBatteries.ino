/*
 * Day 0 - AI Apocalypse by inventr.io
 * Learn more at https://inventr.io/product/adventure-kit-2/
 *
 * Charging the Batteries
 *
 * Now that we have the charging level simulated it's time to start modeling
 * how our batteries will charge. We can do that by adding a bit of charge to
 * our simulated battery every time through our loop based how the current
 * charge rate.
 *
 * Our first concern is that the real charging will take hours each day, but we
 * don't wish to wait THAT long for each test of our charging simulation. So,
 * how much charge do we add to our simulated battery each time through the
 * loop?
 *
 * The nice thing about computers is that this is the kind of problem they are
 * designed for. Let's start by identifying how long we'd like for simulated
 * charge cycle to take using a SECONDS_TO_FULL constant that will give us the
 * number of seconds (at *average* room light level).
 *
 * We can also set AVERAGE_CHARGE_LEVEL to our *observed* charge rate by looking
 * at the rate we read from our photoresistor when in our current room's
 * ambient light.
 *
 * Lastly, we can slow down our loop() with a delay() to keep the number of
 * times through the loop constant using LOOPS_PER_SECOND.
 *
 * Now we can use those constants to calculate how much to add to a discharged
 * battery each time through our loop to reach full charge in SECONDS_TO_FULL
 * seconds at our average room's light. Then we can test how long it takes go
 * from a discharged battery to full charge if we cover or shine a light on our
 * simulated solar panel.
 *
 * OK, let's see how all this is accomplished!
 *
 * Alex Eschenauer
 * David Schmidt
 */

/*
 * Arduino language concepts introduced in this lesson:
 * - float data type - Floating point numbers (numbers with decimal points)
 *
 * Hardware concepts introduced in this lesson:
 */
#include "Arduino.h"

/*
 * Choosing what pin to use.
 * This project uses two digital pins and one analog pin. On the Hero XL we
 * *could* use any digital or analog pin (D0-D53, A0-A15). However, some pins
 * support specialized functions and in later lessons we will be using multiple
 * parts, some of which will use some of those special functions. So, let's start
 * out on the right foot by trying to use the most basic pin we can for each of
 * our parts.
 *
 * Skip: A0-A15 (save for Analog),
 *       D0/D1 (used by USB and Serial)
 *       D14-D19 (used by Serial 1-3)
 *       D2/D3, D18-D21 (used for external interrupts)
 *       D13 (this pin controls the build in LED on the HERO XL board (LED_BUILTIN)),
 *       D2-D13, D44-D46 (used for Pulse Width Modulation (PWM))
 *       D50 (MISO), D51 (MOSI), D52 (SCK), D53 (SS).  (used for SPI communication)
 *       D20 (SDA), D21 (SCL).  (used for I2C communication using the Wire library)
 *
 * Recommended for fewest conflicts:
 *    D22-D43, D47-D49, A8-A15
 */
const uint8_t LIGHT_PIN = 22;      // LED on pin 22
const uint8_t LIGHT_BUTTON = 23;   // Button (light switch) on pin 23
const uint8_t CHARGING_RATE = A8;  // Photoresistor input simulating battery charge rate

// Set up two constants so that we can turn our light "on" or "off".
const uint8_t ON = HIGH;  // HIGH is defined in Arduino.h to output 5 volts to a pin
const uint8_t OFF = LOW;  // LOW is defined to turn a pin "off" (low voltage)

// Set constants to read better with our use of the internal pull-up resistor.
const uint8_t PRESSED = LOW;       // Button input pin reads LOW when pressed
const uint8_t NOT_PRESSED = HIGH;  // Button input pin reads HIGH when NOT pressed

// Here are some constants used to determine how much to add to our simulated battery every
// time through our loop().  Many are also defined as floats to force the entire espression
// to use floating point math.
const uint8_t SECONDS_TO_FULL = 30;    // For our simulation, fully charge battery in this many seconds
const uint8_t LOOPS_PER_SECOND = 20;   // Run this many loops per second, quick enough for light switch
const int AVERAGE_CHARGE_LEVEL = 420;  // Photoresistor reads approximately this value for room light.

// Now, using those constants we can calculate (at average room light) how much to charge our battery
// every time through our loop().  We could do this in one long calculation, but to show you how it was
// derived we'll show every incremental step.

// We want to simulate a full charge in SECONDS_TO_FULL, so we charge this much per second
// Note that in order to do the calculation in floating point arithmetic we need at least
// one of the numbers to be floating point, so we use 100.0 instead of 100.
const float PERCENTAGE_PER_SECOND = 100.0 / SECONDS_TO_FULL;

// To keep our light switch responsive, we run loop() many times per second (by adding a delay())
// so we should add this much charge per loop() execution.
const float PERCENTAGE_PER_LOOP = PERCENTAGE_PER_SECOND / LOOPS_PER_SECOND;

// This value is how much charge to add to our battery for every unit read from our
// photoresistor.  If our analog pin reads AVERAGE_CHARGE_LEVEL then we should reach
// full charge in SECONDS_TO_FULL seconds.
const float CHARGE_PER_LIGHT_UNIT = PERCENTAGE_PER_LOOP / AVERAGE_CHARGE_LEVEL;

void setup() {
  // Intialize Serial class, used to communicate with the Arduino IDE Serial Monitor
  Serial.begin(9600);  // Initialize Serial, set speed to 9600 bits/second (baud)
  while (!Serial) {
    ;  // wait for serial port to connect.
  }
  pinMode(LIGHT_PIN, OUTPUT);           // LED representing our light (output)
  pinMode(LIGHT_BUTTON, INPUT_PULLUP);  // Button controlling light (input with pull-up resistor)
  pinMode(CHARGING_RATE, INPUT);        // Photoresistor analog input
}

/* Global Variables
 *
 * These variables need to maintain their state between runs of the loop so they
 * need to be defined with global variable scope.  They're placed right above loop()
 * for easy reference.
 *
 * Since our battery will charge only a small amount every time through our loop
 * we need to track numbers smaller than 1.  Arduino language supports floating point
 * numbers (https://www.arduino.cc/reference/en/language/variables/data-types/float/)
 * and we'll use them in these sketches to track our battery charging.
 */
float battery_charge_percentage = 0;  // LOW_BATTERY_LIMIT;  // Battery level in percent.  Starts out discharged.

bool light_on = false;                     // we start with the light turned off
bool previous_button_state = NOT_PRESSED;  // start out with button NOT pressed

void loop() {
  int current_charging_rate = analogRead(CHARGING_RATE);  // Read "charging rate" from our photoresistor (0-1023)

  // Using our constant from above, multiply our reading from the photoresistor by
  // that constant to see how much to add this loop()
  float new_charge = current_charging_rate * CHARGE_PER_LIGHT_UNIT;

  // Now add that bit of charge to our battery level!
  battery_charge_percentage += new_charge;

  Serial.print("0%:");  // Label for  0% charge
  Serial.print(0);
  Serial.print(", 100%:");  // Label for  100% charge
  Serial.print(100);
  Serial.print(", Battery_%:");
  Serial.print(battery_charge_percentage);
  Serial.print(", Charge_Rate:");  // Label for battery_charge_percentage
  Serial.println(map(current_charging_rate, 0, 1023, 0, 100));

  uint8_t button_state = digitalRead(LIGHT_BUTTON);  // read current button state and save it

  // first check to see if the button state has changed since last loop()
  if (button_state != previous_button_state) {
    if (button_state == PRESSED) {  // if our NEW state is PRESSED this is a new button press
      // then toggle our light, turning it of if it's on, and on if it's off.
      if (light_on) {
        digitalWrite(LIGHT_PIN, OFF);  // Light is on, turn it off
        light_on = false;              // ... and save it's new state
      } else {                         // Light must be off
        digitalWrite(LIGHT_PIN, ON);   // turn on light
        light_on = true;               // ... and save it's new state
      }
    }
    // Since button state changed, let's save its current state for next time through loop()
    previous_button_state = button_state;
  }

  delay(50);
}
