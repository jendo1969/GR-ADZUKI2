// DEGITAL COMPASS HMC5883

#include <Wire.h> //I2C Arduino Library

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
  
  delay(250);  
}
