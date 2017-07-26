/***************************************************
DFPlayer - A Mini MP3 Player For Arduino
 <https://www.dfrobot.com/index.php?route=product/product&product_id=1121>
 
 ***************************************************
 This example shows the basic function of library for DFPlayer.
 
 Created 2016-12-07
 By [Angelo qiao](Angelo.qiao@dfrobot.com)
 
 GNU Lesser General Public License.
 See <http://www.gnu.org/licenses/> for details.
 All above must be included in any redistribution
 ****************************************************/

/***********Notice and Trouble shooting***************
 1.Connection and Diagram can be found here
 <https://www.dfrobot.com/wiki/index.php/DFPlayer_Mini_SKU:DFR0299#Connection_Diagram>
 2.This code is tested on Arduino Uno, Leonardo, Mega boards.
 ****************************************************/

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

void setup()
{
  mySoftwareSerial.begin(9600);
  Serial.begin(115200);
  
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));
}

int delayTime = 40000;
int songTrack = 5;
int volume = 15;

int eq[] = {DFPLAYER_EQ_NORMAL, DFPLAYER_EQ_POP, DFPLAYER_EQ_ROCK, DFPLAYER_EQ_JAZZ,  DFPLAYER_EQ_CLASSIC, DFPLAYER_EQ_BASS};
char* myStrings[]={"DFPLAYER_EQ_NORMAL", "DFPLAYER_EQ_POP", "DFPLAYER_EQ_ROCK",
"DFPLAYER_EQ_JAZZ", "DFPLAYER_EQ_CLASSIC","DFPLAYER_EQ_BASS"};


void loop()
{
  for(int i = 0; i < 6; i++)
  {
    Serial.println(myStrings[i]);
    myDFPlayer.EQ(DFPLAYER_EQ_POP);
    myDFPlayer.volume(volume);
    myDFPlayer.play(songTrack);
    delay(delayTime);
  }
  
}
void loop1()
{

  Serial.println("DFPLAYER_EQ_POP");
  myDFPlayer.EQ(4);
  myDFPlayer.volume(20);  //Set volume value. From 0 to 30
  myDFPlayer.play(5);  //Play the first mp3
  delay(60000);  
  
  Serial.println("DFPLAYER_EQ_POP");
  myDFPlayer.EQ(DFPLAYER_EQ_POP);
  myDFPlayer.volume(20);  //Set volume value. From 0 to 30
  myDFPlayer.play(5);  //Play the first mp3
  delay(60000);

 Serial.println("DFPLAYER_EQ_ROCK");
  myDFPlayer.EQ(DFPLAYER_EQ_ROCK);
  myDFPlayer.volume(20);  //Set volume value. From 0 to 30
  myDFPlayer.play(5);  //Play the first mp3
  delay(60000);

  Serial.println("DFPLAYER_EQ_JAZZ");
  myDFPlayer.EQ(DFPLAYER_EQ_JAZZ);
  myDFPlayer.volume(20);  //Set volume value. From 0 to 30
  myDFPlayer.play(5);  //Play the first mp3  
  delay(60000);

  Serial.println("DFPLAYER_EQ_CLASSIC");
  myDFPlayer.EQ(DFPLAYER_EQ_CLASSIC);
  myDFPlayer.volume(20);  //Set volume value. From 0 to 30
  myDFPlayer.play(5);  //Play the first mp3           
  delay(60000);

  Serial.println("DFPLAYER_EQ_BASS");
  myDFPlayer.EQ(DFPLAYER_EQ_BASS);
  myDFPlayer.volume(20);  //Set volume value. From 0 to 30
  myDFPlayer.play(5);  //Play the first mp3  
  delay(60000);
}

void printDetail(uint8_t type, int value){
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }

}
