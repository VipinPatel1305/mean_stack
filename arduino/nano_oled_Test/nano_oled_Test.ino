/*********************************************************************
This is an example for our Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

This example is for a 128x64 size display using I2C to communicate
3 pins are required to interface (2 I2C and one reset)

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.  
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/

#include <SPI.h>
#include <Wire.h>
#include "DHT.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

#define  LM_PREC 0
#define DHTPIN 2

#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 

#define DHTTYPE DHT11
#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

DHT dht(DHTPIN, DHTTYPE);

void setup()   {                
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  // init done
  
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.clearDisplay();
  delay(2000);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("Sensor");
  display.display();
  delay(1000);
  dht.begin();
  //display.stopscroll();

}

void displaDht11()
{
  float h = dht.readHumidity();  
  float t = dht.readTemperature();
  display.setCursor(0,16);
  if (isnan(h) || isnan(t)) {
    display.print("Failed");
  }
  else
  {
    display.print(t);
  }
}

void displayTemp()
{
     float temp;
    //dicard first value
    int reading = analogRead(LM_PREC);
    reading = 0;
    
    for(int i = 0; i < 10; i++)
    {
      reading += analogRead(LM_PREC);
      delay(100);
    }

    float sum = reading;
    sum = sum/10.0;
    float mv = (sum / 1024.0) * 500;
    display.setCursor(0,0);
    display.print(mv); 
}

void loop() {
  display.clearDisplay();
  displayTemp();
  displaDht11();
  display.display();
  delay(5000);
}







