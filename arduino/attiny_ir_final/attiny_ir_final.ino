
int irPin = 3; //Sensor pin connect to digital pin2 (ATINY85 pin7)
int start_bit = 2200; //Start bit threshold (Microseconds)
int bin_1 = 1000; //Binary 1 threshold (Microseconds)
int bin_0 = 400; //Binary 0 threshold (Microseconds)
const byte BIT_PER_BLOCK = 32;

int ledPin=0;
 
void setup() {
  pinMode(irPin, INPUT);
   //Serial.begin(9600);
}
 
void loop() {
  //DigiKeyboard.update(); //keep on updating the keyboard 
  // this is generally not necessary but with some older systems it seems to
  // prevent missing the first character after a delay:
  //DigiKeyboard.sendKeyStroke(0);
 
  int key = getIRKey();        //Fetch the key

 if(key == 7 || key == 14)
 {
  for(int p = 0; p < 10; p++)
  {
    digitalWrite(ledPin, HIGH);
    delay(100);
    digitalWrite(ledPin, LOW);
    delay(100);
  }
 }

  if(key == 22 || key == 11)
 {
  for(int p = 0; p < 10; p++)
  {
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
    delay(500);
  }
 }

  digitalWrite(ledPin, LOW);
  /*if(key != 0) //Ignore keys that are zero
  {
    //DigiKeyboard.print("=>");  //uncomment this if you want to 
    //DigiKeyboard.println(key); //print out the value of the button
   // Serial.println(key);
  }*/
}
 
/////////////////////////////////////////////////////////////
// decode infrared signal
/////////////////////////////////////////////////////////////
int getIRKey() {
  int data[BIT_PER_BLOCK];
  int i;
  while(pulseIn(irPin, HIGH) < start_bit); //Wait for a start bit
 
  for(i = 0 ; i < BIT_PER_BLOCK ; i++) 
    data[i] = pulseIn(irPin, HIGH); //Start measuring bits, I only want HIGH pulses
 
  delay(100);  
  for(i = 0 ; i < BIT_PER_BLOCK ; i++) //Parse them
  {   
    if(data[i] > bin_1) //is it a 1?
      data[i] = 1;
    else if(data[i] > bin_0) //is it a 0?
      data[i] = 0;
    else
      return -1; //Flag the data as invalid; Return -1 on invalid data
  }
  //based on NEC protocol, command data started from bit 16
  //and end with bit 24 (8 bits long)
  int result = 0;
  for(i = 16 ; i < 24; i++) { 
    //DigiKeyboard.print(data[i]); //print out the value of button in binary form
    if(data[i] == 1) result |= (1<<i-16); //Convert data bits to integer
  }  
  return result; //Return key number
}
