/*
 * Day 0 - AI Apocalypse by inventr.io
 * Learn more at https://inventr.io/PLACEHOLDER
 *
 * OK, that works, but it's a bit clumsy to add more controls or pages.  It's also difficult
 * to run other code in our loop.  I did some research and found a library that makes
 * responding to web requests much easier, allowing us to create more complex sketches that
 * have more complex web sites AND also allow us to run more complex code in our loop().
 *
 * The library is ESPAsyncWebServer and is installed as follows:
 * 1. Go to the GitHub repository for the ESPAsyncWebServer library: https://github.com/me-no-dev/ESPAsyncWebServer
 * 2. Click on the green “Code” button and select “Download ZIP” to download the library as a ZIP file.
 * 3. Open the Arduino IDE and go to Sketch > Include Library > Add .ZIP Library.
 * 4. Browse to the folder where you extracted the library and select the “ESPAsyncWebServer-master.zip” file.
 * 5. Click on the “Open” button to install the library.
 * 6. Wait for the installation process to finish.
 * 7. Once the installation is complete, you can use the library in your Arduino projects.
 *
 * We also need to load TFT_eSPI and Adafruit_GFX libraries, which are available from the Arduino
 * IDE Library Manager.
 *
 * Alex Eschenauer
 * David Schmidt
 */

/*
  This creates a WiFi access point and provides a web server on it.

  Steps:
  1. Connect to the access point defined as SSID below
  2. Point your web browser to http://192.168.4.1/ to visit the Lighting control page
*/

#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include "Adafruit_GFX.h"
#include "TFT_eSPI.h"
#if USER_SETUP_ID != 25
#error "This sketch is for TFT_eSPI config 25 (TTGO_T_Display)."
#error "Edit libraries/TFT_eSPI/User_Setup_Select.h file and uncomment #include for Setup25_TTGO_T_Display.h"
#endif

#define HOUSE_LIGHTS 2  // Change this according to your setup

// Replace with your network credentials
const char *ssid = "HomeLights";
const char *password = "";

TFT_eSPI tft = TFT_eSPI();  // Invoke custom library

AsyncWebServer server(80);

// Declare our Web page constant (defined at the bottom of the sketch)
extern const char HTML[];

bool light_status = false;  // Keep track of current status of our light

void setup() {
  pinMode(HOUSE_LIGHTS, OUTPUT);
  digitalWrite(HOUSE_LIGHTS, LOW);

  // TTGO T-Display setup
  tft.init();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(1);
  tft.setCursor(0, 0);
  tft.setTextDatum(MC_DATUM);

  // Connect to Wi-Fi
  if (!WiFi.softAP(ssid, password)) {
    Serial.println("Soft AP creation failed.");
    while (1)
      ;
  }

  tft.println("AP Started");
  tft.println(WiFi.softAPIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    String html = HTML;  // get temporary writable copy of HTML
    if (light_status) {
      html.replace("{state}", "ON");
      html.replace("{buttonOnClass}", "button led-on");
      html.replace("{buttonOffClass}", "button");
    } else {
      html.replace("{state}", "OFF");
      html.replace("{buttonOnClass}", "button");
      html.replace("{buttonOffClass}", "button led-off");
    }
    request->send_P(200, "text/html", html.c_str());
  });

  server.on("/led/on", HTTP_GET, [](AsyncWebServerRequest *request) {
    digitalWrite(HOUSE_LIGHTS, HIGH);
    light_status = true;
    String html = HTML;  // get temporary writable copy of HTML
    html.replace("{state}", light_status ? "ON" : "OFF");
    html.replace("{buttonOnClass}", "button led-on");
    html.replace("{buttonOffClass}", "button");
    request->send_P(200, "text/html", html.c_str());
  });

  server.on("/led/off", HTTP_GET, [](AsyncWebServerRequest *request) {
    digitalWrite(HOUSE_LIGHTS, LOW);
    light_status = false;
    String html = HTML;  // get temporary writable copy of HTML
    html.replace("{state}", light_status ? "ON" : "OFF");
    html.replace("{buttonOnClass}", "button");
    html.replace("{buttonOffClass}", "button led-off");
    request->send_P(200, "text/html", html.c_str());
  });

  // Start server
  server.begin();
}

void loop() {
}

// Here is the Light Control web page
const char HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html>
<head>
<style>
  .button {
    font-size: 40px;
    padding: 20px 48px;
  }
  .led-off {
    background-color: green;
  }
  .led-on {
    background-color: red;
  }
</style>
</head>
<body>
<h1>Light Control</h1>
<p>Current Light State: {state}</p>
<p><a href="/led/on"><button class="{buttonOnClass}">Turn On</button></a></p>
<p><a href="/led/off"><button class="{buttonOffClass}">Turn Off</button></a></p>
</body>
</html>
)rawliteral";
