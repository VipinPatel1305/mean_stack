#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int irPin = 3; //Sensor pin connect to digital pin2 (ATINY85 pin7)
int start_bit = 2200; //Start bit threshold (Microseconds)
int bin_1 = 1000; //Binary 1 threshold (Microseconds)
int bin_0 = 400; //Binary 0 threshold (Microseconds)
const byte BIT_PER_BLOCK = 32;

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 20 chars and 4 line display
char ar[5] = {'0', '0', '0', '0', '0'};

int counter = 0;
int counterMini = 0;
void setup() {
  pinMode(irPin, INPUT);
  //Serial.begin(9600);
  lcd.init();  
  printMyStr(ar, sizeof(ar)/sizeof(ar[0]));
}


 
void loop() {

  int key = getIRKey();        //Fetch the key
  //int key = 0;

  if(key != 0)
  {
    char keyValue[5] = {'0', '0', '0', '0', '0'};
    int indx = 0;
    
    while(key > 0 && indx < 5)
    {
      keyValue[indx] = (key % 10) + '0';
      key = key / 10;
      indx++;
    }
    
    lcd.setCursor(0, 0);
    printMyStr(keyValue, 5);
    //delay(5000);
  }
  
  lcd.setCursor(0, 1);
  printMyStr(ar, 5);
  incrValue();
  delay(10);
}

void incrValue()
{
  
  if(counterMini > 10)
    counterMini = 0;
  else
  {
    counterMini++;
    return;
  }
    
  counter++;
  int t = counter;
  int indx = 0;

  while(t > 0 && indx < 5)
  {
    int digit = t % 10;
    ar[indx] = digit + '0';
    t = t/10;
    indx++;
  }
}


void printMyStr(char ar1[], int size1)
{
    for(int i = size1 - 1; i> -1; i--)
     lcd.print(ar1[i]);
} 
/////////////////////////////////////////////////////////////
// decode infrared signal
/////////////////////////////////////////////////////////////
int getIRKey() {
  int data[BIT_PER_BLOCK];
  int i;
  //while(pulseIn(irPin, HIGH) < start_bit); //Wait for a start bit
 if(pulseIn(irPin, HIGH) < start_bit)
  return 0;
  
  for(i = 0 ; i < BIT_PER_BLOCK ; i++) 
    data[i] = pulseIn(irPin, HIGH); //Start measuring bits, I only want HIGH pulses
 
  delay(100);  
  for(i = 0 ; i < BIT_PER_BLOCK ; i++) //Parse them
  {   
    if(data[i] > bin_1) //is it a 1?
      data[i] = 1;
    else if(data[i] > bin_0) //is it a 0?
      data[i] = 0;
    else
      return -1; //Flag the data as invalid; Return -1 on invalid data
  }
  //based on NEC protocol, command data started from bit 16
  //and end with bit 24 (8 bits long)
  int result = 0;
  for(i = 16 ; i < 24; i++) { 
    //DigiKeyboard.print(data[i]); //print out the value of button in binary form
    if(data[i] == 1) result |= (1<<i-16); //Convert data bits to integer
  }  
  return result; //Return key number
}
