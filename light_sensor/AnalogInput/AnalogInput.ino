/*
  Analog Input
 */

int sensorPin = A2;    // select the input pin for the light sensor
int LED6 = 13;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(LED6, OUTPUT);  
}

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);    
  // turn the ledPin on
  digitalWrite(LED6, HIGH);  
  // stop the program for <sensorValue> milliseconds:
  delay(sensorValue);          
  // turn the ledPin off:        
  digitalWrite(LED6, LOW);   
  // stop the program for for <sensorValue> milliseconds:
  delay(sensorValue);                  
}
