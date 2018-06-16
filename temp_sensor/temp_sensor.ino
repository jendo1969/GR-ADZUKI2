#include <math.h>

const int B = 4275;            // B value of the thermistor
const long R0 = 100000;        // 100k
const int pinTempSensor = A1;  // Grove - Temperature Sensor connect to A1

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  int a = analogRead(pinTempSensor);
  
  float R = 1023.0 / ((float)a) - 1.0;
  R = 100000.0 * R;
  
  //convert to temperature via datasheet ;
  float temperature = 1.0 / (log(R / 100000.0) / B + 1 / 298.15) - 273.15;
  
  Serial.print("temperature = ");
  Serial.println(temperature);  
  
  delay(1000);
}



