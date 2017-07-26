//#include <SoftwareSerial.h>
#include <Wire.h>
#include "SSD1306_minimal.h"
#define DEG "\xa7" "C"
SSD1306_Mini oled;


//#define TXPIN 11
//#define RXPIN 10
//SoftwareSerial Genotronex(TXPIN, RXPIN);  //Tx_bluetooth Rx_bluetooth

char timeMsg[12];

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
  char msg[300];
  int indx = 0;
  bool readSuccess = false;

  manageTime();

  if (Serial.available())
  {

    int bData = Serial.read();
    while (bData != -1 && indx < 300)
    {
      msg[indx] = char(bData);
      bData = Serial.read();
      indx++;
    }
    msg[indx] = '\0';

    if (msg[0] == '#' && msg[indx - 1] == ']')
    {
      memcpy(timeMsg, msg, indx);
      timeMsg[9] = '\0';
      readSuccess = true;
    }

    if (msg[0] == '&' && msg[indx - 1] == ']')
    {
      oled.cursorTo(0, 4);
      oled.printString(msg);
      readSuccess = true;
    }

    if (msg[0] == ')' && msg[indx - 1] == ']')
    {
      oled.cursorTo(0, 7);
      oled.printString(msg);
      readSuccess = true;
    }
    memset(msg, '\0', 300);

    if (readSuccess == true)
    {
      Serial.write("1");
    }
    else
    {
      Serial.write("0");
    }
  }

  oled.cursorTo(0, 2);
  oled.printString(timeMsg);
  delay(1000);
}

void manageTime()
{
  //"& 2 0 : 2 3 : 5 4 ]"
  // 0 1 2 3 4 5 6 7 8 9
  if (timeMsg[8] < '9')
    timeMsg[8]++;
  else
  {
    timeMsg[8] = '0';

    if (timeMsg[7] < '5')
      timeMsg[7]++;
    else
    {
      timeMsg[7] = '0';
      if (timeMsg[5] < '9')
        timeMsg[5]++;
      else
      {
        timeMsg[5] = '0';

        if (timeMsg[4] < '5')
          timeMsg[4]++;
        else
        {
          timeMsg[4] = '0';

          if (timeMsg[2] < '9')
            timeMsg[2]++;
          else
          {
            timeMsg[2] = '0';

            if (timeMsg[1] < '2')
            {
              timeMsg[1]++;
            }
            else
            {
              timeMsg[1] = '0';
            }
          }
        }
      }
    }
  }
}


