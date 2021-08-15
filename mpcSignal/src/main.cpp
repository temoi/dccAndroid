#include <Arduino.h>
#include "Signal.h"
#include "MegaPoint.h"

int period = 1000;
unsigned long time_now = 0;
Signal signal(1);
//MegaPoint megaPoint(21); //Set out I2C address to 21 so we can receive updates from the MultiPanel master.

void onMegaPointAddrChange(int dccAdr, boolean value)
{
    Serial.print("\t");
    Serial.print("DCC# " + String(dccAdr) + " ");
    if (value)
    {
        Serial.print("green");
    }
    else
    {
        Serial.print("red");
    }
}

void setup() {  
    Serial.begin(115200);
    MegaPoint.init(0);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(millis() >= time_now + period){
        time_now += period;
        //Serial.println("Hello");
        //signal.test();

    }
    MegaPoint.run();
}