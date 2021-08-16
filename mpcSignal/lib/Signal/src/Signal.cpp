#include "Arduino.h"
#include "Signal.h"

//Using Arduino Nano for host

#define sign1_red 2
#define sign1_green 3
#define sign1_yellow 4
#define sign2_red 5
#define sign2_green 6
#define sign2_yellow 7
#define sign3_red 8
#define sign3_green 9
#define sign3_yellow 10
#define sign4_red 11
#define sign4_green 12
#define sign4_yellow 13
#define sign5_red 14
#define sign5_green 15
#define sign5_yellow 16
#define sign6_red 17
#define sign6_green 20
#define sign6_yellow 21






Signal::Signal(int dccAdr)
{
  _dccAdr = dccAdr;
  _signItems[0].signstatus=0;
  _signItems[0].pin_red=sign1_red;
  _signItems[0].pin_green=sign1_green;
  _signItems[0].pin_yellow=sign1_yellow;
  _signItems[0].dcc = dccAdr;
  pinMode(sign1_red,OUTPUT);
  pinMode(sign1_green,OUTPUT);
  pinMode(sign1_yellow,OUTPUT);
  setSignalStatus(0,sign1_red);

  return;

  _signItems[1].signstatus=0;
  _signItems[1].pin_red=sign2_red;
  _signItems[1].pin_green=sign2_green;
  _signItems[1].pin_yellow=sign2_yellow;
  _signItems[1].dcc = dccAdr + 2;
  pinMode(sign2_red,OUTPUT);
  pinMode(sign2_green,OUTPUT);
  pinMode(sign2_yellow,OUTPUT);
  setSignalStatus(1,sign1_red);

  _signItems[2].signstatus=0;
  _signItems[2].pin_red=sign3_red;
  _signItems[2].pin_green=sign3_green;
  _signItems[2].pin_yellow=sign3_yellow;
  _signItems[2].dcc = dccAdr + 4;
  pinMode(sign3_red,OUTPUT);
  pinMode(sign3_green,OUTPUT);
  pinMode(sign3_yellow,OUTPUT);
  setSignalStatus(2,sign1_red);

  _signItems[3].signstatus=0;
  _signItems[3].pin_red=sign4_red;
  _signItems[3].pin_green=sign4_green;
  _signItems[3].pin_yellow=sign4_yellow;
  _signItems[3].dcc = dccAdr + 6;
  pinMode(sign4_red,OUTPUT);
  pinMode(sign4_green,OUTPUT);
  pinMode(sign4_yellow,OUTPUT);
  setSignalStatus(3,sign1_red);
}

void Signal::dccValueChange(int dccAdr, boolean value)
{
  int no = getSignalIndex(dccAdr);
  if (no!=0) return;
  if (no > -1)
  {
    if (_signItems[no].dcc == dccAdr)
    {
      _signItems[no].value[0] = value;
    }
    else
    {
      _signItems[no].value[1] = value;
    }
    
    if (_signItems[no].value[0])
    {
      if (_signItems[no].value[1])
      {
        _signItems[no].signstatus = sign_yellow;
      }
      else
      {
        _signItems[no].signstatus = sign_green;
      }
    }
    else
    {
      _signItems[no].signstatus = sign_red;
    }
    updatePins(no);
  }
}

void Signal::test()
{
  Serial.println("Test");
}
int Signal::getSignalIndex(int dccAdr)
{
  if ((dccAdr < _dccAdr) || (dccAdr > (_dccAdr + 11)))
    return -1;
  return ((dccAdr - _dccAdr) / 2);
}
void Signal::updatePins(int signalIndex)
{
  Serial.print("\t");
  switch (_signItems[signalIndex].signstatus)
  {
  case sign_green:
    digitalWrite(_signItems[signalIndex].pin_green, HIGH);
    digitalWrite(_signItems[signalIndex].pin_red, LOW);
    digitalWrite(_signItems[signalIndex].pin_yellow, LOW);
    Serial.print("Signal Green");
    break;
  case sign_red:;
    digitalWrite(_signItems[signalIndex].pin_green, LOW);
    digitalWrite(_signItems[signalIndex].pin_red, HIGH);
    digitalWrite(_signItems[signalIndex].pin_yellow, LOW);
    Serial.print("Signal Red");
    break;
  case sign_yellow:;
    digitalWrite(_signItems[signalIndex].pin_green, HIGH);
    digitalWrite(_signItems[signalIndex].pin_red, LOW);
    digitalWrite(_signItems[signalIndex].pin_yellow, HIGH);
    Serial.print("Signal Yellow");
    break;
  default:
    break;
  }
}

void Signal::setSignalStatus(int index, int status)
{
  _signItems[index].signstatus = status; 
  switch (status)
  {
  case sign_red:
    _signItems[index].value[0] = false;
    _signItems[index].value[1] = false;
    break;
  case sign_green:
    _signItems[index].value[0] = true;
    _signItems[index].value[1] = false;
    break;
  case sign_yellow:
    _signItems[index].value[0] = true;
    _signItems[index].value[1] = true;
  default:
    break;
  }
  updatePins(index);
}
