#define LED_PIN A5
void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT);
}

int flagOn = 0;
void loop() {
  // put your main code here, to run repeatedly:

  if(flagOn == 0)
  {
    flagOn = 1;
    digitalWrite(LED_PIN, HIGH);
  }
  else
  {
    flagOn = 0;
    digitalWrite(LED_PIN, LOW);    
  }

  delay(1000);
}
