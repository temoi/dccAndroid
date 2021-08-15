#include "Arduino.h"
#include "MegaPoint.h"

#include <Wire.h> //Need for MegaControllers
#define SlaveAddr 21 // Set out I2C address to 21 so we can receive updates from the MultiPanel master.
uint8_t MultiPanelBank = 0; // Bank address (0-23)
uint8_t MultiPanelData = 0; // Data
uint8_t MultiPanelDataOld = 0; // Data
uint8_t MultiPanelDataReady = 0; // Fresh data indicator
uint8_t MultiPanelDataArray[24] = {0};

MegaPoint_::MegaPoint_()
{
  // this->_slaveAddr=SlaveAddr;
}
void MegaPoint_::init(int nWaitMs)
{
  void  receiveEvent(int howmany);  
  Wire.begin(SlaveAddr); // Initialise I2C comms, dont care what our address is as were only transmitting data.
  Serial.println("Listening for MegaPoints Controllers MultiPanel data ...");
  Serial.println("\tBank\tData");
  Wire.onReceive(receiveEvent);
}
void MegaPoint_::run()
{
   if (MultiPanelDataReady==1) {
       
       if (MultiPanelBank<24) {
         MultiPanelDataOld = MultiPanelDataArray[MultiPanelBank];
         MultiPanelDataArray[MultiPanelBank] = MultiPanelData;
         if (MultiPanelDataOld!=MultiPanelData) {
           for (int i = 0; i<9; i++) {
             if (bitRead(MultiPanelDataOld,i)!=bitRead(MultiPanelData,i)) {
                
                if (onMegaPointAddrChange) {
                  onMegaPointAddrChange(databank2dccId(MultiPanelBank,i),bitRead(MultiPanelData,i));
                };
                /*
                Serial.print("\t");
                Serial.print("DCC# "+String(databank2dccId(MultiPanelBank,i))+" ");
                if (bitRead(MultiPanelData,i)) {
                   Serial.print("on");
                } else {
                   Serial.print("off"); 
                }*/
                
                Serial.println("");
             } 
           }
           /*
            Serial.print("\t");
            Serial.print(MultiPanelBank); // Print the bank number.
            Serial.print("\t");
            Serial.print(MultiPanelData); // Print the data.
            Serial.println();
            */
         }
         
       }
       MultiPanelDataReady = 0; // reset data indicator back to 0.
   }
}
int MegaPoint_::databank2dccId(int aBankid, int aDataIndex) {
  return (aBankid * 8 + aDataIndex + 1);
}
void MegaPoint_::_doInit()
{

}

void  receiveEvent(int howmany){ // This function is called when data is received.
    MultiPanelBank = Wire.read(); // Read the bank number (0-23).
    MultiPanelData = Wire.read(); // Read the data byte.
    MultiPanelDataReady = 1; // Set the data ready flag.
}

// Preinstantiate Objects //////////////////////////////////////////////////////
MegaPoint_ MegaPoint = MegaPoint_();
