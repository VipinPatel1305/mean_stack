const int buzzer = 6; 

void setup() {
  // put your setup code here, to run once:
pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output
}

int count = 0;
void loop(){

  if(count < 9)
  { 
  tone(buzzer, 3000); // Send 1KHz sound signal...
  delay(200);        // ...for 1 sec
  noTone(buzzer);     // Stop sound...
  delay(200);        // ...for 1sec
  count++;
  }
  
}
