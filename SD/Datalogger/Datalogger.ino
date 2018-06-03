#include <SparkFun_RHT03.h>

/*
  SD2 card datalogger 	 
 */

// Include the library:
#include <SparkFun_RHT03.h>
#include <SD.h>

/////////////////////
// Pin Definitions //
/////////////////////
// change this to match your SD2 shield or module;
const int chipSelect = 27;    //P41
const int RHT03_DATA_PIN = 13; // RHT03 data pin

///////////////////////////
// RHT03 Object Creation //
///////////////////////////
RHT03 rht; // This creates a RTH03 object, which we'll use to interact with the sensor

float latestHumidity = 0;
float latestTempC = 0;
String dataString = "";

void setup()
{
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  Serial.print("Initializing SD2 card...");
  // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(chipSelect, OUTPUT);
  
  // see if the card is present and can be initialized:
  if (!SD2.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
  
  // Call rht.begin() to initialize the sensor and our data pin
  rht.begin(RHT03_DATA_PIN);

  while(1)
  {  
    int updateRet = rht.update();
     // If successful, the update() function will return 1.
     // If update fails, it will return a value <0
     if (updateRet != 1)
     {
       Serial.println("RHT03 not initialized.");
       delay(RHT_READ_INTERVAL_MS);
     }
     else
     {
       Serial.println("RHT03 initialized.");
       break;
     }
  }
}

void loop()
{
  int updateRet = rht.update();
	
  // If successful, the update() function will return 1.
  // If update fails, it will return a value <0
  if (updateRet == 1)
  {
    // The humidity(), tempC(), and tempF() functions can be called -- after 
    // a successful update() -- to get the last humidity and temperature
    // value 
    latestHumidity = rht.humidity();
    latestTempC = rht.tempC();
  }
  
  // make a string for assembling the data to log:
  dataString = String(latestHumidity, 1) ;
  dataString += ","; 
  dataString += String(latestTempC, 1) ;

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD2.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    // Now print the values:
    Serial.println("Humidity: " + String(latestHumidity, 1) + " %");
    Serial.println("Temp (C): " + String(latestTempC, 1) + " deg C");
  }  
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  } 
  delay(10000);
}









