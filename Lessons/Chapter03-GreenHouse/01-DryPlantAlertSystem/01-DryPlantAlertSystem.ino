//Arduino water level sensor code
// CODE FROM: https://circuitdigest.com/microcontroller-projects/interfacing-water-level-sensor-with-arduino
// Sensor pins pin D22 LED output, pin A8 analog Input

#define ledPin 22
#define sensorPin A8

void setup() {

  Serial.begin(9600);

  pinMode(ledPin, OUTPUT);

  digitalWrite(ledPin, LOW);

}

void loop()

{

  unsigned int sensorValue = analogRead(sensorPin);

  if (sensorValue < 540)

    return;

  uint8_t outputValue = map(sensorValue, 540, 800, 0, 255);

  Serial.print(sensorValue);

  Serial.print(" ");

  Serial.println(outputValue);

  analogWrite(ledPin, outputValue); // generate PWM signal

}

