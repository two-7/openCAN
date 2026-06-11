#include <SPI.h>
#include "mcp_can.h"

//CAN/MCP vars
unsigned char len = 0;
unsigned char buf[8];
long unsigned int messID;

//Fan timer vars
unsigned long radtimeold=0, auxtimeold=0;
unsigned long time=0, print;

//Fan vars
int radfanPWM=HIGH, auxfanPWM=HIGH;
byte temp=0; //Stores CAN temp value
bool acstatus=0; //a/c status
byte radfanspeed=4, auxfanspeed=4;
const byte high=38; //high fan duty cycle 95%
const byte med=25; //med fan duty cycle 65%
const byte low=18; //low fan duty cycle 35%
const byte off=4; //fan idle(off) duty cycle 5%
const byte temp1=96;//Stage 1 coolant temp
const byte temp2=99;//Stage 2 coolant temp
const byte temp3=102;//Stage 3 coolat tempCruise vars
bool mainsw=0, mainpwr=1, cancel=1, setretard=1, resaccel=1;

//Pin assignment vars
byte ccancel=0, cresaccel=1, csetretard=4, radfan=5, auxfan=6;

#define CAN0_INT 2  // Set INT to pin 2
MCP_CAN CAN0(10);   // Set CS to pin 10

void setup()
{
SerialUSB.begin(5000000);
pinMode(ccancel,OUTPUT);
pinMode(csetretard,OUTPUT);
pinMode(cresaccel,OUTPUT);
pinMode(radfan,OUTPUT);
pinMode(auxfan,OUTPUT);

digitalWrite(ccancel,cancel); //red/gray T15/7
digitalWrite(csetretard,setretard); //red/yellow T15/9
digitalWrite(cresaccel,resaccel); //blue T15/8

CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ); // Initialize MCP2515 running at 8MHz with a baudrate of 500kb/s and the masks and filters disabled.
CAN0.setMode(MCP_NORMAL);     // Set operation mode to normal so the MCP2515 sends acks to received data.
pinMode(CAN0_INT, INPUT);     // Configuring pin for /INT input
}


void loop(){

  if (millis()-print>1000){
    print=millis();
    SerialUSB.print("cancel = ");
    SerialUSB.print(!cancel);
    SerialUSB.print(" ");
    SerialUSB.print("setretard = ");
    SerialUSB.print(!setretard);
    SerialUSB.print(" ");
    SerialUSB.print("resaccel = ");
    SerialUSB.println(!resaccel);
    SerialUSB.print("radfanspeed = ");
    SerialUSB.print(radfanspeed);
    SerialUSB.print(" ");
    SerialUSB.print("auxradfanspeed = ");
    SerialUSB.println(auxfanspeed);
    SerialUSB.println("");
  }
  

  if(CAN0.checkReceive()==3){
    CAN0.readMsgBuf(&messID,&len, buf);

    //check cc position
    if(messID==0x38A&&bitRead(buf[2],2)==1&&bitRead(buf[2],3)==0){
      mainsw=bitRead(buf[1],0);

      if(mainsw==1&&bitRead(buf[1],1)==0)cancel=0;
      else if(mainsw==1&&bitRead(buf[1],1)==1)cancel=1;
      else cancel=1;
      
      if(bitRead(buf[1],2)==1||bitRead(buf[2],0)==1)setretard=0;
      else setretard=1;

      if(bitRead(buf[1],3)==1||bitRead(buf[2],1)==1)resaccel=0;
      else resaccel=1;

      digitalWrite(ccancel,cancel); //red/gray T15/7
      digitalWrite(csetretard,setretard); //red/yellow T15/9
      digitalWrite(cresaccel,resaccel); //blue T15/8
    } 

    //check ac status
    if(messID==0x5E0){
      acstatus=bitRead(buf[0],4);
      setfanspeed(); 
    }

    //check coolant temp
    if(messID==0x288){
      temp=((buf[1]*.75)-48);
      setfanspeed();
    } 
  }


  //set rad fan PWM
  time=millis(); 
  if((time-radtimeold)>=radfanspeed&&radfanPWM==LOW){
    radfanPWM=HIGH;
    radtimeold=time; 
  }
  else if((time-radtimeold)>=40-radfanspeed&&radfanPWM==HIGH){
    radfanPWM=LOW; 
    radtimeold=time; 
  }
  digitalWrite(radfan,radfanPWM);

  //set aux fan PWM
  if((time-auxtimeold)>=auxfanspeed&&auxfanPWM==LOW){
    auxfanPWM=HIGH;
    auxtimeold=time; 
  }
  else if((time-auxtimeold)>=40-auxfanspeed&&auxfanPWM==HIGH){
    auxfanPWM=LOW; 
    auxtimeold=time; 
  }
  digitalWrite(auxfan,auxfanPWM);
}
void setfanspeed(){
  //set fanspeed
  if(temp>temp1&&radfanspeed==off)radfanspeed=low; //temp between temp1 and temp2, low speed
  if(temp>temp2&&radfanspeed==low)radfanspeed=med,auxfanspeed=med; //temp above temp2, med speed
  if(temp>temp3&&radfanspeed==med)radfanspeed=high,auxfanspeed=high; //temp above temp3, high speed
  if(temp<(temp3-2)&&radfanspeed==high)radfanspeed=med, auxfanspeed=med; //temp cooling from temp3, return to med speed
  if(temp<(temp2-2)&&radfanspeed==med)radfanspeed=low, auxfanspeed=off; //temp cooling from temp2, return to low speed
  if(temp<(temp1-2)&&radfanspeed==low)radfanspeed=off, auxfanspeed=off; //temp cooling from temp1, turn off
  if(auxfanspeed==off&&acstatus==1)radfanspeed=low, auxfanspeed=low; //ac on turn on fan
}
