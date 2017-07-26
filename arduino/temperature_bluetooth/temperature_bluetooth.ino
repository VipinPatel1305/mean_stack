
int reading;
float referenceVoltage;

#define TXPIN 6
#define RXPIN 7
//SoftwareSerial ble(TXPIN, RXPIN);
void setup() {
  // put your setup code here, to run once:
  //analogReference(INTERNAL);
  referenceVoltage = 1.1;

  Serial.begin(9600);
  delay(1000);
  //ble.begin(9600);
  //Serial.println("test message");
}

int readTemp1()
{
 int tempPin = 5;  
int val = analogRead(tempPin);
float mv = ( val/1024.0)*5000; 
float cel = mv/10;
int iVal = (int)cel;
return iVal;
}

int readTemp()
{
  int tempPin = 5;
  float temp;
  //dicard first value
  reading = analogRead(tempPin);
  reading = 0;

  
  for(int i = 0; i < 10; i++)
  {
    reading += analogRead(tempPin);
    delay(40);
  }

   temp =  (referenceVoltage * reading * 10) / 1023;
   int intVal = (int)temp;
   return intVal;
}

void loop() {
  // put your main code here, to run repeatedly:
  int temp = readTemp1();

  char ar[3];
  ar[1] = 48 + temp - (temp/10) * 10;
  ar[0] = 48 + temp/10;
  ar[2] = '\0';
  Serial.write("[");
  Serial.write(ar);
  Serial.write("]");
  delay(5000);
}

