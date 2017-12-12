/*
 acceleration
*/

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

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect.
  }
}

void loop() {
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

  delay(300);                  
}


