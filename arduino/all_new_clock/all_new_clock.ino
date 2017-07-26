#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "RTClib.h"

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 20 chars and 4 line display
RTC_DS3231 rtc;
char currTime[8];
#define SPKR 11
#define LM_PREC 0
int irPin = 9; //Sensor pin connect to digital pin2 (ATINY85 pin7)
int start_bit = 2200; //Start bit threshold (Microseconds)
int bin_1 = 1000; //Binary 1 threshold (Microseconds)
int bin_0 = 400; //Binary 0 threshold (Microseconds)
const byte BIT_PER_BLOCK = 32;

int x = 0;
int prevMinUp = -1;
int flagDot = 0;
int alarmMins = 0;
int backLightState = 1;
char formatted[5];
int timeCounter = 0;

int temp1, temp2;

typedef void (* DigitFuncPtr) ();
extern DigitFuncPtr numeral[10];
extern void beepAlarm();
extern int getIRKey();

void irdecode()
{
  int key = getIRKey();

  if (key != 0)
  {
    switch (key)
    {
      case 2:
        {
          if (backLightState == 1)
          {
            backLightState = 0;
            lcd.noBacklight();
          }
          else
          {
            backLightState = 1;
            lcd.backlight();
          }
          break;
        }

      case 7:
        {
          setTime(1, 0);
          updateTimeLcd();
          break;
        }

      case 11:
        {
          setTime(2, 0);
          updateTimeLcd();
          break;
        }

      case 18:
        {
          setTime(0, 1);
          updateTimeLcd();
          break;
        }

      case 16:
        {
          setTime(0, 2);
          updateTimeLcd();
          break;
        }

      case 45:
        {
          alarmMins = 0;
          break;
        }

      case 96:
      case 192:
        {
          alarmMins += 10;
          displayAlarm();
          break;
        }

      case 97:
      case 194:
        {
          alarmMins -= 10;
          displayAlarm();
          break;
        }

      case 98:
      case 196:
        {
          alarmMins += 1;
          displayAlarm();
          break;
        }

      case 101:
      case 202:
        {
          alarmMins -= 1;
          displayAlarm();
          break;
        }

      case 31:
        {
          beepAlarm();
          break;
        }
    }
  }
}

void updateTimeLcd()
{
  refreshLcd();
  getTime();
}

void displayAlarm()
{
  lcd.setCursor(13, 1);
  int tim1 = alarmMins / 100;
  lcd.print(tim1);
  int tim2 = alarmMins - tim1 * 100;
  lcd.print(tim2 / 10);
  int tim3 = tim2 - (tim2 / 10) * 10;
  lcd.print(tim3);
}

void loop()
{
  irdecode();

  if (timeCounter % 50 == 0)
  {
    getTime();
  }

  char curMin = currTime[4];

  if (prevMinUp != curMin)
  {
    refreshLcd();
    prevMinUp = curMin;

    if (alarmMins > 0)
    {
      reduceAlarm();
    }
  }

  if (timeCounter % 100 == 0)
  {
    displayTemp(1);
  }

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

  lcd.setCursor(x, 0);
  if (flagDot == 0)
  {
    lcd.write(255);
  }
  else
  {
    lcd.print(" ");
  }

  timeCounter++;

  if (timeCounter == 101)
  {
    timeCounter = 0;
  }

  delay(300);
}


void getTime()
{

  DateTime now = rtc.now();
  byte hours = now.hour();
  byte minutes = now.minute();
  byte dayofWeek = now.dayOfTheWeek();
  byte dates = now.day();

  int tensh = hours / 10;
  int unith = hours - ((hours / 10) * 10);
  int tensm = minutes / 10;
  int unitm = minutes - ((minutes / 10) * 10);
  int datet = dates / 10;
  int dateu = dates - ((dates / 10) * 10);

  currTime[0] =  tensh + 48;
  currTime[1] =  unith + 48;
  currTime[2] = ':';
  currTime[3] =  tensm + 48;
  currTime[4] =  unitm + 48;
  currTime[5] = dayofWeek + 48;
  currTime[6] = datet + 48;
  currTime[7] = dateu + 48;
}


void lcdTime()
{
  lcd.setCursor(0, 0);
  x = 0;
  numeral[currTime[0] % 48]();
  x = x + 3;
  numeral[currTime[1] % 48]();
  x = x + 3;

  lcd.setCursor(x, 1);
  lcd.write(255);

  x = x + 1;
  numeral[currTime[3] % 48]();
  x = x + 3;
  numeral[currTime[4] % 48]();
  displayDayMonth();
}

void displayDayMonth()
{
  char dayOW = '-';
  char dayOW2 = '-';
  switch (currTime[5])
  {
    case '0':
      {
        dayOW = 'S';
        dayOW2 = 'U';
        break;
      }
    case '1':
      {
        dayOW = 'M';
        dayOW2 = 'O';
        break;
      }
    case '2':
      {
        dayOW = 'T';
        dayOW2 = 'U';        
        break;
      }
    case '3':
      {
        dayOW = 'W';
        dayOW2 = 'E';
        break;
      }
    case '4':
      {
        dayOW = 'T';
        dayOW2 = 'H';
        break;
      }
    case '5':
      {
        dayOW = 'F';
        dayOW2 = 'R';
        break;
      }
    case '6':
      {
        dayOW = 'S';
        dayOW2 = 'A';
        break;
      }
  }

  lcd.setCursor(13, 0);
  lcd.print(dayOW);
  lcd.setCursor(13, 1);
  lcd.print(dayOW2);
  
  lcd.setCursor(14, 1);
  lcd.print(currTime[6]);
  lcd.print(currTime[7]);
}


void displayTemp(int flagCompute)
{

  if (flagCompute == 1)
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
    cel = cel - 6;
    temp1 = cel / 10;
    temp2 = cel - temp1 * 10;
  }

  lcd.setCursor(14, 0);
  lcd.print(temp1);
  lcd.print(temp2);
}


void refreshLcd()
{
  lcd.clear();
  displayTemp(0);
  lcdTime();
}



void reduceAlarm()
{
  alarmMins -= 1;
  displayAlarm();

  if (alarmMins <= 0)
  {
    alarmMins = 0;
    displayAlarm();
    beepAlarm();
    getTime();
    lcdTime();
  }
}

void lcdPrint(char ar[], int len)
{
  for (int i = 0; i < len; i++)
    lcd.print(ar[i]);
}



void setTime(int setHr, int setMins)
{
  DateTime now = rtc.now();
  DateTime future;
  
  if (setMins == 1)
  {
    future = DateTime(now + TimeSpan(0, 0, 1, 0));
  }
  else if (setMins == 2)
  {
    future = DateTime(now - TimeSpan(0, 0, 1, 0));
  }
  else if (setHr == 1)
  {
    future = DateTime(now + TimeSpan(0, 1, 0, 0));
  }
  else if (setHr == 2)
  {
    future = DateTime(now - TimeSpan(0, 1, 0, 0));
  }
  rtc.adjust(future);
}


