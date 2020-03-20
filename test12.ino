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

int b;
int k=0;
int i;
int startMsg,endMsg;
//char msg1[30];

SoftwareSerial mySerial(3, 2);

void scan_module(){
  led_module.scanDisplayBySPI();
}

void setup() {
  pinMode(9,OUTPUT);
  Timer1.initialize(2000);
  Timer1.attachInterrupt(scan_module);
  led_module.clearScreen( true );
  
  Serial.begin(4800);
  mySerial.begin(4800);
  Serial.println("Starting..."); 
  delay(1000);
  mySerial.println("AT");
  delay(200);

  mySerial.println("AT+CMGF=1"); 
  delay(200);

  mySerial.println("AT+CNMI=1,2,0,0,0");
  delay(200);

}

void loop(){
  while(mySerial.available())
  {
    actual = mySerial.readString();
    digitalWrite(9,HIGH);
    delay(2000); //2sec buz
    digitalWrite(9,LOW);
    Serial.println(actual);
    int lengths = actual.length();
    for(i=0; i<=lengths; i++){
      if(actual[i] == '#'){
        startMsg = i;
      }
     if (actual[i] == '*'){
        endMsg = i;
      }
    }
   k = endMsg - startMsg;
   b=0;
    for(i=startMsg; i<=endMsg;i++){
      Serial.print(actual[i]);
      msg[b++] = actual[i];
    }
    msg[b++] = '\0';
    }
    startMsg =0;
    endMsg=0;
  while(Serial.available())
  {
    m = Serial.readString();
    //Serial.println(m.length());
   Serial.println(m.c_str());

  }
   delay(500);
;
const char *messages = actual.c_str();

//Serial.println(lengths);
  //Start print in led matrix 
  led_module.selectFont(FONT);
  led_module.drawMarquee(msg,b, (32 * ROW), 0);
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
