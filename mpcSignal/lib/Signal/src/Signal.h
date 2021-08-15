/*
  Signal.h - Library for Signal
  Created by Morten Isaksen  
*/
#ifndef Signal_h
#define Signal_h

#include "Arduino.h"

#define sign_red 0
#define sign_green 1
#define sign_yellow 2
#define signalcount 6

typedef struct 
{
  int signstatus =0; // 0=red, 1=green, 2=Yellow, 3=green/yellow 
  int pin_red;
  int pin_green;
  int pin_yellow;
  int dcc =0;
  bool value[2] = {false,false};
} signInfo;


class Signal
{
  public:
    Signal(int dccAdr); //Hoster 16 dcc adresser
    void dccValueChange(int dccAdr, boolean value);
    void setSignalStatus(int index, int status);
    void test();  
    int getSignalIndex(int dccAdr);  
    void updatePins(int signalIndex);
  private:
    int _dccAdr;
    signInfo _signItems[6];
};
#endif
