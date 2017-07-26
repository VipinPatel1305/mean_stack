#include <SoftwareSerial.h>
#include <Wire.h>
#include "SSD1306_minimal.h"

SSD1306_Mini oled;


#define TXPIN 11
#define RXPIN 10
SoftwareSerial bleConn(TXPIN, RXPIN);  //Tx_bluetooth Rx_bluetooth

char timeMsg[12];

void setup(void)
{
  Serial.begin(9600);
  delay(1000);
  bleConn.begin(9600);
  delay(1000);
  Wire.begin();
  oled.init(0x3c);
  oled.clear();
  delay(3000);
}

void loop()
{
  char msg[300];
  int indx = 0;
  int readSuccess = 0;

  manageTime();

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
    Serial.println(msg);
    readSuccess = msgIntrpt(msg, indx);
    memset(msg, '\0', 300);

    if (readSuccess == 1)
    {
      bleConn.write("1");
      Serial.println("success");
    }
    else
    {
      bleConn.write("0");
      Serial.println("fail");
    }
  }

  oled.cursorTo(0, 0);
  oled.printString(timeMsg);
  delay(1000);  
}

void loop1()
{
  char msg[300];
  int indx = 0;
  int readSuccess = 0;

  manageTime();

  if (Serial.available())
  {
    int bData = Serial.read();
    while (bData != -1)
    {
      if (indx < 300)
        msg[indx] = char(bData);

      bData = Serial.read();
      indx++;
    }

    readSuccess = msgIntrpt(msg, indx);
    memset(msg, '\0', 300);

    if (readSuccess == 1)
    {
      Serial.write("1");
      //Serial.println("success");
    }
    else
    {
      Serial.write("0");
      //Serial.println("fail");
    }
  }

  oled.cursorTo(0, 0);
  oled.printString(timeMsg);
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
          memcpy(timeMsg, &msg[st + 1], sizeof(char) * (en - st - 1));
          timeMsg[en - st] = '\0';
          break;
        }

      case '&':
      case ')':
        {
          char customMsg[300];
          memcpy(customMsg, &msg[st + 1], sizeof(char) * (en - st - 1));
          customMsg[en - st] = '\0';
          Serial.println("phone call");
          oled.cursorTo(0, cursorIn);
          oled.printString(customMsg);
          break;
        }
    }
  }

  return ret;
}

void manageTime()
{
  //"& 2 0 : 2 3 : 5 4 ]"
  // 0 1 2 3 4 5 6 7 8 9
  if (timeMsg[7] < '9')
    timeMsg[7]++;
  else
  {
    timeMsg[7] = '0';

    if (timeMsg[6] < '5')
      timeMsg[6]++;
    else
    {
      timeMsg[6] = '0';
      if (timeMsg[4] < '9')
        timeMsg[4]++;
      else
      {
        timeMsg[4] = '0';

        if (timeMsg[3] < '5')
          timeMsg[3]++;
        else
        {
          timeMsg[3] = '0';

          if (timeMsg[1] < '9')
            timeMsg[1]++;
          else
          {
            timeMsg[1] = '0';

            if (timeMsg[0] < '2')
            {
              timeMsg[0]++;
            }
            else
            {
              timeMsg[0] = '0';
            }
          }
        }
      }
    }
  }
}


