#define trigPin 7
#define echoPin 6
#include <SoftwareSerial.h>// import the serial library

SoftwareSerial blu(10, 11); // RX, TX
void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin (9600);
  blu.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  long duration, distance;
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  String d = "#";
  d.concat(distance);
  d.concat("$");
  blu.println(d);
  Serial.println(d);
  delay(500);
}
