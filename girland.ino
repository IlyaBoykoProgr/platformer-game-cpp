#include "Adafruit_NeoPixel.h"
#define PIXELS 60
#define PIN 8
#define BRIGHTNESS 100
#define MODE 2

Adafruit_NeoPixel pix(PIXELS,PIN);

void fillRange(byte from, byte to, uint32_t color=pix.Color(0,0,0)){
  for(byte i=from; i<to; i++){
    pix.setPixelColor(i,color);
    pix.show();
  }
}

void setup(){
  pix.begin();
  pix.setBrightness(BRIGHTNESS);
  pix.show();
}

void loop(){
   uint32_t color = pix.Color(random(0,255),random(0,255),random(0,255));
   switch (MODE){
     case 0:
       for(byte i=0; i<PIXELS; i++){
         pix.setPixelColor(i,color);
         pix.show();
         delay(10);
       }
     break;
     case 1:{
       byte i=random(0,2);
       for(i; i<PIXELS; i+=2){
         pix.setPixelColor(i,color);
       }
       pix.show();
       delay(600);
     }
     break;
     case 2:
       for(byte j=0; j<PIXELS-4; j++){
         fillRange(j,j+5,color);
         delay(3);
         fillRange(j,j+5);
         delay(3);
       }
       for(byte j=PIXELS-5; j>0; j--){
         fillRange(j,j+5,color);
         delay(3);
         fillRange(j,j+5);
         delay(3);
       }
     break;
   }
}
