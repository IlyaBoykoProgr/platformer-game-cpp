#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7 );

void setup(){
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Easy calculator");
}

// Нажатая клавиша
#define BUTTON_NONE 0
#define BUTTON_RIGHT 1
#define BUTTON_UP 2
#define BUTTON_DOWN 3
#define BUTTON_LEFT 4
#define BUTTON_SELECT 5

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

int firstnum=0,secondnum=0;int znak=0;
void loop(){
  lcd.setCursor(0,1);
  lcd.print("                ");
  lcd.setCursor(0,1);
  lcd.print(firstnum);
  switch(znak){
   case 0: lcd.print("+"); break;
   case 1: lcd.print("-"); break;
   case 2: lcd.print("/"); break;
   case 3: lcd.print("*"); break;
  }
  lcd.print(secondnum);
  lcd.print('=');
  switch(znak){
   case 0: lcd.print(firstnum+secondnum); break;
   case 1: lcd.print(firstnum-secondnum); break;
   case 2: lcd.print(firstnum/secondnum); break;
   case 3: lcd.print(firstnum*secondnum); break;
  }
  switch(getPressedButton()){
    case BUTTON_UP:
      firstnum++;
    break;
    case BUTTON_DOWN:
      firstnum--;
    break;
    case BUTTON_LEFT:
      secondnum--;
    break;
    case BUTTON_RIGHT:
      secondnum++;
    break;
    case BUTTON_SELECT:
      Serial.println("select");
      znak= (znak==3)? 0 : znak+1 ;
    break;
    case BUTTON_NONE:
      
    break;
  }
  delay(100);
}
