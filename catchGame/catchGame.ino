#include <Adafruit_NeoPixel.h>

#define PIXELS 60 //lenth of led string
#define PIN 8 //pin of led string
#define BUTTON 3 //pin where button attached
#define WAIT delay(8);

Adafruit_NeoPixel pix(PIXELS,PIN);

void setup(){
  pix.begin();pix.show();
  pix.setBrightness(200);
  Serial.begin(9600);
}

bool clicked=false;
short clkPlace;
short point=PIXELS/2;
void checkClk(short where){
  if(digitalRead(BUTTON)==HIGH){
    clicked=true;
    clkPlace=where;
  }
  if(clicked&&point!=where){
    pix.fill(pix.Color(255,0,0),0,PIXELS);
    pix.show(); delay(500); pix.clear();
    pix.setPixelColor(point,0,255,0);
    clicked=false;
  }
}

void loop(){
while(!clicked){
  for(short p=0;p<PIXELS;p++){
    if(clicked&&clkPlace==point)break;
    if(p==point){pix.setPixelColor(p,0,255,0);WAIT;checkClk(p);continue;}
    pix.setPixelColor(p,0,0,255);
    pix.show(); WAIT; checkClk(p);
    pix.setPixelColor(p,0,0,0);
    pix.show(); WAIT; checkClk(p);
  }
  for(short p=PIXELS-1;p>-1;p--){
    if(clicked&&clkPlace==point)break;
    if(p==point){pix.setPixelColor(p,0,255,0);WAIT;checkClk(p);continue;}
    pix.setPixelColor(p,0,0,255);
    pix.show(); WAIT; checkClk(p);
    pix.setPixelColor(p,0,0,0);
    pix.show(); WAIT; checkClk(p);
  }
}clicked=false;
  if(clkPlace==point)//then...
  for(long firstPixelHue = 0; firstPixelHue < 65536; firstPixelHue += 512) {
    for(int i=0; i<PIXELS; i++) {
      int pixelHue = firstPixelHue + (i * 65536 / PIXELS);
      pix.setPixelColor(i, pix.gamma32(pix.ColorHSV(pixelHue)));
    }
    pix.show();
point= rand()%PIXELS;
  }
  Serial.print("Clicked on ");
  Serial.print(clkPlace);
  Serial.println(" pixel");
}


