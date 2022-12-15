Configuring the Raspberry Pi Pico W for the Arduino IDE

Followed instructions at https://dronebotworkshop.com/picow-arduino/#Testing_the_Installation_8211_Blink

Raspberry Pi Pico Arduino core
The Raspberry Pi Pico Arduino core is a boards manager maintained on GitHub by user Earle F Philhower.  This core covers not only the original Pico and the Pico W but also includes pretty well every RP2040-based board that you can find and is frequently updated.

In order to add this to your Arduino IDE, you will need to edit your Preferences to add a JSON string in the same fashion that we have done for other boards like the ESP32 and Seeeduino XIAO.

You can accomplish this as follows:

Open the Arduino IDE.
Click on the File menu item at the top and select Preferences. The Preferences dialog box will open.
Within the Preferences dialog box, look for a text box labeled âAdditional Boards Manager URLsâ.
This is where you will be inserting a JSON string. If the box is empty, you can paste it directly, otherwise, click on the icon on the right of the box to open a text window that allows you to add several JSON strings, one per line.
The string you want to add is as follows:

https://github.com/earlephilhower/arduino-pico/releases/download/global/package_rp2040_index.json

Once you have added the string to your Additional Boards Manager URLs, you can click OK to save it in your Preferences.

Arduino IDE Boards Manager
The JSON file entry doesnât actually install the new Pico RP2040 boards. Instead, it points to a location where your Boards Manager can get updates, mpw including one with the RP2040 board entries.  Youâll need to add the new boards using the Boards Manager utility in the Arduino IDE.

Open the Boards Manager utility by selecting the Tools menu. Scroll down until you see an entry for the type of board (i.e., Arduino Uno) you are currently set up for. Highlight that, and another menu will appear, allowing you to change your existing board or launch the Boards Manager. You will want to launch the Boards Manager so that you can install the new Pico W board.

When the Boards Manager window has launched, filter your search by typing in âPicoâ. Youâll get three results back, the second one, âRaspberry Pi Pico/RP2040â is the one you want.

Select it and click the Install button to install the new Boards Manager entry.

It will take a minute to copy all the files, once itâs done, you are ready to start using the Pico W on your Arduino IDE.

Once complete, you should be able to select "Raspbery Pi Pico W" as your board type.  Make SURE that you select the "W" version as some pins are different (notably the built in LED (LED_BUILTIN).
