#include <SoftwareSerial.h>
SoftwareSerial mySerial(3, 2);
void setup() {
  Serial.begin(4800);
  mySerial.begin(4800);
  Serial.println("Starting..."); 
  delay(1000);
  mySerial.println("AT");
  pollSms();
  mySerial.println("AT+CMGF=1"); 
  pollSms();
  mySerial.println("AT+CNMI=1,2,0,0,0");
  pollSms();
}

void loop(){
  pollSms();
}

void pollSms(){
  delay(500);
  while (Serial.available()) {
    mySerial.write(Serial.read());
    String st = String(Serial.read());
    Serial.println(st);
  }
  while(mySerial.available()) {
    Serial.write(mySerial.read());
  }
  delay(500);
}
