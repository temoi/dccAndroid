/*
  Signal.h - Library for Signal
  Created by Morten Isaksen  
*/
#ifndef Signal_h
#define Signal_h

#include "Arduino.h"

class Signal
{
  public:
    Signal(int id);
    void test();    
  private:
    int _id;
};
#endif
