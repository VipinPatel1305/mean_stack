#include <Wire.h>

#define DS1307_ADDR 0x68

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  char formatted[] = "00:00:00 00-00-00x";
  char *displayTime = formatted;
  displayTime += 9;
  Wire.beginTransmission(DS1307_ADDR); // reset DS1307 register pointer 
  Wire.write((uint8_t) 0x00);
  Wire.endTransmission();
   
  Wire.requestFrom(DS1307_ADDR, 8);
  byte seconds = Wire.read();  // handle the 7 bytes received
  byte minutes = Wire.read();
  byte hours = Wire.read();
  byte dow = Wire.read();
  byte day = Wire.read();
  byte mm = Wire.read();
  byte yr = Wire.read();
  byte sqr = Wire.read();

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
 
  int minL = seconds & 0x0f;
  int minR = seconds >> 4;
  /*
  Serial.print(minR);
  Serial.print(" ");
  Serial.print(minL);
  */
  Serial.print(displayTime);
  Serial.print("\n");
  int dayOfWeek = (dow >> 4) + 48;
  Serial.print(dow);
  delay(1000);
  
      
  /*
  byte hours = bcdToDec(Wire.receive());        
  byte day_of_week = bcdToDec(Wire.receive());    
  byte days = bcdToDec(Wire.receive());          
  byte months = bcdToDec(Wire.receive());      
  byte years = bcdToDec(Wire.receive()); */
}

byte bcdToDec1(byte b)
{
  return ( ((b >> 4)*10) + (b%16) );
}
