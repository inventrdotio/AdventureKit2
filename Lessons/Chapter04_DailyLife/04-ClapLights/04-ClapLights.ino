// Arduino Clap lights

int soundA0 = A0;
int soundD0 = 2;

int led = 13;
bool ledState = false;

void setup() {
  Serial.begin(9600);

  pinMode(soundA0, INPUT);
  pinMode(soundD0, INPUT);

  pinMode(led, OUTPUT);
}

void loop() {
  int sensorData = analogRead(soundA0);
  Serial.print("Sound = ");
  Serial.println(sensorData);
  
  int sound = digitalRead(soundD0);

  if (sound == 1) 
  {
    if (ledState == false) 
    {
      ledState = true;
      digitalWrite(led, HIGH);
      delay(500);
    } 
    
    else 
    {
      ledState = false;
      digitalWrite(led, LOW);
      delay(500);
    }
  }
}
