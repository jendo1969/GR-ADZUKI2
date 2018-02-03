/*
MOTOR
*/

int MOTOR0_F = 9;
int MOTOR0_B = 10;
int MOTOR1_F = 6;
int MOTOR1_B = 11;

int Speed = 0;
int MaxSpeed = 150;
int SpeedAmount = 5;

// the setup routine runs once when you press reset:
void setup()  { 
  // declare pin 9,10,6,11 to be an output:
  pinMode(MOTOR0_F, OUTPUT);
  pinMode(MOTOR0_B, OUTPUT);
  pinMode(MOTOR1_F, OUTPUT);
  pinMode(MOTOR1_B, OUTPUT);
} 

// the loop routine runs over and over again forever:
void loop()  { 
  analogWrite(MOTOR0_F, Speed);    
  analogWrite(MOTOR0_B, 0);    
  analogWrite(MOTOR1_F, Speed);    
  analogWrite(MOTOR1_B, 0);    

  // change the brightness for next time through the loop:
  Speed = Speed + SpeedAmount;

  if (Speed == 0 || Speed == MaxSpeed) {
    SpeedAmount = -SpeedAmount ; 
  }     
  // wait 
  delay(50);                            
}

