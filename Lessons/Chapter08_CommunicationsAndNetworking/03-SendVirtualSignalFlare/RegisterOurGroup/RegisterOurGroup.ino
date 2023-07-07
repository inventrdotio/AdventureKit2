/*
 * Day 0 - AI Apocalypse by inventr.io
 * Learn more at https://inventr.io/PLACEHOLDER
 *
 * Let's join the other resistance groups that are battling the Global Phantom
 * Technologies rogue AI agents!  The Day-0 group we have been communicating with
 * has provided us with an API (Application Programming Interface) key that when
 * combined with our email address will validate our identity.
 *
 * Alex Eschenauer
 * David Schmidt
 */

// The following two libraries are included with the ESP32 board definitions.
// If you get compile errors make sure you have the board set to "ESP32 Dev Module"
// in the Arduino IDE settings.
#include <WiFi.h>
#include <HTTPClient.h>

// This file contains secrets that shouldn't be shared with others.  We include
// a template version named "secrets-template.h" which you should see in the list
// of files above.  Open that file then immediately select File/Save and save it
// as "secrets.h" in the SAME folder as this RegisterOurGroup.ino sketch.  THEN
// open secrets.h and replace the placeholder values with your own (secret) values.
// Your secrets.h should never be shared with others.
#include "secrets.h"

void setup() {
  Serial.begin(115200);
  delay(500);

  // Check if the secrets have been set
  if (String(SSID) == "YOUR_SSID" || String(SSID_PASSWORD) == "YOUR_SSID_PASSWORD"
      || String(USER_EMAIL) == "YOUR_EMAIL_ADDRESS" || String(API_KEY) == "YOUR_API_KEY") {
    Serial.println("Please update the secrets.h file with your credentials before running the sketch.");
    Serial.println("You need to replace YOUR_SSID and YOUR_WIFI_PASSWORD with your WiFi credentials.");
    Serial.println("Also replace YOUR_EMAIL_ADDRESS and YOUR_API_KEY with your API credentials.");
    return;  // Stop further execution of the code
  }

  // Connect to Wi-Fi
  WiFi.begin(SSID, SSID_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Initialize the HTTPClient object
  HTTPClient http;

  // Construct the URL.  This will connect to the Day-0 survivor group we discovered
  // and register our rough location.
  String url = "http://day-0.adventurekit2.com/survivors/register?";
  url += "api_key=" + String(API_KEY);
  url += "&email=" + String(USER_EMAIL);

  // Make the HTTP GET request to register our group with the other survivors
  http.begin(url);
  int httpCode = http.GET();

  // Check the return code
  if (httpCode == HTTP_CODE_OK) {
    // If the server responds with 200, print the response
    String payload = http.getString();
    Serial.println("Response:");
    Serial.println(payload);
  } else if (httpCode == HTTP_CODE_UNAUTHORIZED) {
    // If the server responds with 401, print an error message
    Serial.println("Invalid email or API key.");
    Serial.println(String(http.getString()));
  } else {
    // For any other HTTP response code, print it
    Serial.println("Received unexpected HTTP response:");
    Serial.println(httpCode);
  }

  // End the HTTP connection
  http.end();
}

void loop() {
  // do nothing
}
