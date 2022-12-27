# Active Buzzers

## Two Pin Active Buzzer

Fixed pitch buzzer that buzzes when ever + PIN is held HIGH.  Can be found in misc small parts box.  There are TWO small buzzers in the kit, one active and one passive.  The active buzzer that I have has a 'sealed' back:

<img src="https://user-images.githubusercontent.com/15940/207704594-68e639e8-d183-408e-a649-8fd3ede81f99.jpeg" width="200">

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

<img src="2PinActiveBuzzer.png" width="350">

### Installation
No libraries or includes required.

## Three Pin Active Buzzer (KY-012, none found in kit)

Fixed pitch buzzer that buzzes when ever + PIN is held HIGH.
```
  digitalWrite(BUZZER_PIN, HIGH); // Turn on buzzer
  delay(1000);                    // let it run one second
  digitalWrite(BUZZER_PIN, LOW);  // Turn off buzzer
```
## Wiring
| Arduino | Buzzer |
| --- | --- |
| 2 | S |
| GND | - |

<img src="3PinActiveBuzzer.png" width="350">

## Installation
No libraries or includes required.
