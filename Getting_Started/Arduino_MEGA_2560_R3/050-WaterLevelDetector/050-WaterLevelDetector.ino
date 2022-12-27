// Sensor pins
constexpr byte WATER_DETECTOR_PIN = A0;
constexpr byte POWER_PIN = 7;

void setup() {
  pinMode(WATER_DETECTOR_PIN, INPUT);
	pinMode(POWER_PIN, OUTPUT);
	
	// Set to LOW so no power flows through the sensor
	digitalWrite(POWER_PIN, LOW);
	
	Serial.begin(115200);
}

void loop() {
	//get the reading from the function below and print it
	int waterLevel = readSensor();
	
	Serial.print("Water level: ");
	Serial.println(waterLevel);
	
	delay(1000);
}

//This is a function used to get the reading
int readSensor() {
	digitalWrite(POWER_PIN, HIGH);	// Turn the sensor ON
	delay(10);							        // wait 10 milliseconds
	int val = analogRead(WATER_DETECTOR_PIN);		// Read the analog value form sensor
	digitalWrite(POWER_PIN, LOW);		// Turn the sensor OFF
	return val;							        // return current reading
}