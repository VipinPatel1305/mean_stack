#include <avr/io.h>
#include <util/delay.h>

void setup() {
  // put your setup code here, to run once:
  pinMode(9, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(9, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);              // wait for a second
  digitalWrite(9, LOW);    // turn the LED off by making the voltage LOW
  delay(100); 
}
