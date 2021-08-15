#include "Arduino.h"
#include "Signal.h"

Signal::Signal(int id)
{
  _id = id;
}
void Signal::test()
{
    Serial.println("Test");
}