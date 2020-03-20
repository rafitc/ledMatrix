#include <SoftwareSerial.h> //
#include <SPI.h> //Library for SPI communication
#include <DMD.h>
#include <TimerOne.h> //P10 libraray 
#include "SystemFont5x7.h" 
#include "Arial_black_16.h" //font libraray  

#define ROW 1
#define COLUMN 1
#define FONT Arial_Black_16 // defined font 

DMD led_module(ROW, COLUMN); //initialised LED module 

String st; 
char *msg;
int lengths;
String m;
String actual;
 
SoftwareSerial mySerial(3, 2); //RX pin 3 , TX pin 2

void scan_module(){
  led_module.scanDisplayBySPI(); //checking module 
}

void setup() {
  pinMode(9,OUTPUT); // Buzzer initialastion 
  Timer1.initialize(2000); 
  Timer1.attachInterrupt(scan_module);
  led_module.clearScreen( true ); //clear led module 
  
  Serial.begin(4800); //begi serial communication 
  mySerial.begin(4800); //begin softSerial communication 
  Serial.println("Starting..."); 
  delay(1000);
  mySerial.println("AT"); //Check GSM is ready or not
  delay(200);

  mySerial.println("AT+CMGF=1"); 
  delay(200);

  mySerial.println("AT+CNMI=1,2,0,0,0"); //set device to receive sms 
  delay(200);

}

void loop(){
  while(mySerial.available())
  {
    actual = mySerial.readString(); //Storing reeived sms 
    digitalWrite(9,HIGH); //turn on Buzzer 
    delay(2000); //2sec delay buz
    digitalWrite(9,LOW); //turn off Buzzer 
    Serial.println(actual); 
    int lengths = actual.length(); //finding length of sms
  while(Serial.available())
  {
    m = Serial.readString();
    //Serial.println(m.length());
   Serial.println(m.c_str()); //print serial content 

  }
   delay(500);
  lengths = actual.length(); //finding length of sms
  const char *messages = actual.c_str(); //STring to Char array conversion
  
  led_module.selectFont(FONT); //SEt font 
  led_module.drawMarquee(messages,lengths, (32 * ROW), 0); //print SMS
  long starts = millis(); //setting time to scroll text
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
