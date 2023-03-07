# 4 Digit 7 Segment LED (5161AS)

This part is a 4 digit, 7 segment LED Display.  Each segment on the device is lit when the corresponding pin
on the board is set to High, and digits can be formed by lighting the correct segments.

NOTE: The current part in the Beta kit is a bare display and required significant wiring.  It's likely that this part will be replaced with the same 4 digit 7 segment module from the 30-Day kit, which uses fewer pins/wires on the Arduino.

### Documentation
[Datasheet](http://www.xlitx.com/datasheet/5161AS.pdf)

```
```

### Wiring
| Arduino | resistor | 5161AS |
| -- | -- | -- |
| 2 | 220 ohm | D1 |
| 3 | 220 ohm | D2 |
| 4 | 220 ohm | D3 |
| 5 | 220 ohm | D4 |
| 6 | | A |
| 7 | | B |
| 8 | | C |
| 9 | | D |
| 10 | | E |
| 11 | | F |
| 12 | | G |
| 13 | | DP |

<img src="4Digit7Segment.png" width="500">

### Installation
Install "SevSeg" library by Dean Reading from Arduino IDE Library Manager
