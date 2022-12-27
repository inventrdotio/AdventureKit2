// Push Button 0 - Serial Plotter: sample code for Arduino Uno & Arduino Mega
//
// Use Serial Plotter in Arduino IDE to inspect push-button state in real time!

const byte          BUTTON_PIN =   12;  // Pin 13 has LED on Arduino Mega
const unsigned long BAUD_RATE  = 9600;  // serial-port speed in bits per second

// These two constants prevent the Serial Plotter from autoscaling the y-axis:

const int           PLOT_MIN   =   -1;  // lowest value to plot
const int           PLOT_MAX   =    2;  // highest value to plot

void setup() {
  // Pressing push button grounds BUTTON_PIN input so closed switch reads LOW.
  // Enable internal pullup resistor on BUTTON_PIN so open switch reads HIGH:
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  Serial.begin(BAUD_RATE);  // set speed of serial port
}

void loop() {
  // Send three values per line (button, min, max) to serial port for plotting:
  Serial.print("button:");                // text label (description + colon)
  Serial.print(digitalRead(BUTTON_PIN));  // button state (1 = open, 0 = closed)
  Serial.print(" minimum:");              // separator (space) + text label
  Serial.print(PLOT_MIN);                 // anchor bottom of plot window
  Serial.print(" maximum:");              // separator + text label
  Serial.println(PLOT_MAX);               // anchor top of plot window
  // Call to Serial.println() function above generates end-of-line character(s).
}
