
#include "ssd1306.h"
#include <avr/pgmspace.h>

SSD1306 oled;

#define UV_PIN A3
#define LM_35 A2

void setup(void)
{
  pinMode(UV_PIN, INPUT);
  pinMode(LM_35, INPUT);

  delay(2000);
  TinyWireM.begin(); 
  oled.begin();
  oled.fill(0x00); // clear in black
  oled.print_digits(0, 0, 1, 10, 97, false);
  oled.print_digits(0, 1, 3, 10, 99, false);
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
    oled.print_digits(0, 1, 3, 100, uv, false);
}

void displayTemp()
{
    float temp;
    //dicard first value
    int reading = analogRead(LM_35);
    
    reading = 0;
    
    for(int i = 0; i < 10; i++)
    {
      reading += analogRead(LM_35);
      delay(40);
    }

    reading = reading/10;
    
    float mv = (reading / 1024.0) * 5000;  
    int imv = mv/10;
    oled.print_digits(0, 0, 1, 10, imv, false);
    /*
    float t = dht.readTemperature();
    int imv = t;
    oled.print_digits(0, 0, 1, 10, imv, false);
    
    float h = dht.readHumidity();
    int iHumidity = h;
    oled.print_digits(20, 0, 1, 10, iHumidity, false);
    */
}

void loop()
{
  displayUV();
  displayTemp();
  delay(5000);
}

