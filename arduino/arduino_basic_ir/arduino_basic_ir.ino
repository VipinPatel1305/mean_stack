int irPin=3;  //digital 2 (ATTINT85 pin 7)
int ledPin=7; //digital 0 (ATTINY85 pin 5) 

int start_bit = 2200;

 const byte BIT_PER_BLOCK = 32;
 
void setup()
{
 pinMode(irPin,INPUT);
 pinMode(ledPin,OUTPUT);
 digitalWrite(0,HIGH);
 Serial.begin(9600);
}
 
void loop()
{
  int data[BIT_PER_BLOCK];
  int i;  
 while(pulseIn(irPin, LOW) < start_bit); //Wait for a start bit
  for(i = 0 ; i < BIT_PER_BLOCK ; i++) {
    //Start measuring bits, I only want high pulses 
    //you may want to use LOW pulse --> pulseIn(irPin, LOW)
    data[i] = pulseIn(irPin, HIGH);   
  }
 
  delay(100);
  for(i = 0 ; i < BIT_PER_BLOCK ; i++) {
    Serial.println(data[i]);
  }  
  Serial.println("========="); 
}
