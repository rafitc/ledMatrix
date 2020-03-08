/*********
  Complete project details at https://randomnerdtutorials.com  
*********/

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

const char msg;
unsigned int LengMsg;
// Configure software serial port
SoftwareSerial SIM900(7, 8);
//Variable to save incoming SMS characters
char incoming_char=0;


void scan_module()
{
  led_module.scanDisplayBySPI();
}

void setup() {
  // Arduino communicates with SIM900 GSM shield at a baud rate of 19200
  // Make sure that corresponds to the baud rate of your module
  SIM900.begin(19200);
  // For serial monitor
  Serial.begin(19200); 
  // Give time to your GSM shield log on to network
  delay(20000);
  
  Timer1.initialize(2000);
  Timer1.attachInterrupt(scan_module);
  led_module.clearScreen( true );

  // AT command to set SIM900 to SMS mode
  SIM900.print("AT+CMGF=1\r"); 
  delay(100);
  // Set module to send SMS data to serial out upon receipt 
  SIM900.print("AT+CNMI=2,2,0,0,0\r");
  delay(100);
}

void loop() {
  // Display any text that the GSM shield sends out on the serial monitor
  if(SIM900.available() >0) {
    //Get the character from the cellular serial port
    incoming_char=SIM900.read(); 
    //Print the incoming character to the terminal
    Serial.print(incoming_char); 

    *msg = incoming_char;
    String sr = String(msg);
    LengMsg = sr.length();
    led_module.selectFont(FONT);
    led_module.drawMarquee(msg,LengMsg, (32 * ROW), 0);
    long start = millis();
    long timming = start;
    boolean flag = false;
    while (!flag){
      if ((timming + 20) < millis()) {
        flag = led_module.stepMarquee(-1, 0);
        timming = millis();
      }
    }
    
  }
}
