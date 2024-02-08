/*
 * Day 0 - AI Apocalypse by inventr.io
 * Learn more at https://inventr.io/product/adventure-kit-2/
 *
 * Low power alerts.
 *
 * We have batteries to store the power generated by our solar panels, but the charging
 * was handled by the building AI, which has been disabled.
 *
 * We'll use a HERO XL to control the charging and use of our battery array, using a
 * photoresistor to simulate our solar panels and variables in the code to track our
 * battery level.
 *
 * A photoresistor is a light-sensitive component that changes resistance based on the
 * amount of light it receives.  When light increases, the resistance decreases.
 *
 * Since we'll be powering our lights from the batteries we'll be adding on to our
 * previous switched light circuit and code.
 *
 * Alex Eschenauer
 * David Schmidt
 */

/*
 * Arduino language concepts introduced in this lesson.
 *
 * Hardware concepts introduced in this lesson:
 * - Active Buzzer - plays a fixed pitch tone whenever power is provided.
 */
#include "Arduino.h"

/* Choosing what pin to use.
 * This project only needs digital pins.  So, on the Hero XL we *could* use any digital or analog pin
 * (D0-D53, A0-A15).  However, some pins support specialized functions and in later lessons we will be
 * using multiple parts, some of which will use some of those special functions.  So, let's start out
 * on the right foot by trying to use the most basic pin we can for each of our parts.
 *
 * Skip: A0-A15 (save for Analog),
 *       D0/D1 (used by USB and Serial)
 *       D14-D19 (used by Serial 1-3)
 *       D2/D3, D18-D21 (used for external interrupts)
 *       D13 (this pin controls the build in LED on the HERO XL board (LED_BUILTIN)),
 *       D2-D13, D44-D46 (used for Pulse Width Modulation (PWM))
 *       D50 (MISO), D51 (MOSI), D52 (SCK), D53 (SS).  (used for SPI communication)
 *       D20 (SDA), D21 (SCL).  (used for I2C communication using the Wire library)
 * Recommended for fewest conflicts:
 *    D22-D43, D47-D49, A8-A15
 */
const uint8_t LIGHT_PIN = 22;      // LED on pin 22
const uint8_t LIGHT_BUTTON = 23;   // Button (light switch) on pin 23
const uint8_t ALARM_PIN = 24;      // Active buzzer simulating our alarm speakers
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

// Many battery types can be damaged over time if always charged to 100% or fully discharged.  Thus,
// in normal use we'll only charge up to the HIGH_BATTERY_LIMIT and turn off our batteries when
// LOW_BATTERY_LIMIT is reached.
const float LOW_BATTERY_LIMIT = 10;   // Turn off power use when battery charge drops below this value
const float HIGH_BATTERY_LIMIT = 90;  // Stop charging battery here to minimize battery degredation

// It is hard on a battery when charging is started and stopped often.  Because of this, when we
// start drawing power from our HIGH_BATTERY_LIMIT we won't begin to charge until battery level drops
// below this level.
const float RESUME_CHARGING_AT = HIGH_BATTERY_LIMIT - 5.0;

const uint8_t SECONDS_TO_FULL = 30;    // For our simulation, fully charge battery in this many seconds
const uint8_t LOOPS_PER_SECOND = 20;   // Run this many loops per second, quick enough for light switch
const int AVERAGE_CHARGE_LEVEL = 420;  // Photoresistor reads approximately this value for room light.

// Warn users when current charge level approaches lower limit
const float LOW_BATTERY_WARNING = LOW_BATTERY_LIMIT + 5.0;

// Now, using those constants we can calculate (at average room light) how much to charge our battery
// every time through our loop().  We could do this in one long calculation, but to show you how it was
// derived we'll show every incremental step.

// How many percentage points from our lowest charge to our highest charge?
const float PERCENTAGE_FROM_EMPTY_TO_FULL = HIGH_BATTERY_LIMIT - LOW_BATTERY_LIMIT;

// We want to simulate a full charge in SECONDS_TO_FULL, so we charge this much per second
const float PERCENTAGE_PER_SECOND = PERCENTAGE_FROM_EMPTY_TO_FULL / SECONDS_TO_FULL;

