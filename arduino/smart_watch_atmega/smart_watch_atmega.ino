//#define F_CPU 16000000UL
#include <SoftwareSerial.h>
#include <Wire.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include "SSD1306_minimal.h"

SSD1306_Mini oled;
#define TXPIN 6
#define RXPIN 7
SoftwareSerial Genotronex(TXPIN, RXPIN);


void setup() {
  Wire.begin();
  oled.init(0x3c);
  oled.clear();
  oled.cursorTo(0, 0);
  oled.printString("test Message");
  delay(300);

  Genotronex.begin(9600);
  delay(300);
  Serial.begin(9600);
}


void loop2()
{
  char msg[300];
  int indx = 0;

  if (Genotronex.available())
  {
    int bData = Genotronex.read();
    while (bData != -1 && indx < 300)
    {
      msg[indx] = char(bData);
      bData = Genotronex.read();
      indx++;
    }
    msg[indx] = '\0';
    {
      oled.cursorTo(0, 2);
      oled.printString(msg);
    }
  }
  delay(200);
}


void loop()
{
  char msg[300];
  int indx = 0;

  if (Genotronex.available())
  {
    int bData = Genotronex.read();
    while (bData != -1 && indx < 300)
    {
      msg[indx] = char(bData);
      bData = Genotronex.read();
      indx++;
    }
    msg[indx] = '\0';

    if (msg[0] == '#' && msg[indx - 1] == ']')
    {
      oled.cursorTo(0, 2);
      oled.printString(msg);
    }

    if (msg[0] == '&' && msg[indx - 1] == ']')
    {
      oled.cursorTo(0, 4);
      oled.printString(msg);
    }

    if (msg[0] == ')' && msg[indx - 1] == ']')
    {
      oled.cursorTo(0, 7);
      oled.printString(msg);
    }
    memset(msg, '\0', 300);
  }
  delay(200);
}


