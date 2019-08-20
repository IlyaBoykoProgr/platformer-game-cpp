#include "Adafruit_NeoPixel.h"
#define PIXELS 60
#define PIN 8
#define BRIGHTNESS 100
#define MODE 1

Adafruit_NeoPixel pix(PIXELS,PIN);

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
     case 1:
       int i=random(0,2);
       for(i; i<PIXELS; i+=2){
         pix.setPixelColor(i,color);
         pix.show();
         delay(10);
       }
     break;
     case 2:
       
     break;
   }
}
