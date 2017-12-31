/*
  Serial Output
 */
 
int sensorPin = A2;    // select the input pin for the light sensor
int lightSensor = 0;    // first analog sensor

void setup()
{
  // start serial port at 9600 bps and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect.
  }

  establishContact();  // send a byte to establish contact until receiver responds 
}

void loop()
{
  // read first analog input:
  lightSensor = analogRead(sensorPin);
  // send sensor values:
  Serial.println(lightSensor);    
  delay(500);
}

void establishContact() {
  while (Serial.available() <= 0) {
    Serial.println("Initializing");   // send an initial string
    delay(500);
  }
}
