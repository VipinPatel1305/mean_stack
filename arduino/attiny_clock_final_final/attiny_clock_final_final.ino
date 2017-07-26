
#include <TinyWireM.h> 
#include <LiquidCrystal_I2C.h>


int flagDot = 0;
char formatted[20];
int prevMin = 0;

#define RECV_PIN 4
#define LM_PREC 1
#define SPKR 3
#define DS1307_ADDR 0x68

int start_bit = 2200; //Start bit threshold (Microseconds)
int bin_1 = 1000; //Binary 1 threshold (Microseconds)
int bin_0 = 400; //Binary 0 threshold (Microseconds)
const byte BIT_PER_BLOCK = 32;

int alarmMode = 0;
int hr = 0, mm = 0, rp = 0;
LiquidCrystal_I2C lcd(0x27, 16, 2);
int preMins = 0;

//#define lcd Serial

void setup()
{
 TinyWireM.begin();                    // initialize I2C lib

  lcd.init();                           // initialize the lcd
  lcd.backlight();
  lcd.clear();  // Print a message to the LCD.

  pinMode(RECV_PIN, INPUT);
  pinMode(LM_PREC, INPUT);
  pinMode(SPKR, OUTPUT);
  displayDate();
}

int backLightState = 1;

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
          break;
        }

      case 11:
        {
          setTime(2, 0);
          break;
        }

      case 18:
        {
          setTime(0, 1);
          break;
        }

      case 16:
        {
          setTime(0, 2);
          break;
        }

      case 26:
        {
          alarmMode = 1;
          break;
        }

      case 45:
        {
          alarmMode = 0;
          hr = 0;
          mm = 0;
          displayDate();
          break;
        }

      case 96:
      case 192:
        {
          if (hr < 99)
            hr++;
          break;
        }

      case 97:
      case 194:
        {
          if (hr > 0)
            hr--;
          break;
        }

      case 98:
      case 196:
        {
          if (mm < 99)
            mm++;
          break;
        }

      case 101:
      case 202:
        {
          if (mm > 0)
            mm--;
          break;
        }

      case 88:
      case 176:
        {
          if (rp == 0)
            rp = 1;
          else
            rp = 0;
          break;
        }

      case 104:
      case 208:
        {
          //start timer
          alarmMode = 2;
          //Serial.print("Alarm Set");
          lcd.setCursor(0, 1);
          lcd.print("Alarm Set          ");
          delay(1000);
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



void displayAlarm()
{
  char alarm[17];

  lcd.setCursor(0, 1);

  if (hr < 10)
  {
    alarm[0] = 48;
    alarm[1] = 48 + hr;
  }
  else
  {
    alarm[1] = 48 + hr % 10;
    int hr1 = hr / 10;
    alarm[0] = 48 + hr1;
  }

  alarm[2] = ':';

  if (mm < 10)
  {
    alarm[3] = 48;
    alarm[4] = 48 + mm;
  }
  else
  {
    alarm[4] = 48 + mm % 10;
    int mm1 = mm / 10;
    alarm[3] = 48 + mm1;
  }

  alarm[5] = ' ';
  alarm[6] = ' ';

  alarm[7] = 'R';
  alarm[8] = 'e';
  alarm[9] = 'p';
  alarm[10] = 'e';
  alarm[11] = 'a';
  alarm[12] = 't';
  alarm[13] = ' ';
  alarm[14] = 'O';

  if (rp == 1)
  {
    alarm[15] = 'n';
  }
  else
  {
    alarm[15] = 'f';
  }

  alarm[16] = '\0';
  lcd.print(alarm);
}

void beepAlarm()
{
  int i = 15;

  while (i > 0)
  {
    int key = getIRKey();
    if (key != 0)
    {
      break;
    }
    analogWrite(SPKR, 20);      // Almost any value can be used except 0 and 255
    // experiment to get the best tone
    delay(250);          // wait for a delayms ms
    digitalWrite(SPKR, 0);       // 0 turns it off
    delay(250);
    i--;
  }

}


void reduceAlarm(int dif)
{
  if (mm > 0)
  {
    mm = mm - dif;
  }

  if (mm <= 0)
  {
    if (hr > 0)
    {
      hr--;
      mm = 60;
    }
    else
    {
      //alarm over
      alarmMode = 0;
      mm = 0;
      hr = 0;
      //Serial.print("Alarm Over");
      displayDate();
      //beep alarm
    }
  }
}
//========================//
void loop()
{
  irdecode();
  lcd.setCursor(0, 0);          // set cursor to column 0, row 0 (the first row)
  //RTC.readClock();
  //RTC.getFormatted(formatted);
  getTime(formatted);
  char *displayTime = formatted;

  int curMinute = 0;
  displayTime += 9;



  if (flagDot == 1)
  {
    flagDot = 0;
    displayTime[2] = ':';
    displayTime[5] = ':';
  }
  else
  {
    flagDot++;
    displayTime[2] = ' ';
    displayTime[5] = ' ';
  }

  lcd.print(displayTime);    // change this text to whatever you like. keep it clean.
  lcd.print(" ");
  int val = analogRead(LM_PREC);
  float mv = (val / 1024.0) * 5000;
  int cel = mv / 10;
  lcd.print(cel);
  lcd.print("`C");


  curMinute = displayTime[4] - 48;
  curMinute = curMinute + (displayTime[3] - 48) * 10;

  int difMinute = curMinute - prevMin;
  //Serial.print(prevMin);

  if (difMinute > 0)
  {
    prevMin = curMinute;
  }

  if (alarmMode != 0)
  {
    displayAlarm();

    if (difMinute > 0 && alarmMode == 2)
    {
      reduceAlarm(difMinute);
    }
  }
}

int getIRKey() {
  int data[BIT_PER_BLOCK];
  int i;

  //while(pulseIn(RECV_PIN, HIGH) < start_bit);
  if (pulseIn(RECV_PIN, HIGH) < start_bit) //Wait for a start bit
    return 0;

  for (i = 0 ; i < BIT_PER_BLOCK ; i++)
    data[i] = pulseIn(RECV_PIN, HIGH); //Start measuring bits, I only want HIGH pulses

  delay(100);
  for (i = 0 ; i < BIT_PER_BLOCK ; i++) //Parse them
  {
    if (data[i] > bin_1) //is it a 1?
      data[i] = 1;
    else if (data[i] > bin_0) //is it a 0?
      data[i] = 0;
    else
      return -1; //Flag the data as invalid; Return -1 on invalid data
  }
  //based on NEC protocol, command data started from bit 16
  //and end with bit 24 (8 bits long)
  int result = 0;
  for (i = 16 ; i < 24; i++) {
    //DigiKeyboard.print(data[i]); //print out the value of button in binary form
    if (data[i] == 1) result |= (1 << i - 16); //Convert data bits to integer
  }
  return result; //Return key number
}

void displayDate()
{
  //RTC.readClock();
  //RTC.getFormatted(formatted);
  getTime(formatted);
  char *displayTime = formatted;
  prevMin = displayTime[13] - 48;
  prevMin = prevMin + (displayTime[12] - 48) * 10;

  char yr[4], mm[3], dd[3];
  yr[0] = displayTime[0];
  yr[1] = displayTime[1];
  yr[2] = '#';
  yr[3] = '\0';
  mm[0] = displayTime[3];
  mm[1] = displayTime[4];
  mm[2] = '\0';
  dd[0] = displayTime[6];
  dd[1] = displayTime[7];
  dd[2] = '\0';
  lcd.setCursor(0, 1);

  switch ((displayTime[18]))
  {
    case 1:
      {
        lcd.print("Mon");
        break;
      }
    case 2:
      {
        lcd.print("Tue");
        break;
      }

    case 3:
      {
        lcd.print("Wed");
        break;
      }

    case 4:
      {
        lcd.print("Thu");
        break;
      }

    case 5:
      {
        lcd.print("Fri");
        break;
      }

    case 6:
      {
        lcd.print("Sat");
        break;
      }

    case 7:
      {
        lcd.print("Sun");
        break;
      }
  }
  lcd.print(" ");
  lcd.print(dd);
  lcd.print(" ");

  if (mm[0] == '0')
  {
    switch (mm[1])
    {
      case '1':
        {
          lcd.print("Jan");
          break;
        }

      case '2':
        {
          lcd.print("Feb");
          break;
        }

      case '3':
        {
          lcd.print("Mar");
          break;
        }

      case '4':
        {
          lcd.print("Apr");
          break;
        }

      case '5':
        {
          lcd.print("May");
          break;
        }

      case '6':
        {
          lcd.print("Jun");
          break;
        }

      case '7':
        {
          lcd.print("Jul");
          break;
        }

      case '8':
        {
          lcd.print("Aug");
          break;
        }

      case '9':
        {
          lcd.print("Sep");
          break;
        }
    }
  }
  else
  {
    if (mm[1] == '0')
    {
      lcd.print("Oct");
    }
    else if (mm[1] == '1')
      lcd.print("Nov");
    else
      lcd.print("Dec");
  }

  lcd.print(" ");
  lcd.print("20");
  lcd.print(yr);
}


void getTime(char *formatted)
{
  char *displayTime = formatted;
  //displayTime += 9;
  //Serial
  TinyWireM.beginTransmission(DS1307_ADDR); // reset DS1307 register pointer
  TinyWireM.send((uint8_t) 0x00);
  TinyWireM.endTransmission();

  TinyWireM.requestFrom(DS1307_ADDR, 8);
  byte seconds = TinyWireM.receive();  // handle the 7 bytes received
  byte minutes = TinyWireM.receive();
  byte hours = TinyWireM.receive();
  byte dow1 = TinyWireM.receive();
  byte day = TinyWireM.receive();
  byte mm = TinyWireM.receive();
  byte yr = TinyWireM.receive();
  byte sqr = TinyWireM.receive();

  displayTime[0] =  (yr >> 4) + 48;
  displayTime[1] =  (yr & 0x0f) + 48;
  displayTime[2] = '-';
  displayTime[4] =  (mm & 0x0f) + 48;
  displayTime[3] =  (mm >> 4) + 48;
  displayTime[5] =  '-';
  displayTime[7] =  (day & 0x0f) + 48;
  displayTime[6] =  (day >> 4) + 48;
  displayTime[8] =  ' ';
  displayTime[9] =  (hours >> 4) + 48;
  displayTime[10] =  (hours & 0x0f) + 48;
  displayTime[11] = ':';
  displayTime[12] =  (minutes >> 4) + 48;
  displayTime[13] =  (minutes & 0x0f) + 48;
  displayTime[14] = ':';
  displayTime[15] =  (seconds >> 4) + 48;
  displayTime[16] =  (seconds & 0x0f) + 48;
  displayTime[17] = '\0';
  displayTime[18] = dow1;
}

void setTime(int setHr, int setMins)
{
  TinyWireM.beginTransmission(DS1307_ADDR); // reset DS1307 register pointer
  TinyWireM.send((uint8_t) 0x00);
  TinyWireM.endTransmission();

  TinyWireM.requestFrom(DS1307_ADDR, 8);
  byte seconds = TinyWireM.receive();  // handle the 7 bytes received
  byte minutes = TinyWireM.receive();
  byte hours = TinyWireM.receive();
  byte dow1 = TinyWireM.receive();
  byte day = TinyWireM.receive();
  byte mm = TinyWireM.receive();
  byte yr = TinyWireM.receive();
  byte sqr = TinyWireM.receive();


  writeData1(0, 0x80);
  //now, we'll write everything *except* the second
  TinyWireM.beginTransmission(DS1307_ADDR);
  TinyWireM.send((uint8_t) 0x01);
  
  int iMM = bcdToDec1(minutes);
  int iHH = bcdToDec1(hours);
  
  if (setMins == 1)
  {
    //mins++
    
    if(iMM < 59)
      iMM++;
     byte b = decToBcd1(iMM); 
    TinyWireM.send(b);
  }else if (setMins == 2)
  {
    if(iMM > 0)
      iMM--;
     byte b = decToBcd1(iMM); 
    TinyWireM.send(b);
  }
  else
  {
    TinyWireM.send(minutes);
  }

  if (setHr == 1)
  {
    if(iHH < 23)
      iHH++;
    byte b = decToBcd1(iHH);  
    TinyWireM.send(b);
  }else if (setHr == 2)
  {
    if(iHH > 0)
      iHH--;
    byte b = decToBcd1(iHH);  
    TinyWireM.send(b);
  }
  else
  {
    TinyWireM.send(hours);
  }

  TinyWireM.send(dow1);
  TinyWireM.send(day);
  TinyWireM.send(mm);
  TinyWireM.send(yr);
  TinyWireM.endTransmission();
  //now, we'll write the seconds; we didn't have to keep
  //track of whether the clock was already running, because
  //_reg0_sec already knows what we want it to be. This
  //will restart the clock as it writes the new seconds value.
  writeData1(0, seconds);
}

byte decToBcd1(byte b)
{
  return ( ((b/10) << 4) + (b%10) );
}

// Convert binary coded decimal to normal decimal numbers
byte bcdToDec1(byte b)
{
  return ( ((b >> 4)*10) + (b%16) );
}
void writeData1(byte regNo, byte value)
{
  if (regNo > 0x3F) {
    return;
  }
  TinyWireM.beginTransmission(DS1307_ADDR);
  TinyWireM.send(regNo);
  TinyWireM.send(value);
  TinyWireM.endTransmission();
}

