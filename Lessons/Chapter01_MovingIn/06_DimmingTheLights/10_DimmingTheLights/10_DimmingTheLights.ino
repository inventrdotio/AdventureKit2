/*
 * Day 0 - AI Apocalypse by inventr.io
 * Learn more at https://inventr.io/product/adventure-kit-2/
 *
 * Dimming the lights
 *
 * It looks like our lights are using too much current and our battery charge level
 * is getting drained too quickly.  There are lot of things we plan that will need
 * power so we need to reduce how much our lights are using.
 *
 * The lights are brighter than we really need, and in fact could draw the attention
 * of the AI hunting us.  Let's modify our sketch so that we can dim the lights to
 * a lower level, which will draw less attention AND use less power.
 *
 * First version
 * =============
 * Our photoresistor shows how a variable resistance can be used to generate a number
 * from 0-1023 on one of our analog pins.  But of course, using a photoresistor to
 * dim our lights wouldn't work very well.
 *
 * It looks like our stash of parts contains just what we need.  A potentiometer is
 * resistor where the value can be set by turning a dial.
 *
 * Let's start by wiring in a potentiometer and seeing if we can read a value we can
 * use.  We'll convert the value to a percentage and print it to the Serial Console
 * and display it using the Serial Plotter.
 *
 * With the SKETCH_VERSION to 1, build and upload so we can try out our new code. Open
 * the Serial Console to see the dimmer percentage, and open the Serial Plotter as you
 * turn the dial to see our desired light setting.
 * 
 * Second version
 * ==============
 * That's odd.  When I turn our dimmer up (clockwise), the percentage goes down, and
 * vice-versa.
 *
 * I see the problem, the potentiometer we found has it's maximum resistance when turned
 * counter-clockwise, and least resistance when turned clockwise.
 *
 * I think there's an easy fix for this though.  Remember the map() function that we
 * use to convert the analog input (0-1023) to a different range (0-100)?  It turns
 * out that if we reverse the values for our target range, the map() function will
 * increase it's output as the input decreases, and vice-versa.  This gives us 100
 * when our input is 0, and 0 when the input is 1023.
 *
 * Change SKETCH_VERSION to 2, rebuild and upload. Now we see that our dimmer now
 * increases the light percentage as we rotate the dimmer clockwise.
 *
 * Third Version
 * =============
 * Now that we can read our dimmer setting, let's change the intensity of the lights
 * to match.
 *
 * While the HERO XL has analog input pins, it does not have analog *output* pins.  The
 * pins can only output 0V or 5V.  So, how can we dim our LED?  One way is to change
 * how much time we send the 5V.  If we turn the output pin on and off very quickly then
 * the LED will dim between pulses of 5V.  This technique is called Pulse Width Modulation
 * (PWM) and our HERO XL supports this on pins D2-D13 and D44-D46.
 *
 * So, start by moving the lead plugged into pin 22 to pin 44 so that we can use PWM
 * to let us dim our simulated office light (the LED).  Now we can set LIGHT_PIN to
 * 44 to match.
 *
 * Our last step will use the analogWrite() function.  Now, didn't I just tell you that
 * the HERO XL doesn't have analog output pins?  Yes, but since PWM *simulates* an
 * analog output that name was chosen.  The analogWrite() function takes a value from
 * 0 to 255.  We currently have the value we read from the dimmer (0-1023) and the
 * percentage we computed (0-100).  But we can use the map() function again to convert
 * the dimmer values to our desired range.  Again, we will reverse the range so that
 * our light will get brighter as we turn the dial clockwise.
 *
 * Change SKETCH_VERSION to 3, rebuild and upload.  Now when you turn on the LED
 * and turn the dimmer dial we see that the LED gets brighter or dimmer to match.
 *
 * Fourth Version
 * ==============
 * (change amount of charge that the light uses based on light percentage)
 * Our simulation is almost complete, but we have one more change to make.  Did you
 * notice that even if you dim the light, the battery is still getting discharged
 * at the same rate?
 *
 * In our simulation we need to adjust the amount of charge used by our LED based
 * on our dimmer setting so that the battery charge level goes down slower when
 * the LED is dimmed.
 *
 * We do this by simply taking the value we were subtracting from the battery and
 * multiplying it by the dimmer percentage (making sure to convert the percentage)
 * to a fractional value from 0 to 1.0 instead of 0 to 100.
 *
 * Now change SKETCH_VERSION to 4, rebuild and upload.  Now when the LED is on the
 * speed the battery is discharged is based on how bright we have our lights.  Just
 * what we need!
 *
 * Next Steps
 * ==========
 * Here's one other change we could make if you have extra time.  What is we
 * *automatically* dimmed our lights as we neared our battery low limit.  This
 * could be done by setting a maximum intensity that is 100% above our warning
 * level and then be reduced as we approach our low battery limit.
 *
 * Remember that if the user has the light dimmed LOWER than this max limit the
 * light should use the actual setting, but if the setting is brighter than the
 * lowered maximum then it should be set to the maximum.
 *
 * Alex Eschenauer
 * David Schmidt
 */

