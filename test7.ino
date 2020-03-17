#include <SoftwareSerial.h>
#include <SPI.h>
#include <DMD.h>
#include <TimerOne.h>
#include "SystemFont5x7.h"
#include "Arial_black_16.h"

#define ROW 1
#define COLUMN 1
#define FONT Arial_Black_16

DMD led_module(ROW, COLUMN);

String st; 
 char *msg;
unsigned int LengMsg;
String m;
String actual;
String s;

int buz = 9;
SoftwareSerial mySerial(3, 2);

void scan_module(){
  led_module.scanDisplayBySPI();
}

void setup() {
  Timer1.initialize(2000);
  Timer1.attachInterrupt(scan_module);
  led_module.clearScreen( true );

  pinMode(buz,OUTPUT);
  
  Serial.begin(4800);
  mySerial.begin(4800);
  Serial.println("Starting..."); 
  delay(1000);
  mySerial.println("AT");
  delay(200);
//  pollSms();
  mySerial.println("AT+CMGF=1"); 
  delay(200);
//pollSms();
  mySerial.println("AT+CNMI=1,2,0,0,0");
  delay(200);
//  pollSms();
}

void loop()
{
  //pollSms();
  while(mySerial.available())
  {
    actual = mySerial.readString();
    Serial.println(actual);
    digitalWrite(buz,HIGH);
    delay(1000);
    digitalWrite(buz,LOW);
    
  }
  while(Serial.available())
  {
    m = Serial.readString();
    Serial.println(m.c_str());
  }
   delay(500);
  const char *messages = actual.c_str();
  int lengths = (String(messages)).length();
  //Start print in led matrix 
  led_module.selectFont(FONT);
  led_module.drawMarquee(messages,lengths, (32 * ROW), 0);
  long starts = millis();
  long timming = starts;
  boolean flag = false;
  
  while (!flag){
    if((timming + 50) < millis()){
        flag = led_module.stepMarquee(-1, 0);
        timming = millis();
      }
    }
 }
