
#include "ssd1306.h"
#include <dht11.h>
#include <avr/pgmspace.h>
dht11 DHT11;
SSD1306 oled;

#define UV_PIN A2
#define DHT11PIN A3

void setup(void)
{
  pinMode(UV_PIN, INPUT);
  pinMode(DHT11PIN, INPUT);
  delay(2000);
  TinyWireM.begin(); 
  delay(2000);
  oled.begin();
  oled.fill(0x00); // clear in black
  oled.print_digits(0, 0, 1, 10, 88, false);
  //oled.print_digits(20, 0, 1, 10, 88, false);
  oled.print_digits(0, 1, 3, 10, 88, false);
  delay(3000);
}

void displayUV()
{
   uint16_t uv = analogRead(UV_PIN);
   uv = 0;
   
   for(int i = 0; i < 10; i++)
   {
     uv += analogRead(UV_PIN);
     delay(40);
   }

    uv = uv/10;
    oled.print_digits(1, 0, 1, 100, 124, false);
    //oled.print_digits(0, 1, 3, 100, uv, false); //orig
}

void displayTemp()
{
  int chk = DHT11.read(DHT11PIN);
  int tem = DHT11.temperature;
  int iHumidity = DHT11.humidity;

   uint16_t uv = analogRead(UV_PIN);
   uv = 0;
   
   for(int i = 0; i < 10; i++)
   {
     uv += analogRead(UV_PIN);
     delay(40);
   }

  uv = uv/10;
         
  oled.print_digits(1, 0, 1, 100, uv, false);
  oled.print_digits(0, 1, 3, 10, tem, false);
}

void loop()
{
  displayTemp();
  delay(1000);
}

