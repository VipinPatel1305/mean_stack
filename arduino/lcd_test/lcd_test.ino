/*
A set of custom made large numbers for a 16x2 LCD using the 
 LiquidCrystal librabry. Works with displays compatible with the 
 Hitachi HD44780 driver. 
 
 The Cuicuit:
 LCD RS pin to D7
 LCD Enable pin to D6
 LCD D4 pin to D5
 LCD D5 pin to D4
 LCD D6 pin to D3
 LCD D7 pin to D2
 LCD Vee tied to a pot to control brightness
 LCD Vss and R/W tied to ground
 LCD Vcc to +5V
 LCD pin 15 tied to pushbutton for control of backlight
 
 Made by Michael Pilcher
 2/9/2010
 */

// include the library
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// initialize the interface pins
//LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
LiquidCrystal_I2C lcd(0x27, 16, 2);
int x = 0;

typedef void (* DigitFuncPtr) ();

void numbers();
// the 8 arrays that form each segment of the custom numbers
byte LT[8] = 
{
  B00111,
  B01111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};
byte UB[8] =
{
  B11111,
  B11111,
  B11111,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};
byte RT[8] =
{
  B11100,
  B11110,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};
byte LL[8] =
{
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B01111,
  B00111
};
byte LB[8] =
{
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111,
  B11111
};
byte LR[8] =
{
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11110,
  B11100
};
byte UMB[8] =
{
  B11111,
  B11111,
  B11111,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111
};
byte LMB[8] =
{
  B11111,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111,
  B11111
};



void setup()
{
  Wire.begin();                    // initialize I2C lib

  lcd.init();                           // initialize the lcd
  lcd.backlight();
  lcd.clear();  // Print a message to the LCD.
  // assignes each segment a write number
  lcd.createChar(8,LT);
  lcd.createChar(1,UB);
  lcd.createChar(2,RT);
  lcd.createChar(3,LL);
  lcd.createChar(4,LB);
  lcd.createChar(5,LR);
  lcd.createChar(6,UMB);
  lcd.createChar(7,LMB);

  // sets the LCD's rows and colums:
  //lcd.begin(0, 2);
  //numbers();
}

void zero()
{ // uses segments to build the number 0
  lcd.setCursor(x, 0); 
  lcd.write(8);  
  lcd.write(1); 
  lcd.write(2);
  lcd.setCursor(x, 1); 
  lcd.write(3);  
  lcd.write(4);  
  lcd.write(5);
}

void one()
{
  lcd.setCursor(x,0);
  lcd.write(1);
  lcd.write(2);
  lcd.setCursor(x,1);
  lcd.write(4);  
  lcd.write(255);
  lcd.write(4);  
}

void two()
{
  lcd.setCursor(x,0);
  lcd.write(6);
  lcd.write(6);
  lcd.write(2);
  lcd.setCursor(x, 1);
  lcd.write(3);
  lcd.write(7);
  lcd.write(7);
}

void three()
{
  lcd.setCursor(x,0);
  lcd.write(6);
  lcd.write(6);
  lcd.write(2);
  lcd.setCursor(x, 1);
  lcd.write(7);
  lcd.write(7);
  lcd.write(5); 
}

void four()
{
  lcd.setCursor(x,0);
  lcd.write(3);
  lcd.write(4);
  lcd.write(2);
  lcd.setCursor(x+2, 1);
  lcd.write(255);
}

void five()
{
  lcd.setCursor(x,0);
  lcd.write(255);
  lcd.write(6);
  lcd.write(6);
  lcd.setCursor(x, 1);
  lcd.write(7);
  lcd.write(7);
  lcd.write(5);
}

void six()
{
  lcd.setCursor(x,0);
  lcd.write(8);
  lcd.write(6);
  lcd.write(6);
  lcd.setCursor(x, 1);
  lcd.write(3);
  lcd.write(7);
  lcd.write(5);
}

void seven()
{
  lcd.setCursor(x,0);
  lcd.write(1);
  lcd.write(1);
  lcd.write(2);
  lcd.setCursor(x+1, 1);
  lcd.write(8);
}

void eight()
{
  lcd.setCursor(x,0);
  lcd.write(8);
  lcd.write(6);
  lcd.write(2);
  lcd.setCursor(x, 1);
  lcd.write(3);
  lcd.write(7);
  lcd.write(5);
}

void nine()
{
  lcd.setCursor(x,0);
  lcd.write(8);
  lcd.write(6);
  lcd.write(2);
  lcd.setCursor(x+2, 1);
  lcd.write(255);
}

DigitFuncPtr numeral[10] = {zero,one,two,three,four,five,six,seven,eight,nine};

void numbers()
{
  /*
  custom0O();    // displays custom 0 on the LCD
  x = x + 4;    // sifts cursor over 4 columns
  custom1();
  x = x + 4;
  custom0O();
  x = x + 4;
  custom1();
  x = x + 4;
  custom4();
  x = x + 4;
  custom5();
  x = x + 4;
  custom6();
  x = x + 4;
  custom7();
  x = x + 4;
  custom8();
  x = x + 4;
  custom9();*/
  delay(500);
}

int flag = 0;

void loop()
{
  /*
  numeral[8]();
  x = x + 3;
  numeral[9]();
  x = x + 3;
  lcd.setCursor(x,0);
  x = x + 1;
  if(flag == 0)
  {
    lcd.write(255);
    flag = 1;
  }
  else
  {
    flag = 0;
    lcd.print(" ");
    //lcd.write(0);
  }
   numeral[6]();
  x = x + 3;
   numeral[7]();
  x = x + 3;
  delay(500);
  x = 0;*/
  lcd.setCursor(0,0);
  lcd.print(5);
  lcd.print(3);
  delay(1000);
/*
  lcd.clear();
  delay(500);
  numbers();
  x = 0;
  lcd.clear();
  delay(500);*/
}




