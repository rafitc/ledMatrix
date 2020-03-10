#include <SoftwareSerial.h>
const char *msg;
SoftwareSerial mySerial(3, 2);

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
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
    //mySerial.write(Serial.read());
 
  }
  while(mySerial.available()) {
    //Serial.write(mySerial.read());
    String st = String(mySerial.read());
    int k = st.length();
    st.toCharArray(*msg,k);
    Serial.write( msg);
    
        
      }
    }
