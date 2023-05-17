/*
 * Day 0 - AI Apocalypse by inventr.io
 * Learn more at https://inventr.io/PLACEHOLDER
 *
 * Intruders seem to be approaching our safe haven more and more lately.  While the
 * motion sensors seem to be working, we need something better to see exactly what's
 * approaching our building.
 *
 * We can use an ultrasonic distance sensor to determine distance to objects near us
 * and if we rotate the sensor around we can protect a wide area.
 *
 * Let's use the HC-SR04 Ultrasonic Ranging Module for distance to objects, and we can
 * use an SG90 Servo to rotate the sensor 180 degrees back and forth.  We can put one
 * on each side of our building to warn us of anything approaching.
 *
 * Let's use the Touch LCD 240x320 display shield to display our results.  We can display
 * the distance to objects as dots in a display similar to a 180 degree radar screen.
 *
 * Alex Eschenauer
 * David Schmidt
 */

#include <Servo.h>          // Servo library for controlling our SG90 servo
#include <MCUFRIEND_kbv.h>  // Graphics library used to draw our "radar" screen

MCUFRIEND_kbv tft;  // Instantiate the graphics object to be used for drawing.

const uint8_t TRIGGER_PIN = 22;  // attach pin D13 Arduino to pin Trig of HC-SR04
const uint8_t ECHO_PIN = 23;     // attach pin D12 Arduino to pin Echo of HC-SR04
const uint8_t SERVO_PIN = 24;

long raw_distance;  // variable for the raw_distance of sound wave travel
long max_distance = 0;
long display_max_distance = 10000;

Servo myservo;  // create servo object to control a servo

void setup() {
  Serial.begin(9600);

  // Set up pins to HC-SR04 Ultrasonic Ranging module.
  pinMode(TRIGGER_PIN, OUTPUT);  // Trigger pin used to trigger a ranging attempt
  pinMode(ECHO_PIN, INPUT);      // Echo pin reads amount of time for echo to return

  myservo.attach(SERVO_PIN);  // Servo control is on SERVO_PIN

  tft.begin(tft.readID());  // Initialize display screen
  tft.setRotation(0);       // Set rotation of display.  (0 places upper left above 9V plug)
  drawRanges();             // Show ranging lines on our display
}

int scan_count = 0;  // How many sweeps have we made.

void loop() {
  /*
   * We don't know how our servo is aligned when we first install it.  In order
   * to calibrate (or align) our servo uncomment the following two lines and run
   * the sketch.  This will set the servo so that it is halfway through it's sweep.
   * You can then attacht the ultrasonic ranging module so that it points away from
   * our building wall and will fully sweep the area.
   *
   * Once alligned, just comment out the following two lines to run the detector.
   */

  // myservo.write(90);
  // return;

  // First sweep from 0 degrees to 180 degrees
  for (int direction = 0; direction <= 180; direction += 2) {  // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(direction);  // tell servo to go to position in variable 'direction'
    delay(20);
    distanceCheck(direction);   // Check range to closest object and display
  }

  // Now do a sweep back in the opposite direction  
  for (int direction = 180; direction >= 0; direction -= 2) {  // goes from 180 degrees to 0 degrees
    myservo.write(direction);                                  // tell servo to go to position in variable 'direction'
    delay(20);
    distanceCheck(direction);
  }

  drawRanges();
  display_max_distance = max_distance;
}

void distanceCheck(int direction) {
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  long raw_distance = pulseIn(ECHO_PIN, HIGH);
  if (raw_distance > max_distance) {
    max_distance = raw_distance;
  }
  // Serial.print("Angle: " + String(direction) + ", distance: ");
  // Serial.println(raw_distance);
  distancePlot(0, 160, direction, map(raw_distance, 0, display_max_distance, 0, 160));
}

void distancePlot(int x, int y, float degrees, int length) {
  float angle_rad = (180 - degrees) * (PI / 180.0);

  int dx = length * cos(angle_rad);
  int dy = length * sin(angle_rad);

  // Rotate the (dx, dy) vector 90 degrees clockwise
  int dx_rotated = dy;
  int dy_rotated = -dx;

  int x2 = x + length * sin(angle_rad);
  int y2 = y - length * cos(angle_rad);
  // Serial.println("  Draw line from " + String(x) + ":" + String(y) + " to " + String(x2) + ":" + String(y2));
  tft.fillCircle(x2, y2, 1, TFT_CYAN);
}

void drawRanges() {
  if (scan_count++ % 10 == 0 || (display_max_distance - max_distance) > 100)
    tft.fillScreen(TFT_BLACK);
  tft.drawCircle(0, 160, 40, TFT_BLUE);
  tft.drawCircle(0, 160, 80, TFT_BLUE);
  tft.drawCircle(0, 160, 120, TFT_BLUE);
  tft.drawCircle(0, 160, 160, TFT_BLUE);
  tft.drawLine(0, 160, 160, 160, TFT_BLUE);
}