// To keep our light switch responsive, we run loop() many times per second using delay()
// so we should add this much charge per loop() execution.
const float PERCENTAGE_PER_LOOP = PERCENTAGE_PER_SECOND / LOOPS_PER_SECOND;

// This value is how much charge to add to our battery for every unit read from our
// photoresistor.  If our analog pin reads AVERAGE_CHARGE_LEVEL then we should reach
// full charge in SECONDS_TO_FULL seconds.
const float CHARGE_PER_LIGHT_UNIT = PERCENTAGE_PER_LOOP / AVERAGE_CHARGE_LEVEL;

/*
 * As this sketch evolves we'll make changes to improve the way it works.  Rather
 * than having multiple sketches, we use conditional compilation to only include
 * the code for the current version.  We begin with version 1.  As the lesson
 * progresses simply increment this number, rebuild and upload to see the next
 * evolution in our code.
 */
#define SKETCH_VERSION 3  // Current version of code to build

void setup() {
  // Intialize Serial class, used to communicate with the Arduino IDE Serial Monitor
  Serial.begin(9600);  // Initialize Serial, set speed to 9600 bits/second (baud)
  while (!Serial) {
    ;  // wait for serial port to connect.
  }
  pinMode(LIGHT_PIN, OUTPUT);           // LED representing our light (output)
  pinMode(LIGHT_BUTTON, INPUT_PULLUP);  // Button controlling light (input with pull-up resistor)
  pinMode(CHARGING_RATE, INPUT);        // Photoresistor analog input
  pinMode(ALARM_PIN, OUTPUT);           // Set Alarm pin to OUTPUT
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
float battery_charge_percentage = LOW_BATTERY_LIMIT;  // Battery level in percent.  Starts out discharged.

bool light_on = false;                     // we start with the light turned off
bool previous_button_state = NOT_PRESSED;  // start out with button NOT pressed

// Since we now cannot determine whether to charge by simply tracking the current battery level
// we need to track whether our battery is currently charging or not.
bool charging = true;

// Keep track of previous charge level so we can detect when we first drop below
// our warning level.  Start with our beginning level.
float previous_charge_percentage = battery_charge_percentage;

// If version is greater than 1, include a global beep count.
#if SKETCH_VERSION > 1
int beep_count = 0;  // store number of beeps left to sound.
#endif

// NOTE that #if blocks can be nested, one inside another.
#if SKETCH_VERSION > 2
// How long to delay while beeping the buzzer (in milliseconds).
const int BUZZER_DELAY = 300;  // Delay this much while beeping the buzzer

unsigned long buzzer_delay_start = 0;  // when did our last buzzer state change

#if SKETCH_VERSION > 3
const int TONES[] = { 880, 698, 587 };
bool playing_tones = false;
int current_tone;

#if SKETCH_VERSION > 4
const int RISING_TONES[] = { 587, 698, 880 }
#endif
#endif
#endif

void
loop() {
  /*
   * We can do more than one thing inside our loop() code.  Since the photoresistor is new
   * let's handle that first, but then we can still handle switching our light on/off.
   */
  int current_charging_rate = analogRead(CHARGING_RATE);  // Read "charging rate" from our photoresistor (0-1023)

  // Using our constant from above, multiply our reading from the photoresistor by
  // that constant to see how much to add this loop()
  float new_charge = current_charging_rate * CHARGE_PER_LIGHT_UNIT;

  // If we're currently charging add any new charge to our battery.
  if (charging) {
    battery_charge_percentage += new_charge;
  }

  // If our light is on, we subtract charge from the battery.  For our simulation, that
  // amount is below our average charge reading so that the battery charge will increase
  // during the "day" (though slower) and decrease when the charge rate drops (like at
  // night.)
  if (light_on) {
    battery_charge_percentage -= CHARGE_PER_LIGHT_UNIT * AVERAGE_CHARGE_LEVEL;
  }

#if SKETCH_VERSION == 1
  // Sound warning when battery level drops below warning
  if (previous_charge_percentage >= LOW_BATTERY_WARNING && battery_charge_percentage < LOW_BATTERY_WARNING) {
    digitalWrite(ALARM_PIN, HIGH);
  }

  // turn alarm off once we pass above warning level
  if (previous_charge_percentage < LOW_BATTERY_WARNING && battery_charge_percentage >= LOW_BATTERY_WARNING) {
    digitalWrite(ALARM_PIN, LOW);
  }
#elif SKETCH_VERSION == 2
  // Rather than continuous tone, just beep three times when charge nears empty
  if (previous_charge_percentage >= LOW_BATTERY_WARNING && battery_charge_percentage < LOW_BATTERY_WARNING) {
    beep_count = 3;
    while (beep_count-- > 0) {
      digitalWrite(ALARM_PIN, HIGH);
      delay(500);
      digitalWrite(ALARM_PIN, LOW);
      delay(500);
    }
  }
#elif SKETCH_VERSION == 3
  // When charge drops below warning level tell loop to beep 3 times
  if (previous_charge_percentage >= LOW_BATTERY_WARNING && battery_charge_percentage < LOW_BATTERY_WARNING) {
    beep_count = 3;
  }

  if (beep_count) {
    int current_millis = millis();  // Get current millis() count
    if (current_millis - buzzer_delay_start > BUZZER_DELAY) {
      if (digitalRead(ALARM_PIN)) {    // if buzzer is currently on
        digitalWrite(ALARM_PIN, OFF);  // Turn buzzer off
        beep_count--;                  // Beep completed, decrement count of remaining beeps
      } else {
        digitalWrite(ALARM_PIN, ON);  // Turn on buzzer
      }
      buzzer_delay_start = current_millis;  // Save start time
    }
  }
#elif SKETCH_VERSION > 4
  // Sound warning when battery level drops below warning
  if (previous_charge_percentage >= LOW_BATTERY_WARNING && battery_charge_percentage < LOW_BATTERY_WARNING) {
    playing_tones = true;
    current_tone = 0;
  }

  if (playing_tones) {
    int current_millis = millis();  // Get current millis() count
    if (current_millis - buzzer_delay_start > BUZZER_DELAY) {
      if (current_tone < sizeof(TONES) / sizeof(int)) {
        tone(ALARM_PIN, TONES[current_tone++]);
        // Serial.print("play tone ");
        // Serial.println(current_tone);
        buzzer_delay_start = current_millis;  // Save start time
      } else {
        // Serial.println("stop playing");
        noTone(ALARM_PIN);
        playing_tones = false;
      }
    }
  }
#endif

  // If our light is on and our charge reaches our low battery limit then
  // turn out the light.
  if (light_on && battery_charge_percentage < LOW_BATTERY_LIMIT) {
    digitalWrite(LIGHT_PIN, OFF);  // Light is on, turn it off
    light_on = false;              // ... and save it's new state
  }

  // When battery reaches the high battery limit we turn off charging.  We do not
  // turn it back on until we drop below the RESUME_CHARGING_AT level so that we
  // don't turn the charging on/off ever time through the loop (which would be
  // bad for our batteries).
  if (battery_charge_percentage < RESUME_CHARGING_AT) {
    charging = true;
  }

  // If we've reached our high battery limit then turn off charging.  It will
  // remain off until our battery charge drops below RESUME_CHARGING_AT.
  if (battery_charge_percentage > HIGH_BATTERY_LIMIT) {
    // battery_charge_percentage = HIGH_BATTERY_LIMIT;
    charging = false;
  }

  // Output the numbers we wish to plot using the Serial Plotter.
  Serial.print("0%:");                                          // Label for 0% charge level
  Serial.print(0);                                              // plotter value for 0% charge
  Serial.print(", 100%:");                                      // Label for 100% charge level
  Serial.print(100);                                            // plotter value for 100% charge
  Serial.print(", %_charged:");                                 // Label for battery_charge_percentage
  Serial.print(battery_charge_percentage);                      // plotter value
  Serial.print(", Charge_Rate:");                               // Label for battery_charge_percentage
  Serial.println(map(current_charging_rate, 0, 1023, 0, 100));  // plotter value

  // Save current charge level for next tinme through loop()
  previous_charge_percentage = battery_charge_percentage;

  // ============================================================================
  // The remainder of the sketch is the same as the last sketch from the previous lesson

  // Since we only use the button state *inside* loop() we declare it here as a local variable.
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

  // Set delay time to get our desired number of loop() runs per second.
  delay(1000 / LOOPS_PER_SECOND);
}
