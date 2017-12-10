/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// give it a name:
int led1 = 6;
int led2 = 9;
int led3 = 10;
int led4 = 11;
int led5 = 12;
int led6 = 13;

int led_R = 22;
int led_G = 23;
int led_B = 24;


// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led1, OUTPUT);     
  pinMode(led2, OUTPUT);     
  pinMode(led3, OUTPUT);     
  pinMode(led4, OUTPUT);     
  pinMode(led5, OUTPUT);     
  pinMode(led6, OUTPUT);     
  pinMode(led_R, OUTPUT);     
  pinMode(led_G, OUTPUT);     
  pinMode(led_B, OUTPUT);     

  digitalWrite(led_R, LOW);   // RED LED COMMON
  digitalWrite(led_G, LOW);   // GREEN LED COMMON
  digitalWrite(led_B, HIGH);  // BLUE LED COMMON
}

// the loop routine runs over and over again forever:
void loop() {
  
  
  digitalWrite(led1, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(led2, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(led3, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(led4, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(led5, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(led6, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);               // wait for a second
  digitalWrite(led1, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(led2, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(led3, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(led4, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(led5, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(led6, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);               // wait for a second
}
