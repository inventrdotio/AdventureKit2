/*
 * Day 0 - AI Apocalypse by inventr.io
 * Learn more at https://inventr.io/product/adventure-kit-2/
 *
 * Low power alerts.
 *
 * Whoa! Why'd the lights just go out?
 *
 * First version
 * =============
 * OK, I understand we wrote the code so that power is cut off when the charge level
 * approaches empty, but bad things can happen if we just suddenly cut the lights off
 * with no warning.
 *
 * So, our goal today is to add some code to give us some WARNING before the lights get
 * turned off. Let's try giving a warning when the battery charge level drops within 5%
 * of our low battery limit.
 *
 * Now, we could flash the lights as a warning, but that sudden, unexpected darkness
 * is kind of what we're trying to avoid. Let's use those speakers found in every room
 * to give an audible warning instead.
 *
 * Each speaker has a couple connections. One is an "active buzzer" and that's the
 * simplest way to get a sound since it will emit sound whenever 5 volts is supplied.
 * Our parts box even has a small active buzzer we can add to our simulation. Let's
 * start with our last sketch and add a warning before we cut the lights.
 *
 * Define a constant for our buzzer pin and then add another new constant for our new
 * LOW_BATTERY_WARNING and make it 5% higher than our cutoff limit.
 *
 * Now, in our loop() we simply turn the buzzer on when the battery charge is at our
 * warning limit. Let's test that out and see how it works.
 *
 * With the SKETCH_VERSION to 1, build and upload so we can try out our new code. Turn on
 * the light, cover the photoresistor (to simulate night) and let's see if we get a
 * warning *before* the light goes out.
 *
 * Second version
 * ==============
 * Oh, dear. That was NOT better. I'd almost rather be suddenly plunged into darkness
 * than have that tone blasting in my ears whenever power gets low. It would keep up
 * that racket until the battery started charging again the next day!
 *
 * I guess this can be a good learning experience. Code evolves and our early ideas
 * may not always work out the way we like. In fact, to demonstrate this let's KEEP
 * our first version around to remind us and use more conditional compilation to create
 * version 2 of our low battery warning. You'll see a define for SKETCH_VERSION below.
 * If it's set to 1 you'll get the first version of our warning.
 *
 * For version 2, let's just beep a few times to let us know we should finish what
 * we're doing and turn out the lights before they suddenly go out.
 *
 * We only want to beep when we first drop below the limit so let's add a variable to
 * track the charge level the *previous* time through the loop. We can set it equal to
 * the starting charge level so we don't get any bad alerts. We'll only beep when the
 * previous level was above the limit and the current value is below the limit. That is,
 * we'll have it beep when it first crosses that level.
 *
 * At the bottom of the loop, we'll copy the current charge level into the variable for
 * the previous charge level for the next time through our loop.
 *
 * Set the SKETCH_VERSION to 2, build and upload so we can try out our new code. Turn on
 * the light, cover the photoresistor (to simulate night) and let's see if we get a
 * warning *before* the light goes out.
 *
 * Third Version
 * =============
 * Excellent! That's much less annoying and now we have some warning as our
 * batteries get low so that we can carefully stop what we're doing and get
 * ready for the lights to go out.
 *
 * However, we still have a small issue. Were you watching the Serial Plotter
 * when it started beeping? Instead of showing lots of values every second, the
 * display froze for the entire time we were beeping. What's up with that?
 *
 * Oh, of course! We did our beeping by doing a digitalWrite() followed by a
 * delay(). Those delays are all added to the amount of time used during the
 * loop() execution when we cross below the warning limit. That's not good.
 * Let's see if we can get the same beeping *without* using the delay()
 * function since delay pauses the entire program when it is called.
 *
 * What we really want to do is to turn on the buzzer and then, at some future
 * time, turn it back off again. The pin will remain at whatever state we set,
 * so all we have to do is to *toggle* the pin state after some time has passed
 * until we have toggled it on/off the number of times we wish to beep.
 *
 * The Arduino IDE has a way to track how much time your sketch has been
 * running, so if we save the time when we START the beep we can then check
 * each time through the loop until enough time has passed. The millis()
 * function will return how long the sketch has been executing, in milliseconds
 * (thousandths of a second) just like delay().
 *
 * Once enough time has passed we then toggle the state of the buzzer pin, and
 * each time we turn the buzzer off we'll subtract one from the number of beeps
 * left and save the current millis() value.
 *
 * Set SKETCH_VERSION to 3, upload it to our HERO XL and watch the Serial
 * Plotter when our charge level drops below our warning limit.
 *
 * Version Four
 * ============
 * Things are really coming together now, aren't they? I think we could stop here,
 * but I have one more idea we can try to put even more polish on our solution.
 *
 * The speakers in our new home can do more than just emit a constant tone. Instead
 * of just beeping, we could use our speakers to play some tones. In the future, we
 * could use different tones to indicate different events, but for now, let's modify
 * our sketch to play three tones with descending pitch to indicate our battery level
 * is low.
 *
 * In addition to the active buzzer, our parts cache contains a *passive* buzzer. How
 * is that different from our active buzzer, you ask? Well, the active buzzer generates
 * a fixed tone whenever it's connected to 5V. A passive buzzer, on the other hand,
 * just emits a short "tic" sound when voltage is supplied. How does that help us?
 * Well, if we turn the voltage on and off very fast those "tic" sounds run together
 * and can sound like a musical note.
 *
 * We can change how quickly we toggle the voltage to generate different notes. Lucky
 * for us, the Arduino Language has provided the tone() function that will do that for
 * us, AND it will do this without causing a delay in our loop(). In order to make it
 * easy to make musical notes, you just provide the frequency (in cycles per second,
 * or "Hertz") for the note you desire. The note will change if you call the tone()
 * function with a new frequency or stop playing if you call noTone().
 *
 * We can save our "tune" in an "array" of variables. Computer arrays allow us to store
 * multiple values attached to a variable name and use an "index" to indicate which
 * value to use. The index is indicated by adding square brackets ("[]") to the end of
 * the variable name, with the desired index inside the brackets. You can also use a
 * variable name for the index which allows us to quickly point to any value in an array.
 *
 * The variable name points to the FIRST object in the array, and the index is then
 * added to that address to find additional values. Because of that, we use an index
 * of zero to point to the first value in an array, an index of one to point to the
 * second value, etc.
 *
 * We can set up a constant array called TONES and initialize it with the frequencies
 * to play in turn to produce a tune. We'll use the same timing code using millis()
 * to determine when to switch tones or for when it's time to turn off our tune.
 *
 * So, swap out the active buzzer and replace it with the passive buzzer, set
 * SKETCH_VERSION to 4, upload and give that a try. When the charge level hits our
 * warning level you should now hear a short tune when the charge level reaches our
 * warning level.
 *
 * Next Steps
 * ==========
 * That's enough for now, but here's an idea to try if you have some extra time.
 *
 * We now know when we're about to exhaust our batteries and need to turn off the
 * lights (or have them turned off by our HERO XL!). But what about in the morning?
 * Once the sun hits our solar panels the batteries will start to charge again, and
 * we can turn on the lights once we get a bit of charge.
 *
 * Perhaps you could evolve the sketch one more time to play a DIFFERENT tune when
 * the charge level first goes back *above* our warning level? That will let us know
 * that we can turn the lights back on.
 *
 * Alex Eschenauer
 * David Schmidt
 */

