#include <Adafruit_GFX.h>    // Core graphics library
#include <MCUFRIEND_kbv.h>
#include <Wire.h>
#include <RealTimeClockDS1307.h>

#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

// GND              -- GND
// 3V3               -- 3.3V
// CS                 -- A3
// RS                 -- A2
// WR                -- A1
// RD                 -- A0
// RST                -- RESET
// LED                -- GND
// DB0                -- 8
// DB1                -- 9
// DB2                -- 10
// DB3                -- 11
// DB4                -- 4
// DB5                -- 13
// DB6                -- 6
// DB7                -- 7

MCUFRIEND_kbv tft;

char formatted[] = "00-00-00 00:00:00x";
char hrs[3], mins[3], dd[3], mm[3], yy[3];
int timeCall = 0;
char datePrint[] = "TUE 23 MAY";

#define DS1307_ADDR 0x68

void setup() {
  Serial.begin(9600);
  hrs[2] = '\0';
  mins[2] = '\0';
  dd[2] = '\0';
  mm[2] = '\0';
  yy[2] = '\0';
  
  delay(300);
  tft.reset();

  uint16_t identifier = tft.readID();
  tft.begin(identifier);
  tft.setRotation(3);  
  delay(500);
  
  displayTime();
}


void loop() {
  // put your main code here, to run repeatedly:
  delay(500);

  tft.setTextSize(15);
  tft.setCursor(152, 75);
  
  if (timeCall % 2 == 0)
  {
    tft.setTextColor(WHITE);
    tft.print(":");
  }
  else
  {
    tft.setTextColor(BLACK);
    tft.print(":");
  } 

  timeCall++;

  if(timeCall > 60)
  {
    displayTime();
    timeCall = 0;
  }
}



void displayTime()
{
  RTC.readClock();
  RTC.getFormatted(formatted);
  Serial.println(formatted);
  
  hrs[0] = formatted[9];
  hrs[1] = formatted[10];
  mins[0] = formatted[12];
  mins[1] = formatted[13];  
  datePrint[4] = formatted[6];
  datePrint[5] = formatted[7];

  tft.fillScreen(BLACK);
  tft.setCursor(0, 0);
  tft.setTextSize(5);
  tft.setTextColor(YELLOW);
  tft.print(datePrint);
  
  tft.setTextColor(WHITE); 
  tft.setCursor(0, 70);
  tft.setTextSize(16);
  tft.print(hrs);

  tft.setTextSize(15);
  tft.setCursor(152, 75);
  tft.print(" ");

  tft.setTextColor(WHITE); 
  tft.setCursor(205, 70);
  tft.setTextSize(16);
  tft.print(mins);
  
  tft.setTextColor(YELLOW); 
  tft.setCursor(0, 200);
  tft.setTextSize(4);
  tft.print("26`C");
}

void getDateP()
{
  int monthVal = RTC.getMonth();
  int weekDay = RTC.getDay();

  switch(monthVal)
  {
    case 1:
    {
      datePrint[7] = 'J';
      datePrint[8] = 'A';
      datePrint[9] = 'N';
      break;
    }
    case 2:
    {
      datePrint[7] = 'F';
      datePrint[8] = 'E';
      datePrint[9] = 'B';
      break;
    }
    case 3:
    {
      datePrint[7] = 'M';
      datePrint[8] = 'A';
      datePrint[9] = 'R';
      break;
    }
    case 4:
    {
      datePrint[7] = 'A';
      datePrint[8] = 'P';
      datePrint[9] = 'R';
      break;
    }
    case 5:
    {
      datePrint[7] = 'M';
      datePrint[8] = 'A';
      datePrint[9] = 'Y';
      break;
    }
    case 6:
    {
      datePrint[7] = 'J';
      datePrint[8] = 'U';
      datePrint[9] = 'N';
      break;
    }
    case 7:
    {
      datePrint[7] = 'J';
      datePrint[8] = 'U';
      datePrint[9] = 'L';
      break;
    }
    case 8:
    {
      datePrint[7] = 'A';
      datePrint[8] = 'U';
      datePrint[9] = 'G';
      break;
    }
    case 9:
    {
      datePrint[7] = 'S';
      datePrint[8] = 'E';
      datePrint[9] = 'P';
      break;
    }                            
    case 10:
    {
      datePrint[7] = 'O';
      datePrint[8] = 'C';
      datePrint[9] = 'T';
      break;
    }                            
    case 11:
    {
      datePrint[7] = 'N';
      datePrint[8] = 'O';
      datePrint[9] = 'V';
      break;
    }                            
    case 12:
    {
      datePrint[7] = 'D';
      datePrint[8] = 'E';
      datePrint[9] = 'C';
      break;
    }                                       
  }

  switch(weekDay)
  {
    case 0:
    {
      datePrint[0] = 'S';
      datePrint[1] = 'U';
      datePrint[2] = 'N';
      break;
    }
    case 1:
    {
      datePrint[0] = 'M';
      datePrint[1] = 'O';
      datePrint[2] = 'N';
      break;
    }
    case 2:
    {
      datePrint[0] = 'T';
      datePrint[1] = 'U';
      datePrint[2] = 'E';
      break;
    }
    case 3:
    {
      datePrint[0] = 'W';
      datePrint[1] = 'E';
      datePrint[2] = 'D';
      break;
    }
    case 4:
    {
      datePrint[0] = 'T';
      datePrint[1] = 'H';
      datePrint[2] = 'U';
      break;
    }
    case 5:
    {
      datePrint[0] = 'F';
      datePrint[1] = 'R';
      datePrint[2] = 'I';
      break;
    }
    case 6:
    {
      datePrint[0] = 'S';
      datePrint[1] = 'A';
      datePrint[2] = 'T';
      break;
    }                        
  }
}

