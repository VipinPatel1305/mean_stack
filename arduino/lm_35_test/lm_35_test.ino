#define  LM_PREC 0


void setup() {
  // put your setup code here, to run once:
pinMode(LM_PREC, INPUT);
 Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
      float temp;
    //dicard first value
    int reading = analogRead(LM_PREC);
    reading = 0;
    
    for(int i = 0; i < 10; i++)
    {
      reading += analogRead(LM_PREC);
      delay(40);
    }

    float sum = reading;
    sum = sum/10.0;
    float mv = (sum / 1024.0) * 500;
    Serial.println(mv);


}