/*
 * Arduino language concepts introduced in this lesson.
 * - Reverse map() - Map can decrease output as input range increases.
 *
 * Hardware concepts introduced in this lesson:
 * - potentiometer - a variable resistor that changes value as a dial is turned
 * - Pulse Width Modulation (PWM) - Turns voltage on/off very quickly to lower
 *            amount of current 
 */
#include "Arduino.h"

/*
 * As this sketch evolves we'll make changes to improve the way it works.  Rather
 * than having multiple sketches, we use conditional compilation to only include
 * the code for the current version.  We begin with version 1.  As the lesson
 * progresses simply increment this number, rebuild and upload to see the next
 * evolution in our code.
 */
#define SKETCH_VERSION 4  // Current version of code to build

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

#if SKETCH_VERSION <= 2        // If version is 1 or 2
const uint8_t LIGHT_PIN = 22;  // LED on pin 22
#else
const uint8_t LIGHT_PIN = 44;  // LED now on pin 44 which supports PWM
#endif
const uint8_t LIGHT_BUTTON = 23;   // Button (light switch) on pin 23
const uint8_t ALARM_PIN = 24;      // Active buzzer simulating our alarm speakers
const uint8_t CHARGING_RATE = A8;  // Photoresistor input simulating battery charge rate
const uint8_t LIGHT_DIMMER = A9;   // Our dimmer used to dim our lights.

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

const uint8_t SECONDS_TO_FULL = 30;        // For our simulation, fully charge battery in this many seconds
const uint8_t LOOPS_PER_SECOND = 20;       // Run this many loops per second, quick enough for light switch
const int16_t AVERAGE_CHARGE_LEVEL = 420;  // Photoresistor reads approximately this value for room light.

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
  pinMode(LIGHT_DIMMER, INPUT);         // Set potentiometer pin as INPUT
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
const int16_t BUZZER_DELAY = 300;  // Delay this much while beeping the buzzer

uint8_t beep_count = 0;  // store number of beeps left to sound.

uint32_t buzzer_delay_start = 0;  // when did our last buzzer state change

// For our tune we'll use an array of integer values.  For more information about
// arrays refer to https://www.arduino.cc/reference/en/language/variables/data-types/array/
const int16_t TONES[] = { 880, 698, 587 };
bool playing_tones = false;
int16_t current_tone;

