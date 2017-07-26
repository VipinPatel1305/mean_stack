/*
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <IRremote.h>

int RECV_PIN = 10;

IRrecv irrecv(RECV_PIN);
IRsend irsend;
decode_results results;
unsigned int rawCod[] = {3,7,7,2,7,9,3,0,2,3};

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  irsend.enableIROut(38);
}

void loop() {
  //recvTest();
  sendTest();
  delay(10000);

}

void recvTest()
{
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    Serial.println(results.value, DEC);
    Serial.println(results.decode_type);
    irrecv.resume(); // Receive the next value
  }
}

void sendTest()
{
  //irsend.sendRaw(0xE0E040BF, 32, 38);
  //delay(1000);
  //irsend.sendSAMSUNG(0xE0E040BF, 32);
  irsend.sendRC5(0xB5E, 12);
}


