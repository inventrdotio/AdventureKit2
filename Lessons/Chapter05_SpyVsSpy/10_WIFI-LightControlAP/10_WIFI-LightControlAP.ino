/*
 * Day 0 - AI Apocalypse by inventr.io
 * Learn more at https://inventr.io/PLACEHOLDER
 *
 * We now have our light switches set up to turn on our lights.  But it's not always
 * convenient to locate and go to a light switch.  But we always have our devices with
 * us.  These T-Display devices have built-in WiFi so why don't we use THOSE to control
 * our lights.  We can set them us as WiFi Access Points (APs), connect to them and
 * then turn our lights on/off without having to even stand up!
 *
 * This sketch creates a WiFi access point that we can connect to with our WiFi devices.
 * It also starts up a web server and once we're connected to the AP we can browse to
 * it.  On that server we simply set up a web page with buttons that will allow us to
 * turn our lights on and off.  (I wonder what else we can control this way?)
 *
 * Alex Eschenauer
 * David Schmidt
 */

/*
  WiFiAccessPoint.ino creates a WiFi access point and provides a web server on it.

  Steps:
  1. Connect to the access point defined as SSID below
  2. Point your web browser to http://192.168.4.1/H to turn the LED on or http://192.168.4.1/L to turn it off
*/

#include <WiFi.h>

#define HOUSE_LIGHTS 2  // Set the GPIO pin where you connected your test LED or comment this line out if your dev board has a built-in LED

// Set these to your desired credentials.
const char *ssid = "HomeLights";
const char *password = "";  // No password required right now

WiFiServer server(80);

const char HTML[] = R"rawliteral(
<!DOCTYPE HTML>
<html>
<head>
<style>
  .button {
    font-size: 40px;
    padding: 20px 48px;
  }
</style>
</head>
<body>
<h1>Light Control</h1>
<p><a href="/H"><button class="button">Turn On</button></a></p>
<p><a href="/L"><button class="button">Turn Off</button></a></p>
</body>
</html>
)rawliteral";

void setup() {
  pinMode(HOUSE_LIGHTS, OUTPUT);  // Pin controlling our lights (LED)

  Serial.begin(9600);
  Serial.println();
  Serial.println("Configuring access point...");

  // You can remove the password parameter if you want the AP to be open.
  // a valid password must have more than 7 characters
  if (!WiFi.softAP(ssid, password)) {
    Serial.println("Soft AP creation failed.");
    while (1)
      ;
  }
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();

  Serial.println("Server started");
}

void loop() {
  WiFiClient client = server.available();  // listen for incoming clients

  if (client) {                     // if you get a client,
    Serial.println("New Client.");  // print a message out the serial port
    String currentLine = "";        // make a String to hold incoming data from the client
    while (client.connected()) {    // loop while the client's connected
      if (client.available()) {     // if there's bytes to read from the client,
        char c = client.read();     // read a byte, then
        Serial.write(c);            // print it out the serial monitor
        if (c == '\n') {            // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.println(HTML);

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {  // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /H")) {
          digitalWrite(HOUSE_LIGHTS, HIGH);  // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(HOUSE_LIGHTS, LOW);  // GET /L turns the LED off
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
