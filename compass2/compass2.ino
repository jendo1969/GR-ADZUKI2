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
 
  R_Value = sqrt(X_Value*X_Value + Y_Value*Y_Value + Z_Value*Z_Value); 
  //R_Value = 204; 
  X_degree = atan(X_Value / sqrt(Y_Value*Y_Value+Z_Value*Z_Value)) * 180 / PI;
  Y_degree = atan(Y_Value / sqrt(X_Value*X_Value+Z_Value*Z_Value)) * 180 / PI;
  Z_degree = atan(Z_Value / sqrt(X_Value*X_Value+Y_Value*Y_Value)) * 180 / PI;
  
  // send sensor values:
  Serial.print("(x,y,z)=(");
  Serial.print(X_Value);
  Serial.print(", ");
  Serial.print(Y_Value);
  Serial.print(", ");
  Serial.print(Z_Value);
  Serial.print("), Tx=");
  Serial.print(X_degree);
  Serial.print(", Ty=");
  Serial.print(Y_degree);
  Serial.print(", Tz=");
  Serial.print(Z_degree);
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
  
  // XYZの3軸のうち、X軸方向の角度
  // ※X軸方向の詳細は記事を参照ください。
  float degree = rad * 180 / M_PI;  
  if(degree <0){
    degree = 360 + degree;
  }
  
  //Print out values of each axis
  Serial.print("x: ");
  Serial.print(x);
  Serial.print("  y: ");
  Serial.print(y);
  Serial.print("  z: ");
  Serial.print(z);
  Serial.print(" degree: ");
  Serial.println(degree);  
  
  delay(500);  
}
