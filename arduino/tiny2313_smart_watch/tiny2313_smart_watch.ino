#include <SoftwareSerial.h>
#include <TinyWireM.h>
#include "SSD1306_minimal.h"

#define DEG "\xa7" "C"

SSD1306_Mini oled;
#define RX PD0
#define TX PD1
SoftwareSerial Genotronex(RX, TX); //Tx_bluetooth Rx_bluetooth


void setup() {
  Genotronex.begin(9600);
  delay(3000);

  TinyWireM.begin();  
  oled.init(0x3c);
  oled.clear();
  oled.cursorTo(0, 0);
  oled.printString("*****Vips1****");
  delay(3000);
}

int flagStar = 0;

void loop()
{
  char ar[300];
  oled.cursorTo(0, 0);
  
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

  if (Genotronex.available())
  {
    int bData = Genotronex.read();
    //int bData = 0;
    int arindx = 0;

    if (bData == 35 || bData == 38 || bData == 41)
    {
      oled.cursorTo(0, bData - 34);


      while (bData != 93 && bData != -1)
      {
        ar[arindx] = char(bData);
        bData = Genotronex.read();
        arindx++;
      }

      ar[arindx] = '\0';
      oled.printString(ar);
    }
  }
     for(int i = 0; i < 10; i++)
  {
    digitalWrite(3, HIGH);
    delay(200);
    digitalWrite(3, LOW);
    delay(200);
  }
  delay(100);
}


