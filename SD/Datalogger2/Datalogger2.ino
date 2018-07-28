#include <SparkFun_RHT03.h>

/*
  SD2 card datalogger 	 
 */

// Include the library:
#include <SD.h>
#include <math.h>

/////////////////////
// Pin Definitions //
/////////////////////
int led6 = 13;
int led_R = 22;
int led_G = 23;
int led_B = 24;
// change this to match your SD2 shield or module;
const int chipSelect = 27;    //P41
const int B = 4275;            // B value of the thermistor
const long R0 = 100000;        // 100k
const int pinTempSensor = A1;  // Grove - Temperature Sensor connect to A1

const int pinLightSensor = A6;  // Grove - Light Sensor connect to A6
float Rsensor; //Resistance of sensor in K

const int pinMoistSensor = A0;  // Grove - Moisture Sensor connect to A0
int MoistureValue = 0.0;

float temperature = 0.0;
String dataString = "";

void setup()
{
  // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(chipSelect, OUTPUT);
  pinMode(led6, OUTPUT);     
  pinMode(led_R, OUTPUT);     
  pinMode(led_G, OUTPUT);     
  pinMode(led_B, OUTPUT);  
  
  digitalWrite(led_R, LOW);   // RED LED COMMON  
  digitalWrite(led_G, LOW);   // GREEN LED COMMON
  digitalWrite(led_B, HIGH);  // BLUE LED COMMON
  
  // see if the card is present and can be initialized:
  if (!SD2.begin(chipSelect)) {
    // don't do anything more:
    return;
  }
}

void loop()
{
//////////////////////////// TEMPERATUR SENSOR /////////////////////////////////////
  int a = analogRead(pinTempSensor);
  
  float R = 1023.0 / ((float)a) - 1.0;
  R = 100000.0 * R;
  
  //convert to temperature via datasheet ;
  temperature = 1.0 / (log(R / 100000.0) / B + 1 / 298.15) - 273.15;

//////////////////////////// LIGHT SENSOR /////////////////////////////////////
  int sensorValue = analogRead(pinLightSensor);
  Rsensor=(float)(1023 - sensorValue) * 10 / sensorValue;
  
//////////////////////////// MOISTURE SENSOR /////////////////////////////////////
  MoistureValue = analogRead(pinMoistSensor);
  
  // make a string for assembling the data to log:
  dataString = String(temperature, 1) ;
  dataString += ","; 
  dataString += String(Rsensor, 1) ;
  dataString += ","; 
  dataString += String(MoistureValue, DEC) ;

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD2.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
  }  

  digitalWrite(led6, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);
  digitalWrite(led6, LOW);    // turn the LED off by making the voltage LOW
  delay(500);
}









