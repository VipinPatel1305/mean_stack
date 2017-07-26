#include <SoftwareSerial.h>
#include <TinyWireM.h>
#include "SSD1306_minimal.h"

#define TXPIN 3
#define RXPIN 4
SSD1306_Mini oled;
SoftwareSerial bleConn(TXPIN, RXPIN); //Tx_bluetooth Rx_bluetooth


void setup() {

  pinMode(TXPIN, INPUT);
  pinMode(RXPIN, OUTPUT);
  bleConn.begin(9600);
  delay(3000);
  
  TinyWireM.begin();
  oled.init(0x3c);
  oled.clear();
  oled.cursorTo(0, 0);
  oled.printString("*****Vips###****");
  delay(3000);


}

int flagStar = 0;

void loop()
{
  char msg[300];
  int indx = 0;
  int readSuccess = 0;


  if (bleConn.available())
  {
    int bData = bleConn.read();
    while (bData != -1)
    {
      if (indx < 300)
        msg[indx] = char(bData);

      bData = bleConn.read();
      indx++;
    }

    msg[indx] = '\0';
    readSuccess = msgIntrpt(msg, indx);
    memset(msg, '\0', 300);

    if (readSuccess == 1)
    {
      bleConn.write("1");
    }
    else
    {
      bleConn.write("0");
    }
  }

//  oled.cursorTo(0, 0);
//  oled.printString(timeMsg);
  delay(1000);  
}



int msgIntrpt(char msg[], int indx)
{
  int st = -1;
  int en = -1;
  int cursorIn = -1;
  int ret = 0;

  for (int i = 0; i < indx; i++)
  {
    if (msg[i] == '#')
    {
      st = i;
      cursorIn = 2;
    }

    if (msg[i] == '&')
    {
      st = i;
      cursorIn = 4;
    }


    if (msg[i] == ')')
    {
      st = i;
      cursorIn = 7;
    }

    if (msg[i] == ']' && st != -1)
    {
      en = i;
      ret = 1;
      break;
    }
  }

  //valid msg
  if (ret == 1)
  {
    switch (msg[st])
    {
      case '#':
        {
          //ignore start # and end ] marker
//          memcpy(timeMsg, &msg[st + 1], sizeof(char) * (en - st - 1));
//          timeMsg[en - st] = '\0';
          break;
        }

      case '&':
      case ')':
        {
          char customMsg[300];
          memcpy(customMsg, &msg[st + 1], sizeof(char) * (en - st - 1));
          customMsg[en - st] = '\0';
//          Serial.println("phone call");
          oled.cursorTo(0, cursorIn);
          oled.printString(customMsg);
          break;
        }
    }
  }

  return ret;
}
