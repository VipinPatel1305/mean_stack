int ledPin = 13;

int knockSensor = 0;               

byte val = 0;

int statePin = LOW;

int THRESHOLD = 3;



void setup() {

 pinMode(ledPin, OUTPUT); 

 Serial.begin(9600);

}



void loop() {

  val = analogRead(knockSensor);     

  if (val >= THRESHOLD) {

    statePin = !statePin;

    //digitalWrite(ledPin, statePin);

    Serial.println("Knock!");
    Serial.println(val);


  }

  delay(100);  // we have to make a delay to avoid overloading the serial port
 
}
