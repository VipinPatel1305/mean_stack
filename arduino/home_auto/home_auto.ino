/*
  RF_Sniffer

  Hacked from http://code.google.com/p/rc-switch/

  by @justy to provide a handy RF code sniffer
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <dht11.h>



#include "RCSwitch.h"
#include <stdlib.h>
#include <stdio.h>
RCSwitch mySwitch = RCSwitch();
#define LAMP 9
#define FAN 8
#define DHT11PIN A3
#define PIRPIN 7
#define SPKR 6
LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 20 chars and 4 line display
dht11 DHT11;


void setup() {
  mySwitch.enableReceive(0);  // Receiver on inerrupt 0 =&gt; that is pin #2
  pinMode(LAMP, OUTPUT);
  pinMode(FAN, OUTPUT);
  digitalWrite(FAN, LOW);
  digitalWrite(LAMP, LOW);
  pinMode(DHT11PIN, INPUT);
  pinMode(PIRPIN, INPUT);
  delay(300);
  Wire.begin();
  delay(300);
  lcd.init();
  delay(400);
  char msg[] = "LCD On";
  lcdPrint(msg, sizeof(msg) / sizeof(msg[0]));
  //lcd.backlight();
  delay(700);
  lcd.setCursor(0, 1);
  lcd.print(8);
  lcd.print(9);
  lcd.setCursor(0, 1);
  delay(400);
  Serial.begin(9600);
  Serial.println("test message");
}

void loop() {

  int val = digitalRead(PIRPIN);

  lcd.setCursor(4, 1);
  
  if(val == HIGH)
  {
    char msg[] = "##Motion On##";
    lcdPrint(msg, sizeof(msg) / sizeof(msg[0]));    
  }
  else
  {
    char msg[] = "  Motion Off ";
    lcdPrint(msg, sizeof(msg) / sizeof(msg[0]));  
  }

  lcd.setCursor(0, 0);

  if (mySwitch.available()) {
    int value = mySwitch.getReceivedValue();
    Serial.println(value);
    if (value == 0) {

    } else {
      if (mySwitch.getReceivedValue() == 400)
      {
        digitalWrite(LAMP, HIGH);
        char msg[] = "Lamp Off";
        lcdPrint(msg, sizeof(msg) / sizeof(msg[0]));
      }
      else if (mySwitch.getReceivedValue() == 500)
      {
        digitalWrite(LAMP, LOW);
        char msg[] = "Lamp On ";
        lcdPrint(msg, sizeof(msg) / sizeof(msg[0]));
      }
      else if (mySwitch.getReceivedValue() == 600)
      {
        char msg[] = "Fan On ";
        digitalWrite(FAN, HIGH);
        lcdPrint(msg, sizeof(msg) / sizeof(msg[0]));
      }
      else if (mySwitch.getReceivedValue() == 700)
      {
        char msg[] = "Fan Off";
        digitalWrite(FAN, LOW);
        lcdPrint(msg, sizeof(msg) / sizeof(msg[0]));
      }
      else if(mySwitch.getReceivedValue() == 1000)
      {
        tone();
      }
    }

    mySwitch.resetAvailable();
  }

  delay(500);
  displayTemp();
}

void tone()
{
  int count = 0;
  
  while(count < 5)
  {
    tone(SPKR, 3000); // Send 1KHz sound signal...
    delay(200);        // ...for 1 sec
    noTone(SPKR);     // Stop sound...
    delay(200);        // ...for 1sec
    count++;
  }
}

void displayTemp()
{
  lcd.setCursor(0, 1);
  int chk = DHT11.read(DHT11PIN);
  int temp = DHT11.temperature;
  int humid = DHT11.humidity;
  lcd.print(temp);
  int unit = temp - ((temp / 10) * 10);
  lcd.print(unit);
  lcd.setCursor(0, 0);
}

void lcdPrint(char ar[], int len)
{
  for (int i = 0; i < len - 1; i++)
    lcd.print(ar[i]);
}
