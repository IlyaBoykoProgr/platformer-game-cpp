#include <TM1637.h>
#define CLK 9
#define DIO 10
#define Button 8

TM1637 dsp(CLK,DIO);


void setup(){
  dsp.init();
  dsp.set(3);
  pinMode(A0,OUTPUT);
  pinMode(A3,INPUT);
  pinMode(11,OUTPUT);digitalWrite(11,0);
  pinMode(12,OUTPUT);digitalWrite(12,1);
}

int test(){
  
  for(byte i=0;i<=1024;i++){
    analogWrite(A0,i);
    if(analogRead(A3)>0)return (i-analogRead(A3))*(270/38);
  }
  return NULL;
};

void loop(){
    while(digitalRead(Button)==0){}
    int om=test();
    analogWrite(A0,LOW);
    dsp.displayByte(_empty,_empty,_empty,_empty);
    (om==NULL)? dsp.displayByte(_N,_O,_N,_E) : dsp.displayInt(om);
    delay(300);
}
