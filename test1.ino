

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

void scan_module()
{
  led_module.scanDisplayBySPI();
}

void setup()
{
  Timer1.initialize(2000);
  Timer1.attachInterrupt(scan_module);
  led_module.clearScreen( true );
}
void loop()
{
    const char msg = "Hi Rafi";
    String sr = String(msg);
    LengMsg = sr.length();
    led_module.selectFont(FONT);
    led_module.drawMarquee(msg,LengMsg, (32 * ROW), 0);
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
