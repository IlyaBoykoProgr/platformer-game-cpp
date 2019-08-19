#include "Adafruit_NeoPixel.h"
#define PIXELS 60
#define PIN 8
#define BRIGHTNESS 100
#define MODE 0

Adafruit_NeoPixel pix(PIXELS,PIN);

void setup(){
  pix.begin();
  pix.setBrightness(BRIGHTNESS);
  pix.show();
}

void loop(){
   uint32_t color = pix.Color(random(100,255),random(100,255),random(100,255));
   switch (MODE){
     case 0:
       for(byte i=PIXELS-1; i>=0; i--){
         for(byte j=0; j<=i; j++){
           pix.setPixelColor(j, color);
           delay(100);
           pix.setPixelColor(j,0,0,0);
         }
         pix.setPixelColor(i,color);
         uint32_t color = pix.Color(random(100,255),random(100,255),random(100,255));
       }
     break;
   }
   
}
