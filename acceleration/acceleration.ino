/*
 acceleration
*/

const int X_Axis = A3;
const int Y_Axis = A4;
const int Z_Axis = A5;

int X_Value = 0; 
int Y_Value = 0; 
int Z_Value = 0; 

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect.
  }
}

void loop() {
  // read the value from the sensor:
  X_Value = analogRead(X_Axis);    
  Y_Value = analogRead(Y_Axis);    
  Z_Value = analogRead(Z_Axis);    
  // send sensor values:
  Serial.print(X_Value);
  Serial.print(", ");
  Serial.print(Y_Value);
  Serial.print(", ");
  Serial.print(Z_Value);
  Serial.println();

  delay(300);                  
}


