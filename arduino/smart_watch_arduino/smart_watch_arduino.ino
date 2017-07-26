
#include <SoftwareSerial.h>
#include <Wire.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include "SSD1306_minimal.h"

#define DEG "\xa7" "C"
#define TX 1
#define RX 0
SSD1306_Mini oled;
SoftwareSerial blue(RX, TX); //Tx_bluetooth Rx_bluetooth


void setup() {
  
  pinMode(RX, INPUT);
  pinMode(TX, OUTPUT);
  Serial.begin(9600);
  blue.begin(9600);
  delay(3000);
  
  Wire.begin();
  oled.init(0x3c);
  oled.clear();
  oled.cursorTo(0, 0);
  oled.printString("*****Vips###****");
  delay(3000);
}

int flagStar = 0;

void loop()
{
  char ar[300];
  oled.cursorTo(0, 4);

  if (flagStar == 0)
  {
    oled.printString("* * * * * * * * *");
    flagStar = 1;
  }
  else
  {
    oled.printString(" * * * * * * * * ");
    flagStar = 0;
  }

  if (Serial.available())
  {
    int bData = Serial.read();
    int arindx = 0;
    oled.cursorTo(0, 6);

    while (bData != -1)
    {
      ar[arindx] = char(bData);
      bData = Serial.read();
      arindx++;
    }

    ar[arindx] = '\0';
    oled.printString(ar);  
  }
  delay(100);
}


