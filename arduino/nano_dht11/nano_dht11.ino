
#include "ssd1306.h"
#include <dht11.h>
#include <avr/pgmspace.h>
dht11 DHT11;
SSD1306 oled;

#define DHT11PIN A3
#define LM_PREC A3

void setup(void)
{
  pinMode(DHT11PIN, INPUT);
  delay(2000);
  TinyWireM.begin();
  delay(2000);
  oled.begin();
  oled.fill(0x00); // clear in black
  oled.print_digits(1, 0, 1, 10, 99, false);
  oled.print_digits(0, 1, 3, 10, 99, false);
  delay(3000);
}

void displayTemp()
{
  float temp;
  //dicard first value
  int reading = analogRead(LM_PREC);
  reading = 0;

  for (int i = 0; i < 10; i++)
  {
    reading += analogRead(LM_PREC);
    delay(40);
  }

  reading = reading / 10;
  float mv = (reading / 1024.0) * 5000;
  int cel = mv / 10;
  oled.print_digits(0, 1, 3, 10, cel, false);
}
void displayTempDHT()
{
  int chk = DHT11.read(DHT11PIN);
  int tem = DHT11.temperature;
  int hum = DHT11.humidity;

  oled.print_digits(1, 0, 1, 10, hum, false);
  oled.print_digits(0, 1, 3, 10, tem, false);
}

void loop()
{
  displayTemp();
  delay(1000);
}

