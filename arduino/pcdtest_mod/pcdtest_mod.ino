/*********************************************************************
This is an example sketch for our Monochrome Nokia 5110 LCD Displays

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/338

These displays use SPI to communicate, 4 or 5 pins are required to
interface

Adafruit invests time and resources providing this open source code,
please support Adafruit and open-source hardware by purchasing
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <SoftwareSerial.h>
// Software SPI (slower updates, more flexible pin options):
// pin 7 - Serial clock out (SCLK)
// pin 6 - Serial data out (DIN)
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)
Adafruit_PCD8544 display = Adafruit_PCD8544(6, 5, 4, 3, 2);
#define TXPIN 7
#define RXPIN 8
SoftwareSerial Genotronex(RXPIN, TXPIN);  //Rx_bluetooth Tx_bluetooth
// Hardware SPI (faster, but must use certain hardware pins):
// SCK is LCD serial clock (SCLK) - this is pin 13 on Arduino Uno
// MOSI is LCD DIN - this is pin 11 on an Arduino Uno
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)
// Adafruit_PCD8544 display = Adafruit_PCD8544(5, 4, 3);
// Note with hardware SPI MISO and SS pins aren't used but will still be read
// and written to during SPI transfer.  Be careful sharing these pins!

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16

static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

void setup()   {
  Genotronex.begin(9600);

  display.begin();
  // init done

  // you can change the contrast around to adapt the display
  // for the best viewing!
  display.setContrast(60);
/*
  // text display tests
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(BLACK);
  display.setCursor(0,0);
  display.println("8888");
  display.setTextSize(1);
  display.setCursor(0,30);
  char msg[] = {'8', '8', ':', '8', '8', '\0'};
  display.println(msg);
  display.display();
  */
  delay(2000);

}

char timeMsg[12];


void loop()
{
  char msg[300];
  int indx = 0;
  bool readSuccess = false;
  display.clearDisplay();
  display.setTextSize(1);
  manageTime();

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
      memcpy(timeMsg, msg, indx);
      timeMsg[9] = '\0';
      readSuccess = true;
    }

    if (msg[0] == '&' && msg[indx - 1] == ']')
    {
      display.setCursor(0, 14);
      display.println(msg);
      readSuccess = true;
    }

    if (msg[0] == ')' && msg[indx - 1] == ']')
    {
      display.setCursor(0, 24);
      display.println(msg);
      readSuccess = true;
    }
    memset(msg, '\0', 300);

    if (readSuccess == true)
    {
      Genotronex.write("1");
    }
    else
    {
      Genotronex.write("0");
    }
  }

  display.setCursor(0, 0);  
  display.setTextSize(3);
  char tmsg[5];
  tmsg[0] = timeMsg[1];
  tmsg[1] = timeMsg[2];
  tmsg[2] = timeMsg[4];
  tmsg[3] = timeMsg[5];
  tmsg[4] = '\0';
  display.println(tmsg);
  display.display();
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






