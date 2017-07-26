#define RELAY1  7 
void setup() {
  // put your setup code here, to run once:
  pinMode(RELAY1, OUTPUT); 
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(RELAY1, 0);  
  digitalWrite(13, HIGH);
  delay(5000);
  
  digitalWrite(13, LOW);
  digitalWrite(7, 1);
  delay(5000);
  
}
