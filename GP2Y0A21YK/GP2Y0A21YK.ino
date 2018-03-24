/*
bend sensor
*/

const int R_Bend = A0;
const int L_Bend = A1;

int R_Bend_Value = 0; 
int L_Bend_Value = 0; 

const int distancePin = A6;
int distanceValue = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect.
  }
}

void loop() {
  // read the value from the sensor:
  R_Bend_Value = analogRead(R_Bend);    
  L_Bend_Value = analogRead(L_Bend);    
  
  distanceValue = analogRead(distancePin); 
    
  // send sensor values:
  Serial.print("(R,L,d)=(");
  Serial.print(R_Bend_Value);
  Serial.print(", ");
  Serial.print(L_Bend_Value);
  Serial.print(", ");
  Serial.print(distanceValue);
  Serial.print(")");
  Serial.println();

  delay(300);                  
}


