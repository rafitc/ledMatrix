#include <SPI.h>
#include <DMD.h>
#include <TimerOne.h>
#include "SystemFont5x7.h"
#include "Arial_black_16.h"

#define ROW 1
#define COLUMN 1
#define FONT Arial_Black_16

DMD led_module(ROW, COLUMN);
int LengMsg;

int led=13;

int temp=0,i=0,x=0,k=0;
char str[100],*msg;

void setup() 
{
  Timer1.initialize(2000);
  Timer1.attachInterrupt(scan_module);
  led_module.clearScreen( true );
  
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);
  Serial.println("GSM Initilizing...");
  gsm_init();
  Serial.println("System Ready");
  Serial.println("AT+CNMI=2,2,0,0,0");
  delay(500);
  Serial.println("AT+CMGF=1");
  delay(1000);
  digitalWrite(led, LOW);
}
void scan_module(){
  led_module.scanDisplayBySPI();
}

void loop()    
{
  for(unsigned int t=0;t<60000;t++)
  {
    serialEvent();
  if(temp == 1)

  
  {
    x=0,k=0,temp=0;
    while(x<i)
    {
      while(str[x]=='#')
      {
        x++;
        while(str[x]!='*')
        {
          msg[k++]=str[x++];
        }
      }
      x++;
    }
    msg[k]='\0';
  //  String st = String(msg);
   Serial.println(String(msg));
    
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
    delay(1000);
    temp=0;
    i=0;
    x=0;
    k=0;
  }
  }
//  lcd.scrollDisplayLeft();
}
void serialEvent()
{
  while(Serial.available())
  {
    char ch=(char)Serial.read();
    str[i++]=ch;
    if(ch == '*')
    {
      temp=1;
      Serial.println("Message Received");
      delay(1000);
    }
  }
}

void gsm_init()
{
  Serial.println("Finding Module..");
  boolean at_flag=1;
  while(at_flag)
  {
    Serial.println("AT");
    while(Serial.available()>0)
    {
      if(Serial.find("OK"))
      at_flag=0;
    }
    delay(1000);
  }
  Serial.print("Module Connected..");
  delay(1000);
  boolean echo_flag=1;
  while(echo_flag)
  {
    Serial.println("ATE0");
    while(Serial.available()>0)
    {
      if(Serial.find("OK"))
      echo_flag=0;
    }
    delay(1000);
  }
  Serial.println("Finding Network..");
  boolean net_flag=1;
  while(net_flag)
  {
    Serial.println("AT+CPIN?");
    while(Serial.available()>0)
    {
      if(Serial.find("+CPIN: READY"))
      net_flag=0;
    }
    delay(1000);
  }
  Serial.print("Network Found..");
  delay(1000);
}
