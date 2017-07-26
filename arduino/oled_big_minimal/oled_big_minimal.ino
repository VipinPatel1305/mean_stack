
#include <ssd1306.h>
#include <avr/pgmspace.h>
//#include <SoftwareSerial.h>

SSD1306 oled;
//SoftwareSerial BTSerial(10, 11);
void setup(void)
{
  Serial.begin(9600);
  delay(300);
  Wire.begin();
  oled.begin();
  oled.fill(0x00); // clear in black
 //oled.print_digits(0, 1, 3, 100, 999, false);
  delay(500);
}

int minCount = 0;

void loop()
{
  char msg[300];
  int indx = 0;
  bool readSuccess = false;
  if (Serial.available())
  {
    int bData = Serial.read();
     
    while (bData != -1 && indx < 300)
    {
      msg[indx] = char(bData);
      bData = Serial.read();
      indx++;
    }

    //Serial.println(msg);
    if((msg[0] == '&' || msg[0] == '#')&& msg[indx - 1] == ']')
    {
      readSuccess = true;
      oled.print_digits(0, 1, 3, 100, minCount, false);
      minCount++;

      if(minCount > 999)
        minCount = 0;
    }
    //Serial.println(msg);
     memset(msg, '\0', 300);

    if (readSuccess == true)
    {
      Serial.print(1);
    }
    else
    {
      Serial.print(0);
    }
  }

  delay(1000);
}

