#include "Adafruit_NeoPixel.h"

#define PIXELS 60 // count of pixels in the lent | кол-во пикселей в ленте
#define PIN 8 //pin with the adress lent | пин с адресной лентой
#define BRIGHTNESS 120 //<255!!!!
#define MODE -1 // the mode | режим
/*  The random mode is | случайный режим задается 
    -1
*/
Adafruit_NeoPixel pix(PIXELS,PIN);

void fillRange(byte from, byte to, uint32_t color=pix.Color(0,0,0)){
  for(byte i=from; i<to; i++){
    pix.setPixelColor(i,color);
  }
}

short mode;

void setup(){
  pix.begin();
  pix.setBrightness(BRIGHTNESS);
  pix.show();
  pinMode(A5,INPUT);
  randomSeed(analogRead(A5));
}

void loop(){
   uint32_t color = pix.Color(random(0,255),random(0,255),random(0,255));
   mode=MODE;
   if(mode<0)mode=random(9);
   if(Serial.available()){
     mode=Serial.read()-'0';
     Serial.print("The mode number ");
     Serial.print(mode);
     Serial.println(" accepted!");
   }
   switch (mode){
     case 0://snake | змейка
       for(byte i=0; i<PIXELS; i++){
         pix.setPixelColor(i,color);
         pix.show();
         delay(10);
       }
     break;
     case 1:{//double snake | двойная змейка
       uint32_t color2=pix.Color(random(0,255),random(0,255),random(0,255));
       for(byte i=0;i<PIXELS;i++){
         pix.setPixelColor(i,color);
         pix.setPixelColor(PIXELS-i,color2);
         pix.show();
         delay(20);
       }
     }
     break;
     case 2://moving line | бегающая линия
       for(byte j=0; j<PIXELS-4; j++){
         fillRange(j,j+5,color);
         pix.show();
         delay(10);
         fillRange(j,j+5);
       }
       for(byte j=PIXELS-5; j>0; j--){
         fillRange(j,j+5,color);
         pix.show();
         delay(10);
         fillRange(j,j+5);
       }
       pix.clear();
     break;
     case 3://pushers) | пихалки
       for(byte i=0; i<PIXELS; i++){
         for(byte j=0; j<i; j++){
           pix.setPixelColor(j,color);
           pix.show();
           delay(2);
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
       pix.clear();
     break;
     case 5:
       pix.setBrightness(5);
       pix.fill(color);
       for(byte i=10; i<=BRIGHTNESS; i++){
         pix.setBrightness(i);
         pix.show();
         delay(3);
       }
       for(byte i=BRIGHTNESS; i>11; i--){
         pix.setBrightness(i);
         pix.show();
         delay(3);
       }
       pix.clear();
       pix.setBrightness(BRIGHTNESS);
     break;
     case 6://rainbow | радуга
       for(long firstPixelHue = 0; firstPixelHue < 65536; firstPixelHue += 256) {
         for(int i=0; i<PIXELS; i++) {
           int pixelHue = firstPixelHue + (i * 65536L / PIXELS);
           pix.setPixelColor(i, pix.gamma32(pix.ColorHSV(pixelHue)));
         }
         pix.show();
       }
     break;
     case 7://random pixels| рандомные пиксели
       for(short i=0;i<PIXELS;i++){
         short randpix=rand()%PIXELS;
         if(pix.getPixelColor(randpix) !=0){i--;continue;}
         pix.setPixelColor(randpix,color);
         pix.show();
         delay(40);
       }
     break;
     default:
       Serial.println("No such mode(");
     break;
   }
   Serial.print(" the MODE ");
   Serial.print(mode);
   Serial.println(" played");
}
