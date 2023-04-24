

  #include "DHT.h"
  #define DHTPIN 7     //                    DHT11 Sensor attached to D7 Pin of Arduino Mega
  #define DHTTYPE DHT11   // DHT 11
  DHT dht(DHTPIN, DHTTYPE);
  
  
  #include <Stepper.h>              // Stepper Motor as Fan
  const int stepsPerRevolution = 2038;
  Stepper myStepper = Stepper(stepsPerRevolution, 8, 10, 9, 11);
  
  void setup() {
    
   Serial.begin(9600);
   dht.begin();
  }
  
  void loop() {


  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);
  
  Serial.print("Temperature in Faranheit: ");
  Serial.print(f);
  Serial.print("°F");
  Serial.println();
  delay(2000);
  
  if (f>70)                                   //     if temperature is greather than 70 than turn on fan
  {
  myStepper.setSpeed(10);
  myStepper.step(stepsPerRevolution);
  }
  else if (f<70)                               //     if temperature is less than 70 than turn off fan
  {
  myStepper.setSpeed(0);
  myStepper.step(0);
  }
  

}
