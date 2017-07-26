
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27, 16, 2);

char formatted[5];
int x = 0;
int flagDot = 0;

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

typedef void (* DigitFuncPtr) ();
DigitFuncPtr numeral[10] = {zero,one,two,three,four,five,six,seven,eight,nine};



void setup()
{
 Wire.begin();                    // initialize I2C lib

  lcd.init();                           // initialize the lcd
  lcd.backlight();
  lcd.clear();  // Print a message to the LCD.

  lcd.createChar(8, LT);
  lcd.createChar(1, UB);
  lcd.createChar(2, RT);
  lcd.createChar(3, LL);
  lcd.createChar(4, LB);
  lcd.createChar(5, LR);
  lcd.createChar(6, UMB);
  lcd.createChar(7, LMB);
  
  Serial.begin(9600);
}





void loop()
{
  
  char *displayTime = formatted;
  lcdTime();
  x = 6;
  lcd.setCursor(x, 1);
  if (flagDot == 0)
  {
    flagDot = 1;
    lcd.write(255);
  }
  else
  {
    lcd.print(" ");
    flagDot = 0;
  }
  
  delay(1200);
}


void lcdTime()
{
  lcd.setCursor(0, 0);
  formatted[0] = '1';
  formatted[1] = '1';
  formatted[2] = '2';
  formatted[3] = '3';
  formatted[3] = '\0';
  char *displayTime = formatted;
  x = 0;
  numeral[displayTime[0] % 48]();
  x = x + 3;
  numeral[displayTime[1] % 48]();
  x = x + 3;
  
  lcd.setCursor(x, 1);
  lcd.write(255);
  
  x = x + 1;
  numeral[displayTime[2] % 48]();
  x = x + 3;
  numeral[displayTime[3] % 48]();
  Serial.println(displayTime);
}


