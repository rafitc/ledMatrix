#include <SPI.h>
#include <DMD.h>
#include <TimerOne.h>
#include "SystemFont5x7.h"
#include "Arial_black_16.h"

#define ROW 1
#define COLUMN 1
#define FONT Arial_Black_16

DMD led_module(ROW, COLUMN);
#include <SoftwareSerial.h>
const char *msg;
SoftwareSerial mySerial(3, 2);

void scan_module()
{
  led_module.scanDisplayBySPI();
}
void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  Serial.println("Starting..."); 
  delay(1000);
  mySerial.println("AT");
  mySerial.println("AT+CMGF=1"); 
  mySerial.println("AT+CNMI=1,2,0,0,0");
  test();
  Timer1.initialize(2000);
  Timer1.attachInterrupt(scan_module);
  led_module.clearScreen( true );
}
void loop()
{
  test2();
}
  void test(){
   while (Serial.available()) {
   mySerial.write(Serial.read());
  }
  while(mySerial.available()){
    Serial.write(mySerial.read());
   }
}

void test2() {
   /*while (Serial.available()) {
   mySerial.write(Serial.read());
  }*/
  while(mySerial.available()){
    Serial.write(mySerial.read());
    String st = String(mySerial.read());
    unsigned int k = st.length();
    st.toCharArray(*msg,k);
    Serial.write(msg);

    led_module.selectFont(FONT);
    led_module.drawMarquee(msg,k, (32 * ROW), 0);
    long start = millis();
    long timming = start;
    boolean flag = false;
    while (!flag)
    {
      if ((timming + 20) < millis()) 
      {
        flag = led_module.stepMarquee(-1, 0);
        timming = millis();
      }
    }
  }
}
