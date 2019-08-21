#include "Adafruit_NeoPixel.h"
#define PIXELS 60 // count of pixels in the lent | кол-во пикселей в ленте
#define PIN 8 //pin with the adress lent | пин с адресной лентой
#define BRIGHTNESS 100 // you understood | яркость
#define MODE 5 // the mode | режим
/*  The random mode is | случайный режим задается 
    random(0,6)
*/
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
     case 0://snake | змейка
       for(byte i=0; i<PIXELS; i++){
         pix.setPixelColor(i,color);
         pix.show();
         delay(10);
       }
     break;
     case 1:{//double snake | двойная змейка
       byte i=random(0,2);
       for(i; i<PIXELS; i+=2){
         pix.setPixelColor(i,color);
       }
       pix.show();
       delay(600);
     }
     break;
     case 2://moving line | бегающая линия
       for(byte j=0; j<PIXELS-4; j++){
         fillRange(j,j+5,color);
         delay(3);
         fillRange(j,j+5);
         delay(3);
       }
       for(byte j=PIXELS-5; j>0; j--){
         fillRange(j,j+5,color);
         delay(5);
         fillRange(j,j+5);
       }
     break;
     case 3://pushers) | пихалки
       for(byte i=0; i<PIXELS; i++){
         for(byte j=0; j<i; j++){
           pix.setPixelColor(j,color);
           pix.show();
           delay(5);
           pix.setPixelColor(j,0,0,0);
           pix.show();
         }
         pix.setPixelColor(i,0,0,255);
       }
       pix.clear();
     break;
     case 4://beads | бусины
       for(byte i=PIXELS-1; i>0; i--){
         for(byte j=0; j<i; j++){
           pix.setPixelColor(j,color);
           pix.show();
           delay(5);
           pix.setPixelColor(j,0,0,0);
           pix.show();
         }
         pix.setPixelColor(i,color);
         color = pix.Color(random(0,255),random(0,255),random(0,255));
       }
     break;
     case 5:
       pix.setBrightness(5);
       pix.fill(color);
       for(byte i=5; i<=BRIGHTNESS; i++){
         pix.setBrightness(i);
         pix.show();
         delay(3);
       }
       for(byte i=BRIGHTNESS; i>4; i--){
         pix.setBrightness(i);
         pix.show();
         delay(3);
       }
       pix.setBrightness(BRIGHTNESS);
     break;
   }
   pix.clear();pix.show();
}
