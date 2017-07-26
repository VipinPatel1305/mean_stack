#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 20 chars and 4 line display

void setup()
{
  Wire.begin();
  lcd.init();
  //lcd.backlight();
  //  lcd.print("BHello, world!");
  char ar[] = {'t', 'h', 'i', 's', 'k'};
  Serial.begin(9600);
  printMyStr(ar);
}

void loop()
{

}


void printMyStr(char ar1[])
{
  int size1 = sizeof(ar1) / sizeof(ar1[0]);
  for (int i = 0; i < size1 - 1; i++)
    lcd.print(ar1[i]);
}

