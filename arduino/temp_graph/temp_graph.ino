#include <EEPROM.h>

#define LM_PREC 0
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LM_PREC, INPUT);
  //clearEPROM();
  displayEPROM();
}


void displayEPROM()
{
  for(int i = 0; i < 1024; i++)
  {
    byte value = EEPROM.read(i);
    int t = value;
    if(t == 1)
      break;
    Serial.print("Addr: ");
    Serial.print(i);
    Serial.print(" ");
    Serial.print(" Value ");
    Serial.println(t);
  }
}



void loop() {
  // put your main code here, to run repeatedly:
  computeTempAndStore();
  delay(60000);
}

void computeTempAndStore()
{
     float temp;
    //dicard first value
    int reading = analogRead(LM_PREC);
    reading = 0;

    for (int i = 0; i < 10; i++)
    {
      reading += analogRead(LM_PREC);
      delay(40);
    }

    reading = reading / 10;
    float mv = (reading / 1024.0) * 5000;
    int cel = mv / 10;
    Serial.println(cel);
    writeFallSafe(cel);
}


void writeFallSafe(int temperature)
{
  for(int i = 0; i < 1024; i++)
  {
    byte value = EEPROM.read(i);
    int t = value;
    if(t == 1)
    {
      EEPROM.write(i, temperature);
      Serial.print("Writing at: ");
      Serial.println(i);
      break;
    }
  }
}


void clearEPROM()
{
  for(int i = 0; i < 1024; i++)
  {
    EEPROM.write(i, 1);
  }
}
