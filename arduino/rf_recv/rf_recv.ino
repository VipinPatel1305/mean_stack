/*
  RF_Sniffer
 
  Hacked from http://code.google.com/p/rc-switch/
 
  by @justy to provide a handy RF code sniffer
*/

#include "RCSwitch.h"
#include <stdlib.h>
#include <stdio.h>
RCSwitch mySwitch = RCSwitch();
#define LAMP 4


void setup() {
  mySwitch.enableReceive(0);  // Receiver on inerrupt 0 =&gt; that is pin #2
  pinMode(LAMP, OUTPUT);
  delay(300);
  Serial.begin(9600);
}
 
void loop() {
  if (mySwitch.available()) {
 
    int value = mySwitch.getReceivedValue();
 
    if (value == 0) {
      Serial.print("Unknown encoding");
    } else {
 
      Serial.print("Received ");
      Serial.print( mySwitch.getReceivedValue() );

      if(mySwitch.getReceivedValue() == 400)
      {
        digitalWrite(LAMP, HIGH); 
        Serial.println("lamp on");
      }
      else if(mySwitch.getReceivedValue() == 500)
      {
        digitalWrite(LAMP, LOW);
        Serial.println("lamp off");
      }
      else if(mySwitch.getReceivedValue() == 600)
      {
        Serial.println("fan off");
      }
      else if(mySwitch.getReceivedValue() == 700)
      {        
        Serial.println("fan on");
      }
      /*
      Serial.print(" / ");
      Serial.print( mySwitch.getReceivedBitlength() );
      Serial.print("bit ");
      Serial.print("Protocol: ");
      Serial.println( mySwitch.getReceivedProtocol() );
      */
    }
 
    mySwitch.resetAvailable();
 
  }
}

