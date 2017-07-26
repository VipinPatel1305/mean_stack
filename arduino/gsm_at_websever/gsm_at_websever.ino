#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  mySerial.begin(9600);
  delay(4000);
  Serial.println("Setting up gprs"); 
  gprsSetup(); 
}

int t = 10;

void loop() {
  // put your main code here, to run repeatedly:
  /*if (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }*/

  //ready to send data
  mySerial.write("AT+HTTPDATA=16,10000\r\n");
  delay(500);
  serPrint();

  //data
  String tem = String("temp=");
  String hum = String("&humid=97\r\n");
  String data =  tem + t + hum;
  t =  t + 5;
  mySerial.print(data);
  delay(500);
  serPrint();

  //send using POST
  mySerial.write("AT+HTTPACTION=1\r\n");
  delay(4000);
  serPrint();


  //read server response
  mySerial.write("AT+HTTPREAD\r\n");
  delay(4000);
  serPrint();
         
  delay(90000);
}

void gprsSetup()
{
  mySerial.write("AT\r\n");
  delay(1000);
  serPrint();
  
  mySerial.write("AT+CPIN?\r\n");
  delay(1000);
  serPrint();


  mySerial.write("AT+CREG?\r\n");
  delay(1000);
  serPrint();

  mySerial.write("AT+CGATT?\r\n");
  delay(1000);
  serPrint();

  mySerial.write("AT+CSQ\r\n");
  delay(1000);
  serPrint();

  mySerial.write("AT+SAPBR=3,1,\"Contype\",\"GPRS\"\r\n");
  delay(1000);
  serPrint();

  mySerial.write("AT+SAPBR=3,1,\"APN\",\"airtelgprs.com\"\r\n");
  delay(1000);
  serPrint();        

  mySerial.write("AT+SAPBR=2,1\r\n");
  delay(1000);
  serPrint();

  mySerial.write("AT+HTTPINIT\r\n");
  delay(1000);
  serPrint();  

  mySerial.write("AT+HTTPPARA=\"CID\",1\r\n");
  delay(1000);
  serPrint();   

  mySerial.write("AT+HTTPPARA=\"URL\",\"http://vipinrocks.net23.net/remote_insert.php\"\r\n");
  delay(1000);
  serPrint();    
     
  mySerial.write("AT+HTTPPARA=\"Content\",\"application/x-www-form-urlencoded\"\r\n");
  delay(1000);
  serPrint();         
}

void serPrint()
{
    if(mySerial.available())
  {
    Serial.println(mySerial.readString());
  }
}



void closeConn()
{
  mySerial.write("AT+HTTPTERM\r\n");
  delay(1000);
  serPrint(); 

  mySerial.write("AT+SAPBR=0,1\r\n");
  delay(1000);
  serPrint();     
}

