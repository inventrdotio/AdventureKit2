// Potentiometer 0 - Serial Plotter: sample code for Arduino Uno & Arduino Mega
//
// Use Serial Plotter in Arduino IDE to inspect potentiometer state in real time!

const byte          ANALOG_PIN =   A0;
const unsigned long BAUD_RATE  = 9600;  // serial-port speed in bits per second

// These two constants prevent the Serial Plotter from autoscaling the y-axis:

const int           PLOT_MIN   =    0;  // lowest value to plot
const int           PLOT_MAX   = 1023;  // highest value to plot

void setup() {
  Serial.begin(BAUD_RATE);  // set speed of serial port
}

void loop() {
  // Send three values per line (pot, min, max) to serial port for plotting:
  Serial.print("potentiometer:");        // text label (description + colon)
  Serial.print(analogRead(ANALOG_PIN));  // potentiometer state (0 to 1023)
  Serial.print(" minimum:");             // separator (space) + text label
  Serial.print(PLOT_MIN);                // anchor bottom of plot window
  Serial.print(" maximum:");             // separator + text label
  Serial.println(PLOT_MAX);              // anchor top of plot window
  // Call to Serial.println() function above generates end-of-line character(s).
}