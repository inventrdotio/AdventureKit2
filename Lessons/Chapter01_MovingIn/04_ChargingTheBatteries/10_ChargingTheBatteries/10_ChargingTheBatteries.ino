/*
 * Day 0 - AI Apocalypse by inventr.io
 * Learn more at https://inventr.io/product/adventure-kit-2/
 *
 * Charging the Batteries
 *
 * Having power for lights during the day is nice, but what about when the sun
 * goes down and our solar panels no longer generate power? That's when we need
 * light the most!
 *
 * Luckily, inventr.io considered this and installed a bank of batteries that can
 * be charged during the day and used after sunset. Of course, all of this was
 * controlled via AI, which is too dangerous to use now.
 *
 * We'll use our HERO XL to control our batteries and as we develop the sketch
 * we'll use a photoresistor to simulate our solar panels.
 *
 * Building a battery charging controller.
 *
 * We have batteries to store the power generated by our solar panels, but the
 * charging was handled by the building AI, which has been disabled.
 *
 * We'll use a HERO XL to control the charging and use of our battery array,
 * using a photoresistor to simulate our solar panels and variables in the code
 * to track our battery level.
 *
 * A photoresistor is a light-sensitive component that changes resistance based
 * on the amount of light it receives. When light increases, the resistance
 * decreases. When we pass current through that variable resistance the voltage
 * coming out of the photoresistor can be read on one of our input pins.
 *
 * If we use one of our digital pins we can only detect on/off levels (0 or 1).
 * But the HERO XL also provides "analog" pins. These pins can convert a 0-5V
 * input to a range (0 - 1023). This is perfect for giving us a relative
 * charging rate in our simulation.
 *
 * We'll start creating our code by displaying the current value being read from
 * our simulated solar panel (the photoresistor). But where can we display that
 * value? Our HERO XL doesn't have any display on it other than some simple LEDs,
 * but remember that we have it connected via USB to our computer running the
 * Arduino IDE.
 *
 * We're not restricted to only uploading our sketches to the HERO XL though.
 * The HERO XL can also *send* us messages, and the Arduino IDE provides a way
 * to display those messages using something called the Serial Monitor.
 *
 * For the HERO XL to send messages we need to initialize the Serial "class" in
 * our setup() function, letting it know how fast we'll be sending our data.
 * We then open the Serial Monitor in the Arduino IDE (Tools/Serial Monitor) and
 * make sure that the speed in Serial Monitor matches the speed we've configured
 * in setup().
 *
 * Once that's done we can have our HERO XL send us messages using various
 * Serial commands. In this first sketch, let's print our current "charge rate"
 * number coming from the photoresistor. We can view these messages by opening
 * up the Arduino IDE's Serial Monitor (Tools/Serial Monitor). Make sure the
 * speed in bits per second (known as "baud") matches the value in the
 * Serial.begin() call in the setup() function.
 *
 * You will see the current charge rate as a number from 0-1023 and you can make
 * that number change by covering or shining a light on the photoresistor.
 *
 * Those scrolling numbers can be a bit difficult to interpret, but the Arduino
 * IDE gives us another tool that allows us to plot data points on moving graph.
 * This tool is called the Serial Plotter. Select Tools/Serial Plotter and another
 * window will open, showing a moving graph of our simulated charge rate. The
 * graph will automatically scale the graph based on the lowest and highest
 * values being currently shown.
 *
 * Alex Eschenauer
 * David Schmidt
 */

/*
 * Arduino language concepts introduced in this lesson:
 * - Analog input pins - Reads values from 0 to 1023
 * - Serial Console - used to display messages from the HERO XL inside the Arduino IDE
 * - Serial Plotter - Can be used to plot values displayed on Serial Console
 *
 * Hardware concepts introduced in this lesson:
 * - photoresistor
 * - voltage divider using 10K resistor to get 0-5V from photoresistor
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

/*
 * NOTE: Using a pull-up resistor can cause some confusion because the input pin connected
 *       to our button will read HIGH when the button is NOT pressed, and LOW when the
 *       button IS pressed.  We can reduce this confusion a little by defining a
 *       new constant for the state of our button: "PRESSED"
 */
const uint8_t PRESSED = LOW;       // Button input pin reads LOW when pressed
const uint8_t NOT_PRESSED = HIGH;  // Button input pin reads HIGH when NOT pressed

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

bool light_on = false;                     // we start with the light turned off
bool previous_button_state = NOT_PRESSED;  // start out with button NOT pressed

void loop() {
  // Since analog pins can return values from 0-1023 an 8 bit integer isn't large
  // enough.  The uint16_t type holds a 16 bit, unsigned integer holding numbers
  // from 0-65535.
  uint16_t current_charging_rate = analogRead(CHARGING_RATE);  // Read "charging rate" from our photoresistor (0-1023)

  // Serial.println() displays text to the Serial Monitor and moves the cursor
  // to the start of the following line.
  Serial.println(current_charging_rate);

  // Read current button state and save in local variable
  uint8_t button_state = digitalRead(LIGHT_BUTTON);

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
