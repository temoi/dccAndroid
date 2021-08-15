/*
  Signal.h - Library for Signal
  Created by Morten Isaksen  
*/
#ifndef MegaPoint_h
#define MegaPoint_h


#include "Arduino.h"

class MegaPoint_
{
  public:
    MegaPoint_();  
    void init(int nWaitMs);
    void run();
    int databank2dccId(int aBankid, int aDataIndex);    
       
  private:
    void _doInit();    
    int _slaveAddr;
};
extern MegaPoint_ MegaPoint;

extern void onMegaPointAddrChange(int dccAdr, boolean value);

#endif
