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
   int k=0;
   int i;
   int startMsg,endMsg;
   char msg1[30];

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
    int le = actual.length();
    int x=0,k=0;
    while(x<le){
      while(actual[x]=='#'){
        x++;
        while(actual[x] !='*'){
          st[k++] = actual[x++];
        }
    }
    x++;
    }
    st[k] = '\0';    
  
  while(Serial.available())
  {
    m = Serial.readString();
    //Serial.println(m.length());
   // Serial.println(m.c_str());

  }
   delay(500);
   
  /*  for(int i=startMsg; i<=endMsg; i++){
      msg1[k] = actual[i];
      k++;
      
    }
    //k++;
    msg1[k] = '\0';
   Serial.print(msg1);*/

const char *messages = st.c_str();
int lengths = (String(st)).length();
//Serial.println(lengths);
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
}
