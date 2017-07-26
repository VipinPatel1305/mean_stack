#include <SoftSerial.h>
#include "SSD1306_minimal.h"
SSD1306_Mini oled;

/*
//#define TXPIN 2 connected to RX of bluetooth 
//#define TXPIN 1 connected to TX of bluetooth
#define TXPIN 2 
#define RXPIN 1
#define LEDPIN 0
#define LEDPIN1 3
*/

#define TXPIN 3
#define RXPIN 1
#define LEDPIN 4
#define LEDPIN1 4

SoftSerial blueSerial(RXPIN, TXPIN);  //Rx_bluetooth Tx_bluetooth


void setup() {
  // put your setup code here, to run once:
  pinMode(TXPIN, OUTPUT);
  pinMode(RXPIN, INPUT);
  pinMode(LEDPIN, OUTPUT);
  //pinMode(LEDPIN1, OUTPUT);
    oled.init(0x3c);
    delay(4000);
  oled.clear();
  oled.cursorTo(0, 0);
  oled.printString("*****Vips###****");
  delay(3000);
  blueSerial.begin(9600);

        for(int i = 0; i < 2; i++)
        {
          delay(500);
          digitalWrite(LEDPIN, HIGH);
          delay(500);
          digitalWrite(LEDPIN, LOW);
        }          
}

void loop()
{
  char msg[300];
  int indx = 0;
  bool readSuccess = false;

    if (blueSerial.available())
  {

    int bData = blueSerial.read();
    while (bData != -1 && indx < 300)
    {
      msg[indx] = char(bData);
      bData = blueSerial.read();
      indx++;
    }
    msg[indx] = '\0';

    if (msg[0] == '#' && msg[indx - 1] == ']')
    {
      oled.cursorTo(0, 0);
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
  }
  delay(1000);
}

void led0()
{
          for(int i = 0; i < 10; i++)
        {
          delay(500);
          digitalWrite(LEDPIN, HIGH);
          delay(500);
          digitalWrite(LEDPIN, LOW);
        }
}


void led1()
{
          for(int i = 0; i < 10; i++)
        {
          delay(500);
          digitalWrite(LEDPIN1, HIGH);
          delay(500);
          digitalWrite(LEDPIN1, LOW);
        }
}

