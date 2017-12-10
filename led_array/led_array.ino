int led[] = {6, 9, 10, 11, 12, 13, 22, 23, 24};
unsigned short cnt;

void setup() {
  // initialize the digital pin as an output.
  pinMode(led[0], OUTPUT);    // LED1
  pinMode(led[1], OUTPUT);    // LED2     
  pinMode(led[2], OUTPUT);    // LED3
  pinMode(led[3], OUTPUT);    // LED4     
  pinMode(led[4], OUTPUT);    // LED5     
  pinMode(led[5], OUTPUT);    // LED6     
  pinMode(led[6], OUTPUT);    // RED LED COMMON  
  pinMode(led[7], OUTPUT);    // GREEN LED COMMO     
  pinMode(led[8], OUTPUT);    // BLUE LED COMMON   
  
  cnt = 64;
}

void loop() {
  unsigned short tmp;
  tmp = cnt;
  for(int i=0;i<9;i++)
  {
      if(tmp & 0x0001 == 0x0001)
      {
        digitalWrite(led[i], HIGH);
      }
      else
      {
        digitalWrite(led[i], LOW);
      }
      tmp >>= 1;
  }
     
  cnt++;
  cnt %= 512;
  if(cnt == 0)
  {
    cnt = 64;
  }
  
  delay(100);  // wait for 100ms
}
