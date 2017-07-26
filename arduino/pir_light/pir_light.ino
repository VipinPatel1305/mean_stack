int lamp = 4;                // choose the pin for the LED
int pirPin = 2;               // choose the input pin (for PIR sensor)


void setup() {
  pinMode(lamp, OUTPUT);      // declare LED as output
  pinMode(pirPin, INPUT);     // declare sensor as input
  digitalWrite(lamp, HIGH);
  delay(40000);
}

int counter = 0;
void loop()
{
  int val = digitalRead(pirPin);

  if (val == HIGH)
  {
      digitalWrite(lamp, LOW);
      counter = 0;     
  }
  else
  {
    if(counter == 40)
    {
      counter = 0;
      digitalWrite(lamp, HIGH);
    }
     else
      counter++;           
  }
 
  delay(500);
}


