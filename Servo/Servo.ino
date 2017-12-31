/* Servo
*/ 

#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
const int L_button = 3;     // the number of the pushbutton pin
 
int pos = 0;    // variable to store the servo position 
int L_buttonState = 0;         // variable for reading the pushbutton status

void setup() 
{ 
  myservo.attach(4);  // attaches the servo on pin 4 to the servo object 
  myservo.write(pos);              // tell servo to go to position in variable 'pos' 
  
  // initialize the pushbutton pin as an input:
  pinMode(L_buttonState, INPUT_PULLUP);     
} 
 
void loop() 
{ 
  // read the state of the pushbutton value:
  L_buttonState = digitalRead(L_button);
  
  // check if the pushbutton is pressed.
  if (L_buttonState == LOW)
  {     
    for(pos = 0; pos <= 180; pos += 1) // goes from 0 degrees to 180 degrees 
    {                                  // in steps of 1 degree 
      myservo.write(pos);              // tell servo to go to position in variable 'pos' 
      delay(10);                       // waits 105ms for the servo to reach the position 
    } 
    for(pos = 180; pos>=0; pos-=1)     // goes from 180 degrees to 0 degrees 
    {                                
      myservo.write(pos);              // tell servo to go to position in variable 'pos' 
      delay(10);                       // waits 10ms for the servo to reach the position 
    }
  } 
} 
