# NodeMCU ESP8266

## Configuring Arduino IDE

To configure the Arduino IDE for the NodeMCU board, you will need to follow these steps:

1. Download and install the Arduino IDE from the official website (https://www.arduino.cc/en/main/software).
2. Open the Arduino IDE and go to "File" > "Preferences".
3. In the "Additional Boards Manager URLs" field, enter the following URL:
```
http://arduino.esp8266.com/stable/package_esp8266com_index.json
```

4. Click "OK" to save the changes and close the Preferences window.
5. Go to "Tools" > "Board" > "Boards Manager".
6. In the Boards Manager window, search for "esp8266" and install the "esp8266 by ESP8266 Community" package.
7. After the installation is complete, go to "Tools" > "Board" and select "NodeMCU 1.0 (ESP-12E Module)" from the list of available boards.
8. Connect your NodeMCU board to your computer using a micro USB cable.
9. In the Arduino IDE, go to "Tools" > "Port" and select the port that your NodeMCU is connected to.
10. You are now ready to upload code to your NodeMCU board using the Arduino IDE. Simply select the desired sketch in the Arduino IDE and click the "Upload" button to upload the code to the board.

I hope this helps! Let me know if you have any questions.
