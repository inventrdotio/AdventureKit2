# Identifying the four different buzzers found in Adventure Kit 2

Adventure Kit 2 (AK2) contains four buzzers.  There are two [active buzzers](#active_buzzers) and two [passive buzzers](#passive_buzzers).  This document will help you identify the four buzzers included in AK2 and describe the similarities and differences.

* functions & requirements: active (fixed pitch, just needs power) vs. passive (variable pitch, needs external signal)
* form factors: 2-pin components (small, fragile) vs. 3-pin modules (correct pin spacing, strong/sturdy/durable)
* caveat for 3-pin buzzer modules: third pin is not connected to anything, so just ignore it
* identifying 2-pin buzzers: active buzzer (closed bottom) vs. passive buzzer (open bottom, exposed circuit board)
* identifying 3-pin buzzer modules by part number: active (KY-012, HW-512) vs. passive (KY-006, HW-508)
* identifying buzzers with 9 V battery test: active (makes continuous tone) vs. passive (makes clicking sound)

## Active Buzzers

Active buzzers emit a fixed pitch sound whenever the proper voltage is supplied to the device.
There are two active buzzers in AK2, a 2-pin (small) buzzer ([KY-012](/Devices/KY-012_2-PinActiveBuzzer.md)) and
a 3-pin buzzer mounted on a small PCB ([HW-512](/Devices/HW-512_3-PinActiveBuzzer.md)).

## Passive Buzzers


