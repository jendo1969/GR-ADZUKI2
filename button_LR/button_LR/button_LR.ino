/*
  Button
  */

// constants won't change. They're used here to 
// set pin numbers:
const int R_button = 2;     // the number of the pushbutton pin
const int L_button = 3;     // the number of the pushbutton pin

const int led1 = 6;
const int led6 = 13;

const int led_R = 22;
const int led_G = 23;
const int led_B = 24;

// variables will change:
int L_buttonState = 0;         // variable for reading the pushbutton status
int R_buttonState = 0;         // variable for reading the pushbutton status

void setup() {
  // initialize the LED pin as an output:
  pinMode(led1, OUTPUT);     
  pinMode(led6, OUTPUT);     
  pinMode(led_R, OUTPUT);     
  pinMode(led_G, OUTPUT);     
  pinMode(led_B, OUTPUT);     

  digitalWrite(led_R, HIGH);  // RED LED COMMON
  digitalWrite(led_G, LOW);  // RED LED COMMON
  digitalWrite(led_B, LOW);  // RED LED COMMON

  // initialize the pushbutton pin as an input:
  pinMode(L_buttonState, INPUT_PULLUP);     
  pinMode(R_buttonState, INPUT_PULLUP);     
}

void loop(){
  // read the state of the pushbutton value:
  L_buttonState = digitalRead(L_button);
  R_buttonState = digitalRead(R_button);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is LOW:
  if (L_buttonState == LOW)
  {     
    // turn LED on:    
    digitalWrite(led1, HIGH);  
  } 
  else 
  {
    // turn LED off:
    digitalWrite(led1, LOW); 
  }
  
  // check if the pushbutton is pressed.
  // if it is, the buttonState is LOW:
  if (R_buttonState == LOW)
  {     
    // turn LED on:    
    digitalWrite(led6, HIGH);  
  } 
  else 
  {
    // turn LED off:
    digitalWrite(led6, LOW); 
  }
}
