int reading;
float referenceVoltage;
#define LM_PREC 0
void setup() {
  // put your setup code here, to run once:
 
 // analogReference(INTERNAL);
  referenceVoltage = 1.1;
  Serial.begin(9600);
}

void preciseMethod()
{
  float temp;
  //dicard first value
  reading = analogRead(LM_PREC);
  reading = 0;
  
  for(int i = 0; i < 10; i++)
  {
    reading += analogRead(LM_PREC);
    delay(40);
  }

  temp =  (referenceVoltage * reading * 10) / 1023;
  int iTem = temp * 100;
  int u = iTem/1000;
  int t = iTem - u * 1000; 
  t = t/100;

  Serial.println(iTem/100);
}

void generalMethod()
{
    float temp;
    //dicard first value
    int reading = analogRead(LM_PREC);
    
    reading = 0;
    
    for(int i = 0; i < 10; i++)
    {
      reading += analogRead(LM_PREC);
      delay(40);
    }

    reading = reading/10;
    
    float mv = (reading / 1024.0) * 5000;
    int cel = mv / 10;
   Serial.println(cel);
}
void loop() {

  //preciseMethod();
  generalMethod();
  delay(5000);
}
