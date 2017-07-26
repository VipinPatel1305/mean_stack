
#include "SSD1306_minimal.h"


SSD1306_Mini oled;

void setup() {
  pinMode(3, INPUT);

  oled.init(0x3c);
  oled.clear();
  oled.cursorTo(0, 0);
  oled.printString("*****Vips****");
  delay(5000);
}

int flagStar = 0;

void loop() {
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


  {

    int bData = 0;
    int arindx = 0;
    //if (bData == 35 || bData == 38 || bData == 41)
    if(0)
    {
      oled.cursorTo(0, bData - 34);
      oled.printString(ar);
    }
  }
  delay(100);
}


