
#define SPEAKER 9
void setup()  { 
  // declare pin 9 to be an output:
  pinMode(SPEAKER, OUTPUT);
  beep(50);
  beep(50);
  beep(50);
  delay(1000);
} 

void loop()  { 
  beep(250); 
}

void beep(unsigned char delayms){
  
  static int freq = 20;
  analogWrite(SPEAKER, freq);      // Almost any value can be used except 0 and 255
                           // experiment to get the best tone
  delay(delayms);          // wait for a delayms ms
  digitalWrite(SPEAKER, 0);       // 0 turns it off
  delay(delayms);          // wait for a delayms ms  
 /*
 if(freq == 200)
    freq = 100;
  else
   freq += 20; 
   */
}  

