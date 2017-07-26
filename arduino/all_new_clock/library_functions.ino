
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
  lcd.setCursor(x, 0);
  lcd.write(1);
  lcd.write(2);
  lcd.setCursor(x, 1);
  lcd.write(4);
  lcd.write(255);
  lcd.write(4);
}

void two()
{
  lcd.setCursor(x, 0);
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
  lcd.setCursor(x, 0);
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
  lcd.setCursor(x, 0);
  lcd.write(3);
  lcd.write(4);
  lcd.write(2);
  lcd.setCursor(x + 2, 1);
  lcd.write(255);
}

void five()
{
  lcd.setCursor(x, 0);
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
  lcd.setCursor(x, 0);
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
  lcd.setCursor(x, 0);
  lcd.write(1);
  lcd.write(1);
  lcd.write(2);
  lcd.setCursor(x + 1, 1);
  lcd.write(8);
}

void eight()
{
  lcd.setCursor(x, 0);
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
  lcd.setCursor(x, 0);
  lcd.write(8);
  lcd.write(6);
  lcd.write(2);
  lcd.setCursor(x + 2, 1);
  lcd.write(255);
}



void beepAlarm()
{
  int count = 0;
  
  while (count < 15)
  {
    int key = getIRKey();
    if (key != 0)
    {
      break;
    }
    
    tone(SPKR, 6500); // Send 1KHz sound signal...
    delay(100);        // ...for 1 sec
    tone(SPKR, 4500); // Send 1KHz sound signal...
    delay(100);        // ...for 1 sec        
    tone(SPKR, 7500); // Send 1KHz sound signal...
    delay(100);        // ...for 1 sec    
    tone(SPKR, 3500); // Send 1KHz sound signal...
    delay(100);        // ...for 1 sec                
    noTone(SPKR);     // Stop sound...
    delay(100);        // ...for 1sec
    count++;
  }
}


typedef void (* DigitFuncPtr) ();
DigitFuncPtr numeral[10] = {zero, one, two, three, four, five, six, seven, eight, nine};


/////////////////////////////////////////////////////////////
// decode infrared signal
/////////////////////////////////////////////////////////////
int getIRKey() {
  int data[BIT_PER_BLOCK];
  int i;
  //while(pulseIn(irPin, HIGH) < start_bit); //Wait for a start bit
  if (pulseIn(irPin, HIGH) < start_bit)
    return 0;

  for (i = 0 ; i < BIT_PER_BLOCK ; i++)
    data[i] = pulseIn(irPin, HIGH); //Start measuring bits, I only want HIGH pulses

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

void setup()
{
  pinMode(SPKR, OUTPUT);
  pinMode(irPin, INPUT);
  pinMode(LM_PREC, INPUT);
  Wire.begin();
  lcd.init();
  lcd.backlight();
  char msg[] = "Booting.!.!.!.";
  lcdPrint(msg, sizeof(msg) / sizeof(msg[0]));
  delay(1000);
  rtc.begin();
  delay(1000);

  lcd.createChar(8, LT);
  lcd.createChar(1, UB);
  lcd.createChar(2, RT);
  lcd.createChar(3, LL);
  lcd.createChar(4, LB);
  lcd.createChar(5, LR);
  lcd.createChar(6, UMB);
  lcd.createChar(7, LMB);
  delay(4000);
  getTime();
  refreshLcd();
  displayDayMonth(); 
  displayTemp(1); 
}
