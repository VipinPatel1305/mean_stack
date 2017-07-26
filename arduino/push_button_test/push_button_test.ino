void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A0, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int readVal = analogRead(A0);

  if(readVal > 1000)
    Serial.println(readVal);
  delay(1000);
}
