# Lesson 1: Onboarding (blink onboard LED)

## Parts required
* Required
    * Student computer (MacOS, Windows, Linux, Chromebook)
    * USB Cable (USB Type A to USB Type B)
    * HERO XL board
* Optional
    * HERO XL mounting board

## Outline
* HERO XL
    * Compatible with Arduino Mega 2560
    * External Power
        * not needed when USB connected
    * USB Type B connector
        * provides power
        * Used to connect to computer for uploading and text communications
    * Reset button
        * restarts last program uploaded
    * Status LEDs
        * Power
        * TX / RX (serial transmit and receive)
        * Controllable built-in (LED_BUILTIN)
            * Pin 13 on HERO XL, but use LED_BUILTIN
    * Pin connections
        * 5 Volt levels for all but 3.3V pin
        * Power output pins for powering external devices
        * Power input pin can power HERO XL
        * Ground (GND) pins
        * 54 digital input/output pins
        * 16 analog inputs
        * 4 UARTS (hardware serial ports)
        * ICSP header (can leave out as I don't think we'll ever use this)
* Arduino IDE (Integrated Development Environment)
    * Installation
        * MacOS
        * Windows
        * Linux
        * Chromebook
    * HERO XL programs are called "sketches"
    * Built in editor for entering and modifying your sketches
    * Library manager to include code to help with your sketches
    * Links to load example sketches to get you started
        * More examples added each time you add a library
    * Build command to build the code for your sketches
    * Upload command to upload (and run) your sketches on devices
* Connect it all up and test
    * Launch Arduino IDE
    * Load example sketch
        * File / Examples / 01.Basics / Blink
            * Will blink the built-in LED on the HERO XL (LED_BUILTIN)
    * Arduino Configuration
        * board selection
        * port selection
        * USB Cable connection
    * Quick/simple code walkthrough
        * comments
        * setup()
            * pinMode
        * loop()
            * digitalWrite()
            * delay
    * Sketch / Verify/Compile
        * Converts sketch to computer code
    * Sketch / Upload
        * Builds sketch for configured board
        * Uploads code to device using configured port
    * Built-in LED should be blinking on for one second then off for one second.
* Further study
    * Change delay value in EACH delay() call
