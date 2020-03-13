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
const char *msg;
unsigned int LengMsg;
SoftwareSerial mySerial(3, 2);

void scan_module(){
  led_module.scanDisplayBySPI();
}

void setup() {
  Timer1.initialize(2000);
  Timer1.attachInterrupt(scan_module);
  led_module.clearScreen( true );
  
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
  delay(500);

  //Start print in led matrix 
  led_module.selectFont(FONT);
  led_module.drawMarquee(msg,LengMsg, (32 * ROW), 0);
  long start = millis();
  long timming = start;
  boolean flag = false;
  while (!flag){
    if((timming + 20) < millis()){
        flag = led_module.stepMarquee(-1, 0);
        timming = millis();
      }
    }
  }

void pollSms(){
  delay(500);
  while (Serial.available()) {
    mySerial.write(Serial.read());
    //String st = String(Serial.read());
    //Serial.println(st);
  }
  while(mySerial.available()) {
    Serial.write(mySerial.read());
    st = String(mySerial.readString());
    Serial.println(st);
    LengMsg = st.length();
    st.toCharArray(msg,LengMsg);    
  }
  delay(500);
}
