#include <SoftwareSerial.h>
SoftwareSerial serial(2, 3); // RX digital pin 2, TX digital pin 3.

void setup()
{
  Serial.begin(9600);
  serial.begin(9600); //Baud rate of the GSM/GPRS Module
  serial.println("AT+CMGF=1\r");
  serial.println("AT+CMGR=1\r");//Read SMS at location 1.
  delay(1000);
}
void loop()
{
  if (serial.available() > 0) {
    int c = serial.read();
    Serial.write(c);
  }
  delay(100);
}
