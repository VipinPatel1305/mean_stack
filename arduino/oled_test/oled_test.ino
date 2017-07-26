
#include "SSD1306_minimal.h"
#include <avr/pgmspace.h>
SSD1306_Mini oled;


void setup(void)
{
  Serial.begin(9600);
  delay(300);
  Wire.begin();
  oled.init(0x3c);
  oled.clear();
  oled.cursorTo(0, 0);
  oled.printString("*****Vips###****");

  delay(3000);
}

void loop()
{
  oled.cursorTo(0, 4);
  oled.printString("54");

    oled.cursorTo(0, 7);
  oled.printString("97");
  delay(5000);
}

