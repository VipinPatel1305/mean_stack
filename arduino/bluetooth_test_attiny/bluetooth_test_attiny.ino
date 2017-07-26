#include <SoftwareSerial.h>
#include "SSD1306_minimal.h"
#include "TinyWireM.h"

#define DEG "\xa7" "C"

SSD1306_Mini oled;
SoftwareSerial Genotronex(3, 4); //Tx_bluetooth Rx_bluetooth


void setup(){
  //pinMode(3, INPUT);
  
  oled.init(0x3c);
  oled.clear();
  oled.cursorTo(0, 0);
  oled.printString("*****VipsR****");
  delay(3000);
  Genotronex.begin(9600);
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
 oled.cursorTo(0, 3);
 oled.printString("Test message1");

   if (Genotronex.available())
  {
    int bData = Genotronex.read();
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
  delay(100);
}


