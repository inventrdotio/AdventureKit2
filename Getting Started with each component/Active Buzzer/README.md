# Active Buzzers

## Two Pin Active Buzzer

Fixed pitch buzzer that buzzes when ever + PIN is held HIGH.

```
  digitalWrite(BUZZER_PIN, HIGH); // Turn on buzzer
  delay(1000);                    // let it run one second
  digitalWrite(BUZZER_PIN, LOW);  // Turn off buzzer
```

### Wiring
| Arduino | Buzzer |
| --- | --- |
| 2 | + |
| GND | other |

<img src="2-Pin Active Buzzer.png" width="350">

### Installation
No libraries or includes required.

## Three Pin Active Buzzer (KY-012)

Multi-tone buzzer.  Uses tone() function to set frequency and duration of tone.
```
  tone(BUZZER_PIN, 440, 1000);  // Sound 440hz pitch for one second
```

## Wiring
| Arduino | Buzzer |
| --- | --- |
| 2 | S |
| GND | - |

<img src="3-Pin Active Buzzer (KY-012).png" width="350">

## Installation
No libraries or includes required.
