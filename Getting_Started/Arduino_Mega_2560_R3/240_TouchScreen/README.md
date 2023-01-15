# Arduino shield with TFT LCD display and touch panel (ILI9341)

<img src="TFT_LCD_240x320DisplayWithTouchShield.jpg" width="500">

This 2.4" 240x320 LCD display by HiLetgo has pins that allows it to be directly installed onto an Arduino Uno or Mege (a "shield").  Thus, there's no wiring diagram.  Simply fit the shield onto the Arduino so that the 3.3v and 5v pins match the same pins on the Arduino.

This shield almost operates like two distinct parts; an LCD display underneath a touch panel.  Different libraries are used to interface with each, and the LCD display is placed into a different rotation the LCD coordinates need to be handled separately.

## Getting Started

Since this is a complex device we have multiple Arduino programs to get you up and running with this shield.

### Step 1: Initial LCD test and orientation

The LCD display can be rotated so that any of it's four sides are designated as "top".  Rotations are numbered 0-4 with rotation 0 used when the display is oriented with the white reset button on top.  The remaining rotations proceed in a clockwise direction (as will be demonstrated with our first test program).

Rotations:

0. Portrait rotation (white button on top)
1. Landscape rotation (white button on left)
2. Portrait rotation (white button on bottom)
3. Landscape rotation (white button on right)

Test Program:

Load 1-ShowLCDRotations and upload.  You should see each text displayed in each rotation briefly.  For each, the origin (x=0, y=0) is displayed in the proper corner and the rotation number is displayed in the center of the display.

### Step 2: Touch Panel Calibration

Since the touch panel is an analog device it also needs to be calibrated so that touch panel coordinates can be accurately mapped to the LCD panel coordinates.



## Installation