/*
 * Arduino language concepts introduced in this lesson.
 * - millis() - get current execution time, in milliseconds
 * - arrays - storing multiple values together, addressed using an index
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

/*
 * As this sketch evolves we'll make changes to improve the way it works.  Rather
 * than having multiple sketches, we use conditional compilation to only include
 * the code for the current version.  We begin with version 1.  As the lesson
 * progresses simply increment this number, rebuild and upload to see the next
 * evolution in our code.
 */
#define SKETCH_VERSION 4  // Current version of code to build

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

#if SKETCH_VERSION > 1
// Keep track of previous charge level so we can detect when we first drop below
// our warning level.  Start with our beginning level.
float previous_charge_percentage = battery_charge_percentage;

// How long to delay while beeping the buzzer (in milliseconds).
const int16_t BUZZER_DELAY = 300;  // Delay this much while beeping the buzzer

uint8_t beep_count = 0;  // store number of beeps left to sound.
#endif

// NOTE that #if blocks can be nested, one inside another.
#if SKETCH_VERSION > 2
uint32_t buzzer_delay_start = 0;  // when did our last buzzer state change

#if SKETCH_VERSION > 3
// For our tune we'll use an array of integer values.  For more information about
// arrays refer to https://www.arduino.cc/reference/en/language/variables/data-types/array/
const int16_t TONES[] = { 880, 698, 587 };
bool playing_tones = false;
int16_t current_tone;
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
  if (battery_charge_percentage < LOW_BATTERY_WARNING) {
    digitalWrite(ALARM_PIN, HIGH);
  }

  // turn alarm off once we pass above warning level
  if (battery_charge_percentage >= LOW_BATTERY_WARNING) {
    digitalWrite(ALARM_PIN, LOW);
  }
#elif SKETCH_VERSION == 2
  // Rather than continuous tone, just beep three times when charge nears empty
  if (previous_charge_percentage >= LOW_BATTERY_WARNING && battery_charge_percentage < LOW_BATTERY_WARNING) {
    beep_count = 3;
    while (beep_count-- > 0) {
      digitalWrite(ALARM_PIN, HIGH);
      delay(BUZZER_DELAY);
      digitalWrite(ALARM_PIN, LOW);
      delay(BUZZER_DELAY);
    }
  }
#elif SKETCH_VERSION == 3
  // When charge drops below warning level tell loop to beep 3 times
  if (previous_charge_percentage >= LOW_BATTERY_WARNING && battery_charge_percentage < LOW_BATTERY_WARNING) {
    beep_count = 3;
  }

  // The millis() function will return the amount of time that the current sketch
  // has executed, in milliseconds.
  if (beep_count) {
    uint32_t current_millis = millis();  // Get current millis() count
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
#elif SKETCH_VERSION >= 4
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

#if SKETCH_VERSION > 1
  // Save current charge level for next tinme through loop()
  previous_charge_percentage = battery_charge_percentage;
#endif

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
