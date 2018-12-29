#define lamp1 12
#define lamp2 11
#define lamp3 9
#define lamp4 6
#define lamp5 4
#define lamp6 3
#define SLEEP 2000 //как долго играть режим
#define MODE 9 //режимы 0-9. Каждый подписан
byte lamps[6]={lamp1,lamp2,lamp3,lamp4,lamp5,lamp6};
int i,j;//вспомогательные не трогать

void on(byte lamp){
 digitalWrite(lamps[lamp],HIGH);
}

void off(byte lamp){
 digitalWrite(lamps[lamp],LOW);
}

void setup(){
 Serial.begin(9600);
 for(byte i=0;i<6;i++)pinMode(lamps[i],OUTPUT);
}

void loop(){
 byte mode=MODE;
 if(Serial.available())mode=Serial.read()-'0';//считываем цифру с порта если есть
 Serial.print("Playing ");
 Serial.print(mode);
 switch(mode){
  case 0://проверка подключения
   for(byte i=0;i<6;i++)on(i);
   delay(SLEEP);
  break;
  case 1://Новый Год
   for(byte i=0;i<6;i+=2){on(i);off(i+1);}
   delay(SLEEP/2);
   for(byte i=0;i<6;i+=2){on(i+1);off(i);}
   delay(SLEEP/2);
  break;
  case 2://бегунок в одну сторону
   for(byte i=0;i<6;i++){
    on(i);delay(SLEEP/12);
    off(i);delay(SLEEP/12);
   }
  break;
  case 3://бегунок в две стороны
   for(byte i=0;i<6;i++){
    on(i);delay(SLEEP/24);
    off(i);delay(SLEEP/24);
   }
   for(byte i=5;0<i;i--){
    on(i);delay(SLEEP/24);
    off(i);delay(SLEEP/24);
   }
  break;
  case 4://бегущая линия
   for(byte i=0;i<6;i++){on(i);delay(SLEEP/12);}
   for(byte i=0;i<6;i++){off(i);delay(SLEEP/12);}
  break;
  case 5://шкала
   for(byte i=0;i<6;i++){on(i);delay(SLEEP/12);}
   for(byte i=5;0<i;i--){off(i);delay(SLEEP/12);}
  break;
  case 6://бегунки внутрь
   i=0, j=5;
   while(i<3){
    on(i);on(j);
    delay(SLEEP/6);
    off(i);off(j);
    delay(SLEEP/6);
    i++;j--;
   }
  break;
  case 7://бегунки внутрь и к краям
   i=0, j=5;
   while(i<2){
    on(i);on(j);
    delay(SLEEP/12);
    off(i);off(j);
    delay(SLEEP/12);
    i++;j--;
   }
   i=2;j=3;
   while(i>0){
    on(i);on(j);
    delay(SLEEP/12);
    off(i);off(j);
    delay(SLEEP/12);
    i--;j++;
   }
  break;
  case 8://рандомное поведение светодиодов
   for(byte i=0;i<10;i++){
    digitalWrite(lamps[random(0,6)],random(0,2));
    delay(SLEEP/10);
   }
  break;
  case 9://красивый и сложный
   i=0, j=5;
   while(i<3){
    on(i);on(j);
    delay(SLEEP/12);
    i++;j--;
   }
   i=2;j=3;
   while(i>-1){
    off(i);off(j);
    delay(SLEEP/12);
    i--;j++;
   }
   i=2;j=3;
   while(-1<i){
    on(i);on(j);
    delay(SLEEP/12);
    i--;j++;
   }
   i=0, j=5;
   while(i<3){
    off(i);off(j);
    delay(SLEEP/12);
    i++;j--;
   }
  break;
  default:
   Serial.println("ENTER CORRECT MODE");
  break;
 }
 Serial.println(".Complete");
}
