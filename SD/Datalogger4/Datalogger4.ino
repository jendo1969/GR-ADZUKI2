#include <SparkFun_RHT03.h>

/*
  SD2 card datalogger 	 
 */

// Include the library:
#include <RTC.h>
#include <SD.h>
#include <math.h>

/////////////////////
// Pin Definitions //
/////////////////////
int led6 = 13;
int led_R = 22;
int led_G = 23;
int led_B = 24;
int led_stat = 0;

//MOTOR1
int MOTOR1_F = 6;
int MOTOR1_B = 11;

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

RTC rtc;
char file_b[] = ".txt";
char filename[64];
char input[64];
char buff[64];
int old_sec;
int old_min;
int i;

int log_mode = 0;

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);

  // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(chipSelect, OUTPUT);
  pinMode(led6, OUTPUT);     
  pinMode(led_R, OUTPUT);     
  pinMode(led_G, OUTPUT);     
  pinMode(led_B, OUTPUT);  

  pinMode(MOTOR1_F, OUTPUT);
  pinMode(MOTOR1_B, OUTPUT);

  digitalWrite(led_R, LOW);   // RED LED COMMON  
  digitalWrite(led_G, LOW);   // GREEN LED COMMON
  digitalWrite(led_B, HIGH);  // BLUE LED COMMON

  if(!rtc.begin()){
    Serial.println("RTC failed, or not present");
    // don't do anything more:
    return;
  }  
  Serial.println("RTC initialized.");

  rtc.setDateTime(2018, 7, 15, 0, 0, 0, RTC_WEEK_SUNDAY);
  old_sec = 0;
  i = 0;
}

void loop()
{
  int year, mon, day, hour, min, sec, week;
  rtc.getDateTime(year, mon, day, hour, min, sec, week);
  year = 2000+year;
  sprintf(filename, "%04d%02d%02d%s", year, mon, day, file_b);

  if(log_mode == 0)
  {
  if (Serial.available() > 0) 
    {
      // get incoming byte:
      input[i] = Serial.read();

      // 文字数が2以上 or 末尾文字
      if (input[i] == ';')
      {
        // 末尾に終端文字の挿入
        input[i] = '\0';
        if((i==16) && (input[0]=='T'))
        { //01234567890123456
          //T201807212232006;
          sscanf(&input[1],"%04d%02d%02d%02d%02d%02d%d", &year, &mon, &day, &hour, &min, &sec, &week);
          rtc.setDateTime(year, mon, day, hour, min, sec, week);
          sprintf(buff, "%04d/%02d/%02d %02d:%02d:%02d %d\r", year, mon, day, hour, min, sec, week);
          Serial.println(buff);
        }
        else if((i==2) && (input[0]=='T') && (input[1]=='?'))
        {
          sprintf(buff, "%04d/%02d/%02d %02d:%02d:%02d %d\r", year, mon, day, hour, min, sec, week);
          Serial.println(buff);
        }
        else if((i==2) && (input[0]=='o') && (input[1]=='n'))
        {
          digitalWrite(led6, HIGH);
          sprintf(buff, "%04d/%02d/%02d %02d:%02d:%02d %d\r", year, mon, day, hour, min, sec, week);
          Serial.println(buff);
        }
        else if((i==3) && (input[0]=='o') && (input[1]=='f') && (input[2]=='f'))
        {
          digitalWrite(led6, LOW);
        }
        else if((i==3) && (input[0]=='S') && (input[1]=='T') && (input[2]=='A'))
        {
          // see if the card is present and can be initialized:
          if (!SD2.begin(chipSelect)) 
          {
            Serial.println("Card failed, or not present");
            // don't do anything more:
            return;
          }
          log_mode = 1;
          Serial.println("card initialized.");
        }
        // カウンタの初期化
        i = 0;
      }
      else
      {
        i++;
      }
    }
  }
  else
  {
//////////////////////////// TEMPERATUR SENSOR /////////////////////////////////////
    int a = analogRead(pinTempSensor);
    float R = 1023.0 / ((float)a) - 1.0;
    R = R0 * R;
    //convert to temperature via datasheet ;
    temperature = 1.0 / (log(R / R0) / B + 1 / 298.15) - 273.15;
    temperature += 10.0;
//////////////////////////// LIGHT SENSOR /////////////////////////////////////
    int sensorValue = analogRead(pinLightSensor);
    Rsensor=(float)(1023 - sensorValue) * 10 / sensorValue;
   
//////////////////////////// MOISTURE SENSOR /////////////////////////////////////
    MoistureValue = analogRead(pinMoistSensor);
   
    if(old_sec > sec)
    {
      // make a string for assembling the data to log:
      if(hour < 10)
      {
        dataString = "0";
      }
      else
      {
        dataString = "";
      }
      dataString += String(hour) ;
      dataString += ":"; 
      if(min < 10)
      {
        dataString += "0";
      }
      dataString += String(min) ;
      dataString += ", "; 
      dataString += String(temperature, 1) ;
      dataString += ", "; 
//      dataString += String(Rsensor, 1) ;
      dataString += String(sensorValue, DEC) ;
      dataString += ", "; 
      dataString += String(MoistureValue, DEC) ;
   
      Serial.println(dataString);
    
      // open the file. note that only one file can be open at a time,
      // so you have to close this one before opening another.
      sprintf(filename, "%04d%02d%02d%s", year, mon, day, file_b);
      File dataFile = SD2.open(filename, FILE_WRITE);
   
      // if the file is available, write to it:
      if (dataFile) 
      {
        dataFile.println(dataString);
        dataFile.close();
        // print to the serial port too:
      }
    }
   
    if( sec != old_sec)
    {
      digitalWrite(led6, led_stat);   // turn the LED on (HIGH is the voltage level)
      if(led_stat == 0)
      {
        led_stat = 1;
      }
      else
      {
        led_stat = 0;
      }
    }
    
    if(min != old_min)
    {
        analogWrite(MOTOR1_F, 255);    
        analogWrite(MOTOR1_B, 0);  
    }
    else
    {
      if(sec > 10)
      {
        analogWrite(MOTOR1_F, 0);    
        analogWrite(MOTOR1_B, 0);  
      }
    }
    
    old_sec = sec;
    old_min = min;
    delay(500);
  }
}










