#include <SPI.h>
#include "mcp_can.h"

unsigned char len=0,buf[8],REQ[8],OBD[8],E0[8],E1[8],E8[8],E9[8];
unsigned long int messID;

#define CAN0_INT 2
#define CAN1_INT 3
MCP_CAN CAN0(10);
MCP_CAN CAN1(11);

void setup()
{  
  CAN0.begin(MCP_ANY,CAN_500KBPS,MCP_16MHZ); // Initialize MCP2515 running at 16MHz with a baudrate of 500kb/s and the masks and filters disabled.
  CAN1.begin(MCP_ANY,CAN_500KBPS,MCP_16MHZ); // Initialize MCP2515 running at 16MHz with a baudrate of 500kb/s and the masks and filters disabled.
  CAN0.setMode(MCP_NORMAL); // Set operation mode to normal so the MCP2515 sends acks to received data.
  CAN1.setMode(MCP_NORMAL); // Set operation mode to normal so the MCP2515 sends acks to received data.

  pinMode(0,OUTPUT);
  pinMode(1,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(PIN_LED_TXL,OUTPUT);
  
}

void loop()
{
    ////////////////////
   //CANBUS Port Side//
  ////////////////////
  if(!digitalRead(CAN1_INT)){
    digitalWrite(PIN_LED_RXL, LOW);   // turn the LED off by making the voltage LOW
    CAN1.readMsgBuf(&messID,&len,buf);
    
    if((messID & 0x80000000) == 0x80000000){     // Determine if ID is standard (11 bits) or extended (29 bits)
      CAN0.sendMsgBuf(messID,1,len,buf);
    }
    else{
      CAN0.sendMsgBuf(messID,0,len,buf);
    }
  }
    ///////////////////
   //CANBUS Car Side//
  ///////////////////
  if(!digitalRead(CAN0_INT)){
    digitalWrite(PIN_LED_RXL, LOW);   // turn the LED off by making the voltage LOW
    CAN0.readMsgBuf(&messID,&len,buf);
    
    if((messID & 0x80000000) == 0x80000000){     // Determine if ID is standard (11 bits) or extended (29 bits)
      CAN1.sendMsgBuf(messID,1,len,buf);
    }
    else{
      CAN1.sendMsgBuf(messID,0,len,buf);
    }
  }
  digitalWrite(PIN_LED_RXL, HIGH);   // turn the LED off by making the voltage LOW
}
