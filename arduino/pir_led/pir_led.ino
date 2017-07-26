int lamp = 4;                // choose the pin for the LED
int pirPin = 2;               // choose the input pin (for PIR sensor)


void setup() {
  int flag = 0;
  pinMode(lamp, OUTPUT);      // declare LED as output
  pinMode(pirPin, INPUT);     // declare sensor as input
  
  for(int i = 0; i < 5; i++)
  {
       
      if(flag == 0)
      {
        flag = 1;
        digitalWrite(lamp, HIGH);
      }
      else
      {
        flag = 0;
         digitalWrite(lamp, LOW);
      }
  }
  
  digitalWrite(lamp, LOW);
  delay(4000);
}

int counter = 0;
void loop()
{
  int val = digitalRead(pirPin);

  if (val == HIGH)
  {
      digitalWrite(lamp, HIGH);
      counter = 0;     
  }
  else
  {
    if(counter == 40)
    {
      counter = 0;
      digitalWrite(lamp, LOW);
    }
     else
      counter++;           
  }
 
  delay(500);
}


