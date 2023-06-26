/*
 * Day 0 - AI Apocalypse by inventr.io
 * Learn more at https://inventr.io/PLACEHOLDER
 *
 * That sketch works, but it's still a bit inconvenient to connect to each T-Display's
 * AP in order to control the lights.  When I'm connected to the T-Display I'm unable
 * to do anything else, like browse our simulated Internet.
 *
 * I found some old (NO AI!) WiFi Access points in the museum so let's just set up our
 * own local WiFi network.  Then we can connect our Internet simulation AND our T-Display
 * servers along with our other device.  Then we can access the Internet simulation AND our
 * light controls at the same time.
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
#include <ESPmDNS.h>
#include "Adafruit_GFX.h"
#include "TFT_eSPI.h"
#if USER_SETUP_ID != 25
#error "This sketch is for TFT_eSPI config 25 (TTGO_T_Display)."
#error "Edit libraries/TFT_eSPI/User_Setup_Select.h file and uncomment #include for Setup25_TTGO_T_Display.h"
#endif

#define HOUSE_LIGHTS 2  // Change this according to your setup

// Create the file "secrets.h" that contains the following two lines.  Replace the placeholders with your
// local SSID and PASSWORD.  The secrets.h file will never be checked into a git repository (which would
// expose your private network credentials).
//
// const char *SECRET_SSID = "YOUR SSID";
// const char *SECRET_PASSWORD = "YOUR PASSWORD";
#include "secrets.h"
#define SSID SECRET_SSID
#define PASSWORD SECRET_PASSWORD
const char HOSTNAME[] = "Day0Survivors.io";

TFT_eSPI tft = TFT_eSPI();  // Invoke custom library

AsyncWebServer server(80);

// Declare our Web page constant (defined at the bottom of the sketch)
extern const char HTML[];

bool light_status = false;  // Keep track of current status of our light

void setup() {
  Serial.begin(115200);
  delay(500);
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
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASSWORD);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.printf("WiFi Failed!\n");
    return;
  }

  if (!MDNS.begin(HOSTNAME)) {  // Start mDNS service with hostname "myserver"
    Serial.println("Error setting up MDNS responder!");
  } else {
    Serial.println("mDNS responder started - hostname: " + String(HOSTNAME));
    MDNS.addService("http", "tcp", 80);  // Add mDNS service
  }

  tft.println("Connected to " + String(SSID));
  tft.print("IP Address: ");
  tft.println(WiFi.localIP());

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
    background-color: LightGreen;
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
