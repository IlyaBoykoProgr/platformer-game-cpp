#include <Arduino.h>

// Нажатая клавиша
#define BUTTON_NONE 0
#define BUTTON_RIGHT 1
#define BUTTON_UP 2
#define BUTTON_DOWN 3
#define BUTTON_LEFT 4
#define BUTTON_SELECT 5
int button= BUTTON_NONE;

// Функция возвращает какая кнопка была нажата
int getPressedButton()
{
  int buttonValue = analogRead(0);
  if (buttonValue < 100) {
    return BUTTON_RIGHT;
  }
  else if (buttonValue < 200) {
    return BUTTON_UP;
  }
  else if (buttonValue < 400){
    return BUTTON_DOWN;
  }
  else if (buttonValue < 600){
    return BUTTON_LEFT;
  }
  else if (buttonValue < 800){
    return BUTTON_SELECT;
  }
  return BUTTON_NONE;
}

void gameOverSound(){
  for(byte i=120; i>100; i-=6){
    tone(13,i,250);
    delay(250);
  }
  noTone(13);
}
void gameOnSound(){
  pinMode(13,OUTPUT);
  for(byte i=70; i<100; i+=8){
    tone(13,i,150);
    delay(150);
  }
  noTone(13);
}

void personMoveSound(){
    tone(13,300,100);
  noTone(13);
}