void loop() {
  /*
   * We can do more than one thing inside our loop() code.  Since the photoresistor is new
   * let's handle that first, but then we can still handle switching our light on/off.
   */
  uint16_t current_charging_rate = analogRead(CHARGING_RATE);  // Read "charging rate" from our photoresistor (0-1023)
  uint16_t dimmer_setting = analogRead(LIGHT_DIMMER);          // read analog dimmer setting (0-1023)
  // Read our dimmer potentiometer and map it to a percentage.
#if SKETCH_VERSION == 1
  uint8_t dimmer_percentage = map(dimmer_setting, 0, 1023, 0, 100);  // Map dimmer to 0-100
#else
  // NOTE: The map command can REVERSE the direction of the output.  In this case
  //       we will map 0 to 100, and 1023 to 0 so that turning the potentiometer
  //       clockwise will increase the percentage.
  uint8_t dimmer_percentage = map(dimmer_setting, 0, 1023, 100, 0);  // Map dimmer to 100-0
#endif

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
    float led_power_draw = CHARGE_PER_LIGHT_UNIT * AVERAGE_CHARGE_LEVEL;
#if SKETCH_VERSION == 4
    // reduce our power draw when our light is dimmed.
    // NOTE: Use 100.0 to force the result to be a floating point number.  Otherwise
    //       the calculation would be done as integers, and if percentage were less
    //       than 100% the result would always be 0.  (99 / 100 is 0 using integer math)
    led_power_draw *= dimmer_percentage / 100.0;
#endif
    battery_charge_percentage -= led_power_draw;
  }

  // Sound warning when battery level drops below warning
  if (previous_charge_percentage >= LOW_BATTERY_WARNING && battery_charge_percentage < LOW_BATTERY_WARNING) {
    playing_tones = true;
    current_tone = 0;
  }

  if (playing_tones) {
    uint32_t current_millis = millis();  // Get current millis() count
    if (current_millis - buzzer_delay_start > BUZZER_DELAY) {
      if (current_tone < sizeof(TONES) / sizeof(int)) {
        tone(ALARM_PIN, TONES[current_tone++]);
        buzzer_delay_start = current_millis;  // Save start time
      } else {
        noTone(ALARM_PIN);
        playing_tones = false;
      }
    }
  }

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
    charging = false;
  }

  // Output the numbers we wish to plot using the Serial Plotter.
  Serial.print("%_charged:");                                 // Label for battery_charge_percentage
  Serial.print(battery_charge_percentage);                    // value to plot
  Serial.print(", Charge_Rate:");                             // Label for battery_charge_percentage
  Serial.print(map(current_charging_rate, 0, 1023, 0, 100));  // value to plot
  Serial.print(", Dimmer_%:");                                // Label for dimmer %
  Serial.print(dimmer_percentage);                            // value to plot
  Serial.println(", 0%:0, 100%:100");                         // Label for 0% charge level

  // Save current charge level for next tinme through loop()
  previous_charge_percentage = battery_charge_percentage;

  // Since we only use the button state *inside* loop() we declare it here as a local variable.
  uint8_t button_state = digitalRead(LIGHT_BUTTON);  // read current button state and save it

  // first check to see if the button state has changed since last loop()
  if (button_state != previous_button_state) {
    if (button_state == PRESSED) {  // if our NEW state is PRESSED this is a new button press
#if SKETCH_VERSION <= 2
      // then toggle our light, turning it off if it's on, and on if it's off.
      if (light_on) {
        digitalWrite(LIGHT_PIN, OFF);  // Light is on, turn it off
        light_on = false;              // ... and save it's new state
      } else {                         // Light must be off
        digitalWrite(LIGHT_PIN, ON);   // turn on light
        light_on = true;               // ... and save it's new state
      }
#else
      // then toggle our light.  Turn it off if it's on.  Set dimmer value if it's on
      if (light_on) {
        analogWrite(LIGHT_PIN, 0);  // Light is on, turn it off
        light_on = false;   // ... and save it's new state
      } else {          // Light is off
        light_on = true;  // ... so set state for light.  Dimmer value is set below
      }
#endif
    }
    // Since button state changed, let's save its current state for next time through loop()
    previous_button_state = button_state;
  }

#if SKETCH_VERSION > 2
  // The dimmer value can change any time, so we need to set the light intensity
  // outside of the code that turns the light on/off, since that code is only
  // executed when the button state changes.
  if (light_on) {
    // Set light intensity based on current dimmer settting, mapping
    // 0-1023 to 255-0.
    analogWrite(LIGHT_PIN, map(dimmer_setting, 0, 1023, 255, 0));
  }
#endif

  // Set delay time to get our desired number of loop() runs per second.
  delay(1000 / LOOPS_PER_SECOND);
}
