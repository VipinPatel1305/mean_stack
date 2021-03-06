
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define RECV_PIN 6
#define LM_PREC 0
#define SPKR 9
#define DS1307_ADDR 0x68

int start_bit = 2200; //Start bit threshold (Microseconds)
int bin_1 = 1000; //Binary 1 threshold (Microseconds)
int bin_0 = 400; //Binary 0 threshold (Microseconds)
const byte BIT_PER_BLOCK = 32;

LiquidCrystal_I2C lcd(0x27, 16, 2);

int x = 0;
int prevMinUp = -1;
int flagDot = 0;
int alarmMins = 0;
int backLightState = 1;
char formatted[5];
int timeCounter = 0;

int temp1, temp2;
int tim1, tim2, tim3;
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

  pinMode(RECV_PIN, INPUT);
  pinMode(LM_PREC, INPUT);
  pinMode(SPKR, OUTPUT);
  analogReference(INTERNAL);
  lcd.createChar(8, LT);
  lcd.createChar(1, UB);
  lcd.createChar(2, RT);
  lcd.createChar(3, LL);
  lcd.createChar(4, LB);
  lcd.createChar(5, LR);
  lcd.createChar(6, UMB);
  lcd.createChar(7, LMB);

  getTime(formatted);
  lcdTime();
  displayTemp(1);
  displayAlarm();
  
  
  delay(500);
  Serial.begin(9600);
}



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



void displayAlarm()
{
    lcd.setCursor(13, 1);
    tim1 = alarmMins / 100;
    lcd.print(tim1);
    tim2 = alarmMins - tim1 * 100;
    lcd.print(tim2/10);
    tim3 = tim2 - (tim2/10) * 10;
    lcd.print(tim3);
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


void reduceAlarm()
{
  alarmMins -= 1;
  displayAlarm();

  if (alarmMins <= 0)
  {
    alarmMins = 0;
    displayAlarm();
    beepAlarm();
    getTime(formatted);
    lcdTime();
  }
}

void displayTemp(int flagCompute)
{

  if(flagCompute == 1)
  {
    float temp;
    //dicard first value
    int reading = analogRead(LM_PREC);
    reading = 0;
    
    for(int i = 0; i < 10; i++)
    {
      reading += analogRead(LM_PREC);
      delay(40);
    }
  
    temp =  (1.1 * reading * 10) / 1023; 
    
    int iTem = temp * 100;
    temp1 = iTem/1000;
    temp2 = iTem - temp1 * 1000; 
    temp2 = temp2/100;
  }
  
  lcd.setCursor(14, 0);
  lcd.print(temp1);
  lcd.print(temp2);
  Serial.print(temp1);
  Serial.print(" ");
  Serial.print(temp2);
  Serial.println(" ===");
}

//========================//




void loop()
{
  
  irdecode();

  if(timeCounter % 50 == 0)
  {
    getTime(formatted);   
  }
  
  char *displayTime = formatted;
  int curMinute = 0;
  char curMin = displayTime[3];

  if (prevMinUp != curMin)
  {
    lcd.clear();
    displayTemp(0);
    lcdTime();
    
    prevMinUp = curMin;

    if (alarmMins > 0)
    {
      reduceAlarm();
    }
  }

  if(timeCounter % 100 == 0)
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
  
  
  timeCounter++;

  if(timeCounter == 101)
  {
    timeCounter = 0;
  }

  delay(200);
}


void lcdTime()
{
  lcd.setCursor(0, 0);
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


void getTime(char *formatted)
{
  char *displayTime = formatted;
  //displayTime += 9;
  //Serial
  Wire.beginTransmission(DS1307_ADDR); // reset DS1307 register pointer
  Wire.write((uint8_t) 0x00);
  Wire.endTransmission();

  Wire.requestFrom(DS1307_ADDR, 8);
  byte seconds = Wire.read();  // handle the 7 bytes received
  byte minutes = Wire.read();
  byte hours = Wire.read();
  byte dow1 = Wire.read();
  byte day = Wire.read();
  byte mm = Wire.read();
  byte yr = Wire.read();
  byte sqr = Wire.read();

  displayTime[0] =  (hours >> 4) + 48;
  displayTime[1] =  (hours & 0x0f) + 48;
  displayTime[2] =  (minutes >> 4) + 48;
  displayTime[3] =  (minutes & 0x0f) + 48;
}

void setTime(int setHr, int setMins)
{
  Wire.beginTransmission(DS1307_ADDR); // reset DS1307 register pointer
  Wire.write((uint8_t) 0x00);
  Wire.endTransmission();

  Wire.requestFrom(DS1307_ADDR, 8);
  byte seconds = Wire.read();  // handle the 7 bytes received
  byte minutes = Wire.read();
  byte hours = Wire.read();
  byte dow1 = Wire.read();
  byte day = Wire.read();
  byte mm = Wire.read();
  byte yr = Wire.read();
  byte sqr = Wire.read();


  writeData1(0, 0x80);
  //now, we'll write everything *except* the second
  Wire.beginTransmission(DS1307_ADDR);
  Wire.write((uint8_t) 0x01);
  
  int iMM = bcdToDec1(minutes);
  int iHH = bcdToDec1(hours);
  
  if (setMins == 1)
  {
    //mins++
    
    if(iMM < 59)
      iMM++;
     byte b = decToBcd1(iMM); 
    Wire.write(b);
  }else if (setMins == 2)
  {
    if(iMM > 0)
      iMM--;
     byte b = decToBcd1(iMM); 
    Wire.write(b);
  }
  else
  {
    Wire.write(minutes);
  }

  if (setHr == 1)
  {
    if(iHH < 23)
      iHH++;
    byte b = decToBcd1(iHH);  
    Wire.write(b);
  }else if (setHr == 2)
  {
    if(iHH > 0)
      iHH--;
    byte b = decToBcd1(iHH);  
    Wire.write(b);
  }
  else
  {
    Wire.write(hours);
  }

  Wire.write(dow1);
  Wire.write(day);
  Wire.write(mm);
  Wire.write(yr);
  Wire.endTransmission();
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
  Wire.beginTransmission(DS1307_ADDR);
  Wire.write(regNo);
  Wire.write(value);
  Wire.endTransmission();
}

