/*
  Serial Output
 */
 
int sensorPin = A2;    // select the input pin for the light sensor
int lightSensor = 0;    // first analog sensor

void setup()
{
  // start serial port at 9600 bps and wait for port to open:
  Serial1.begin(9600);
  while (!Serial1) {
    ; // wait for serial port to connect.
  }

  establishContact();  // send a byte to establish contact until receiver responds 
}

void loop()
{
  // if we get a valid byte, read analog ins:
  if (Serial1.available() > 0) {
    // read first analog input:
    lightSensor = analogRead(sensorPin);
    // send sensor values:
    Serial1.println(lightSensor);    
  }
  delay(300);
}

void establishContact() {
  while (Serial1.available() <= 0) {
    Serial1.println("Initializing");   // send an initial string
    delay(300);
  }
}

