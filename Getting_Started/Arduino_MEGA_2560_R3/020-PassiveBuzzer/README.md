# Passive Buzzers

## Two Pin Passive Buzzer
Fixed pitch buzzer that buzzes when ever + PIN is held HIGH.  Can be found in misc small parts box.  There
are TWO small buzzers in the kit, one active and one passive.  The active has a seal around the pins while
the passive has metal showing around the pins.  This is what my passive buzzer's back looks like:

 There are TWO small buzzers in the kit, one active and one passive.  The active buzzer that I have has a 'sealed' back:

<img src="https://user-images.githubusercontent.com/15940/207705848-e44a0dec-28ed-4292-8348-0756403816c2.jpeg" width="200">

2-pin and 3-pin are coded the same.  There are two ways of coding the passive buzzers.  Both use the tone() function.

The first way simply turns on the tone at a set frequence (in Hz).
```
  constexpr long int ON_LENGTH = 1000;
  constexpr long int OFF_LENGTH = 1000;
  tone(BUZZER_PIN, 440);  // Turn on buzzer (440 Hz).  Returns immediately!
  delay(ON_LENGTH);       // let it run one second
  noTone();               // Turn off buzzer
  delay(OFF_LENGTH);      // Leave off for one second
```

The other way sets the tone duration in the call to tone() but still returns immediately.  Buzzer will turn off after ON_TIME, but if you wish a delay
before the next tone then the delay needs to be longer than the ON_TIME.
```
  constexpr long int ON_LENGTH = 1000;
  constexpr long int OFF_LENGTH = 1000;
  tone(BUZZER_PIN, 440, ON_LENGTH);  // Turn on buzzer (440 Hz).  Returns immediately!
  delay(ON_LENGTH + OFF_LENGTH);     // *total* time in loop is ON_TIME + OFF_TIME
```

### Wiring
| Arduino | Buzzer |
| --- | --- |
| 2 | + |
| GND | other |

<img src="2PinPassiveBuzzer.png" width="350">

### Installation
No libraries or includes required.

## Three Pin Passive Buzzer (KY-006 / HW-508)
Same code as for 2-pin buzzer

## Wiring
| Arduino | Buzzer |
| --- | --- |
| 2 | S |
| GND | - |

<img src="3PinPassiveBuzzer.png" width="350">

## Installation
No libraries or includes required.
