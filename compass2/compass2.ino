/*
 DEGITAL COMPASS HMC5883
 acceleration
*/

#include <Wire.h> //I2C Arduino Library

const int X_Axis = A3;
const int Y_Axis = A4;
const int Z_Axis = A5;

double X_Value = 0; 
double Y_Value = 0; 
double Z_Value = 0; 

double R_Value = 0; 
double X_degree = 0; 
double Y_degree = 0; 
double Z_degree = 0; 

double roll = 0; 
double pitch = 0; 

void setup()
{
  Serial.begin(9600);  // start serial for output
  Wire.begin();        // join i2c bus (address optional for master)
  
  //Put the HMC5883 IC into the correct operating mode
  Wire.beginTransmission(0x1E); //open communication with HMC5883
  Wire.write(0x02); //select mode register
  Wire.write(0x00); //continuous measurement mode
  Wire.endTransmission();
}

void loop()
{
  int x,y,z; //triple axis data

  // read the value from the sensor:
  X_Value = (double)analogRead(X_Axis) - 512;    
  Y_Value = (double)analogRead(Y_Axis) - 512;    
  Z_Value = (double)analogRead(Z_Axis) - 512;   
 
  X_Value = -X_Value;
  roll = atan2(Y_Value, Z_Value);
  pitch = atan2(-X_Value, (Y_Value * sin(roll) + Z_Value * cos(roll)));
    
  // send sensor values:
  Serial.print("(rokll,pitch)=(");
  Serial.print(roll * 180 / PI);
  Serial.print(", ");
  Serial.print(pitch * 180 / PI);
  Serial.print(")");
  Serial.println();

  //Tell the HMC5883 where to begin reading data
  Wire.beginTransmission(0x1E);
  Wire.write(0x03); //select register 3, X MSB register
  Wire.endTransmission();  
 
 //Read data from each axis, 2 registers per axis
  Wire.requestFrom(0x1E, 6);
  if(6<=Wire.available())
  {
    x = Wire.read()<<8; //X msb
    x |= Wire.read();   //X lsb
    z = Wire.read()<<8; //Z msb
    z |= Wire.read();   //Z lsb
    y = Wire.read()<<8; //Y msb
    y |= Wire.read();   //Y lsb
  }
  
  // X,Y軸の位置からラジアンを算出する
  float rad = atan2(y,x); 
  float rad2 = atan2(z*sin(roll)-y*cos(roll), z*cos(pitch)+y*sin(pitch)*sin(roll)+z*sin(pitch)*cos(roll)); 
 
  // XYZの3軸のうち、X軸方向の角度
  float degree = rad * 180 / M_PI;  
  if(degree <0){
    degree = 360 + degree;
  }
  float degree2 = rad2 * 180 / M_PI + 180;  
  if(degree2 <0){
    degree2 = 360 + degree2;
  }
  else if(degree2 > 360)
  {
    degree2 = degree2 - 360;
  }
 
  //Print out values of each axis
  Serial.print("(degree, degree2)=(");
  Serial.print(degree);  
  Serial.print(", ");
  Serial.print(degree2);  
  Serial.print(")");
  Serial.println();
  
  delay(500);  
}
