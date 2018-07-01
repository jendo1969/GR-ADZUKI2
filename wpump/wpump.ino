/* Grove - Sensor 
*
* signal wire to A0.
* signal wire to A6.
*/

#include <math.h>

const int B = 4275;            // B value of the thermistor
const long R0 = 100000;        // 100k
const int pinTempSensor = A1;  // Grove - Temperature Sensor connect to A1

const int pinLightSensor = A6;  // Grove - Light Sensor connect to A6
float Rsensor; //Resistance of sensor in K

const int pinMoistSensor = A0;  // Grove - Moisture Sensor connect to A0
int MoistureValue = 0;

// MOTOR
const int MOTOR0_F = 9;
const int MOTOR0_B = 10;
const int MOTOR1_F = 6;
const int MOTOR1_B = 11;

void setup()
{
  Serial.begin(9600);
  
  // declare pin 9,10,6,11 to be an output:
  pinMode(MOTOR0_F, OUTPUT);
  pinMode(MOTOR0_B, OUTPUT);
  pinMode(MOTOR1_F, OUTPUT);
  pinMode(MOTOR1_B, OUTPUT);
  
  analogWrite(MOTOR0_F, 0);    
  analogWrite(MOTOR0_B, 0);    
  analogWrite(MOTOR1_F, 0);    
  analogWrite(MOTOR1_B, 0);   
}

void loop()
{
//////////////////////////// TEMPERATUR SENSOR /////////////////////////////////////
  int a = analogRead(pinTempSensor);
  
  float R = 1023.0 / ((float)a) - 1.0;
  R = 100000.0 * R;
  
  //convert to temperature via datasheet ;
  float temperature = 1.0 / (log(R / 100000.0) / B + 1 / 298.15) - 273.15;

//////////////////////////// LIGHT SENSOR /////////////////////////////////////
  int sensorValue = analogRead(pinLightSensor);
  Rsensor=(float)(1023 - sensorValue) * 10 / sensorValue;
  
//////////////////////////// MOISTURE SENSOR /////////////////////////////////////
  MoistureValue = analogRead(pinMoistSensor);
  
  Serial.print("temperature = ");
  Serial.println(temperature);  

  Serial.print("Light analog val = ");
  Serial.println(sensorValue);
  Serial.print("Light resistance ival = ");
  Serial.println(Rsensor, DEC);//show the light intensity on the serial monitor;
  
  Serial.print("Moisture = " );
  Serial.println(MoistureValue);
  
  analogWrite(MOTOR1_F, 255); 
    
  delay(1000);
}



