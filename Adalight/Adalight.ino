//----------------------НАСТРОЙКИ-----------------------
#define NUM_LEDS 59          // число светодиодов в ленте
#define PIN 8             // пин, к которому подключена лентаяркость
#define serialRate 115200  // скорость связи с ПК

int new_bright, new_bright_f;
unsigned long bright_timer;

uint8_t prefix[] = {'A', 'd', 'a'}, hi, lo, chk, i;  // кодовое слово Ada для связи
#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel strip(NUM_LEDS,PIN);

void setup(){
  srand(analogRead(A0));
  strip.begin();
  strip.show();
  Serial.begin(serialRate);
  Serial.print("Ada\n");     // Связаться с компом
  strip.setBrightness(255);
}

void loop(){
  for (i = 0; i < sizeof prefix; ++i) {
waitLoop: while (!Serial.available()) ;;
    if (prefix[i] == Serial.read()) continue;
    i = 0;
    goto waitLoop;
  }
  for(byte i=0;i<3;i++){while(!Serial.available());Serial.read();}
  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    int r,g,b;
    while(!Serial.available());
    r= Serial.read();
    while(!Serial.available());
    g= Serial.read();
    while(!Serial.available());
    b= Serial.read();
    strip.setPixelColor(i,r,g,b);
  }
  strip.show();  // записываем цвета в ленту
}
