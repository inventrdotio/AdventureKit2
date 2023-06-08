/*
 * Day 0 - AI Apocalypse by inventr.io
 * Learn more at https://inventr.io/PLACEHOLDER
 *
 * Building a battery charging controller.
 *
 * Batteries are getting charged and we get a warning when they're close to being
 * empty.  But that is happening faster than we prefer.  Perhaps we're using too much
 * power?  The lights are quite bright, probably brighter than they need to be.
 *
 * Let's dim those lights and see if we can reduce our power needs so that our batteries
 * don't run out of charge before we're ready to quit for the night.
 *
 * David Schmidt
 */

/*
 * Arduino language concepts introduced in this lesson.
 *
 * - Potentiometer
 * - Pulse Width Modulation (PWM)
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
const uint8_t LIGHT = 44;          // LED on PWM pin
const uint8_t LIGHT_BUTTON = 23;   // Button (light switch) on pin 23
const uint8_t ALARM_PIN = 24;      // Active buzzer simulating our alarm speakers
const uint8_t CHARGING_RATE = A8;  // Photoresistor input simulating battery charge rate
const uint8_t LIGHT_DIMMER = A9;   // Our dimmer used to dim our lights.

/*
 * NOTE: While HIGH/LOW now make more sense when using a pull-down resistor, it still
 *       makes even MORE clear using PRESSED / NOT_PRESSED.  However, now we set
 *       PRESSED equal to HIGH.  We can also use ON / OFF for our lights.
 */
const uint8_t PRESSED = LOW;       // Button input pin reads LOW when pressed
const uint8_t NOT_PRESSED = HIGH;  // Button input pin reads HIGH when NOT pressed
const uint8_t ON = HIGH;           // Lights are ON when pin is HIGH
const uint8_t OFF = LOW;           // Lights are OFF when pin is LOW

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

// Warn users when current charge level approaches lower limit
const float LOW_BATTERY_WARNING = LOW_BATTERY_LIMIT + 5.0;

const uint8_t SECONDS_TO_FULL = 15;    // For our simulation, fully charge battery in this many seconds
const uint8_t LOOPS_PER_SECOND = 20;   // Run this many loops per second, quick enough for light switch
const int AVERAGE_CHARGE_LEVEL = 530;  // Photoresistor reads approximately this value for room light.

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

void setup() {
  // Intialize Serial class, used to communicate with the Arduino IDE Serial Monitor
  Serial.begin(9600);  // Initialize Serial, set speed to 9600 bits/second (baud)
  while (!Serial) {
    ;  // wait for serial port to connect.
  }
  pinMode(LIGHT, OUTPUT);               // LED representing our light (output)
  pinMode(LIGHT_BUTTON, INPUT_PULLUP);  // Button controlling light (input with pull-up resistor)
  pinMode(CHARGING_RATE, INPUT);        // Photoresistor analog input
  pinMode(ALARM_PIN, OUTPUT);           // Set Alarm pin to OUTPUT
  pinMode(LIGHT_DIMMER, INPUT);
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

// How long to delay while beeping the buzzer (in milliseconds).
const int BUZZER_DELAY = 300;  // Delay this much while beeping the buzzer

unsigned long buzzer_delay_start = 0;  // when did our last buzzer state change

const int TONES[] = { 880, 698, 587 };
bool playing_tones = false;
int current_tone;

void loop() {
  /*
   * We can do more than one thing inside our loop() code.  Since the photoresistor is new
   * let's handle that first, but then we can still handle switching our light on/off.
   */
  int current_charging_rate = analogRead(CHARGING_RATE);  // Read "charging rate" from our photoresistor (0-1023)

  int dimmer_setting = analogRead(LIGHT_DIMMER);  // Read dimmer setting

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
    battery_charge_percentage = battery_charge_percentage - (CHARGE_PER_LIGHT_UNIT * AVERAGE_CHARGE_LEVEL * .8);
  }

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

  // If our light is on and our charge reaches our low battery limit then
  // turn out the light.
  if (light_on && battery_charge_percentage < LOW_BATTERY_LIMIT) {
    analogWrite(LIGHT, OFF);  // Light is on, turn it off
    light_on = false;         // ... and save it's new state
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

  // Save current charge level for next tinme through loop()
  previous_charge_percentage = battery_charge_percentage;

  // Output the numbers we wish to plot using the Serial Plotter.  The first two numbers
  // are just to show the 0% and 100% charged points so the plotter won't continuously
  // change the scale.
  Serial.print(0);  // show line in plotter for 0% charge
  Serial.print(", ");
  Serial.print(100);  // show line in plotter for 100% charge
  Serial.print(", ");
  Serial.print(battery_charge_percentage);  // show current battery charge in percent
  Serial.print(", ");
  Serial.print(map(current_charging_rate, 0, 1023, 0, 100));  // show charge rate, in percent
  Serial.print(", ");
  Serial.println(map(dimmer_setting, 0, 1023, 100, 0));

  // =========== Second part of loop is our prior button / LED control

  // Since we only use the button state *inside* loop() we declare it here as a local variable.
  uint8_t button_state = digitalRead(LIGHT_BUTTON);  // read current button state and save it

  // first check to see if the button state has changed since last loop()
  if (button_state != previous_button_state) {
    if (button_state == PRESSED) {  // if our NEW state is PRESSED this is a new button press
      // then toggle our light, turning it of if it's on, and on if it's off.
      if (light_on) {
        analogWrite(LIGHT, OFF);  // Light is on, turn it off
        light_on = false;         // ... and save it's new state
      } else {                    // Light must be off
        light_on = true;          // ... and save it's new state
      }
    }

    // Since button state changed, let's save its current state for next time through loop()
    previous_button_state = button_state;
  }

  if (light_on) {
    analogWrite(LIGHT, map(dimmer_setting, 0, 1023, 255, 0));  // turn on light based on dimmer
  }

  // Set delay time to get our desired number of loop() runs per second.
  delay(1000 / LOOPS_PER_SECOND);
}
