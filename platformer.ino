#include <Wire.h> 
#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7 );

// Количество позиций в ширину дисплея
const int FIELD_WIDTH = 16;
// Вероятность возникновения препятствия (5 из 10) 50%
const float BAR_PROBABILITY = 4; 

// Нажатая клавиша
int button;
#define BUTTON_NONE 0
#define BUTTON_RIGHT 1
#define BUTTON_UP 2
#define BUTTON_DOWN 3
#define BUTTON_LEFT 4
#define BUTTON_SELECT 5

// Состояния игры
int gameStatus;
#define MAIN_MENU 0 // Главное меню
#define IN_GAME 1 // Игра
#define PAUSE 2 // Пауза
#define ENDING 3 // Конец

// Отображаемые символы
char gameFields[32];     // Игровое поле
#define SPACE ' '  // Пустая клетка
#define BAR '\\'    // Препятствие
#define PLAYER '>' // Игрок

// Игровая скорость, чем меньше параметры тем выше скорость
int gameSpeed;
int SPEED_HIGH = 100;     // Скорость ускорения
int SPEED_NORMAL = 300;  // Изначальная скорость
int changeSpeed = 7000;  // Интервал изменения скорости
int metres = 0; //пройденные метры

long startGameTime;      // Время начала игры
long lastMovementTime;   // Последнее время обновления дисплея
long lastChangeSpeedTime;// Последнее время изменения скорости
long endGameTime;        // Время окончания игры
long bestGameTime;       // Лучшее время
int bestMetres = 0;      // наилучшее растояние
int topQueue = true;     // Параметр для алгоритма расстановки препятствий

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

// Функция начинает новую игру
void startGame()
{
  SPEED_NORMAL = 250; // Устанавливаем скорость
  // Сбрасываем таймеры
  startGameTime = millis();
  lastMovementTime = millis();
  lastChangeSpeedTime = millis();
  endGameTime = 0;
  // Очищаем игровое поле
  for (int i = 0; i < 2*FIELD_WIDTH; i++)
  {
     gameFields[i] = SPACE;
  }
  // Устанавливаем игрока в 1 позицию
  gameFields[0] = PLAYER;
  // Начинаем игру
  gameStatus = IN_GAME;
  // Выводим игровое поле
  printGameField();
}

// Функция выполняет движение игрового поля
void moveGameField()
{
  // Если врезались в препятствие, заканчиваем игру
  if (gameFields[0] == PLAYER && gameFields[1] == BAR ||
      gameFields[FIELD_WIDTH] == PLAYER && gameFields[FIELD_WIDTH+1] == BAR)
  {
    gameOver();
    return;
  } 
  // Вычисляем игровую позицию
  int playerPos = 0;
  if (gameFields[FIELD_WIDTH] == PLAYER)
  {
    playerPos = FIELD_WIDTH;
  }
  // Смещаем позиции
  for (int i = 0; i < FIELD_WIDTH*2; i++)
  {
    if (i != FIELD_WIDTH-1)
    {
      gameFields[i] = gameFields[i+1]; 
    }  
  } 
  gameFields[playerPos] = PLAYER;
  // Вычисляем количество препятствий на строках
  int topBarsCount = 0;
  int bottomBarsCount = 0;
  for (int i = 0; i < FIELD_WIDTH; i++)
  {
    if (gameFields[i] == BAR)
    {
       topBarsCount++; 
    }
  } 
  for (int i = FIELD_WIDTH; i < FIELD_WIDTH*2; i++)
  {
    if (gameFields[i] == BAR)
    {
       bottomBarsCount++; 
    }
  } 
  // Алгоритм установки препятствий в последних клетках дисплея
  // Нельзя допустить заведомо проигрышной ситуации
  // т.е. два препятствия без промежутка для маневра  
  // Также учитываем отсутствие длинных последовательностей препятствий
  if (topQueue)
  {
    // Принимаем решение об установке препятствия в нижней строке
    if (gameFields[FIELD_WIDTH-1] != BAR &&
      gameFields[FIELD_WIDTH-2] != BAR && 
      gameFields[FIELD_WIDTH-3] != BAR &&
      bottomBarsCount < FIELD_WIDTH/2 &&
      random(9) < BAR_PROBABILITY) 
    {
        gameFields[2*FIELD_WIDTH-1] = BAR;
    } else
    {
        gameFields[2*FIELD_WIDTH-1] = SPACE;
    }
    // Принимаем решение об установке препятствия в верхней строке
    if (gameFields[2*FIELD_WIDTH-1] != BAR && 
        gameFields[2*FIELD_WIDTH-2] != BAR && 
        gameFields[2*FIELD_WIDTH-3] != BAR && 
        topBarsCount < FIELD_WIDTH/2 &&
        random(9) < BAR_PROBABILITY) 
    {
        gameFields[FIELD_WIDTH-1] = BAR;
    } else
    {
        gameFields[FIELD_WIDTH-1] = SPACE;
    }
    topQueue = false;
  } else
  {
    // Принимаем решение об установке препятствия в верхней строке
    if (gameFields[2*FIELD_WIDTH-1] != BAR && 
        gameFields[2*FIELD_WIDTH-2] != BAR && 
        gameFields[2*FIELD_WIDTH-3] != BAR && 
        topBarsCount < FIELD_WIDTH/2 &&
        random(9) < BAR_PROBABILITY) 
    {
        gameFields[FIELD_WIDTH-1] = BAR;
    } else
    {
        gameFields[FIELD_WIDTH-1] = SPACE;
    }
    // Принимаем решение об установке препятствия в нижней строке
    if (gameFields[FIELD_WIDTH-1] != BAR &&
      gameFields[FIELD_WIDTH-2] != BAR && 
      gameFields[FIELD_WIDTH-3] != BAR &&
      bottomBarsCount < FIELD_WIDTH/2 &&
      random(9) < BAR_PROBABILITY) 
    {
        gameFields[2*FIELD_WIDTH-1] = BAR;
    } else
    {
        gameFields[2*FIELD_WIDTH-1] = SPACE;
    }
    topQueue = true; 
  }
  metres++;
}

// Функция завершения игры
void gameOver()
{
  gameStatus = ENDING;
  // Рассчитываем время игры
  endGameTime += (millis() - startGameTime);
  // Сравниваем с лучшим
  if (endGameTime > bestGameTime)
  {
     bestGameTime = endGameTime; 
  }
  if(metres>bestMetres){
    bestMetres=metres;
  }
  // Вычисляем позицию игрока
  int playerPos = 0;
  if (gameFields[FIELD_WIDTH] == PLAYER)
  {
    playerPos = FIELD_WIDTH;
  }  
  // Анимация проигрыша
  for(byte i=3;i>0;i--){
  lcd.setCursor(playerPos%FIELD_WIDTH, playerPos/FIELD_WIDTH);
  lcd.print(i);
  delay(1000);  
  }
  // Очищаем дисплей
  lcd.setCursor(0, 0);  
  lcd.print("                ");
  lcd.setCursor(0, 1);   
  lcd.print("                ");
  lcd.setCursor(0, 0);        
  // Выводим статистику
  lcd.print("Time:");
  lcd.print(endGameTime/1000);   
  lcd.print(" sec");     
  lcd.setCursor(0, 1);              
  lcd.print("Metres:");  
  lcd.print(metres);  
  lcd.print(" m"); 
  metres=0;
}

// Функция печати игрового поля
void printGameField()
{
  lcd.setCursor(0,0);
  for (int i = 0; i < FIELD_WIDTH*2; i++)
  {
     if(i==16)lcd.setCursor(0,1);
     lcd.print(gameFields[i]);    
  }
}

// Функция паузы
void pause()
{
  // Очищаем дисплей
  lcd.setCursor(0, 0);  
  lcd.print("                ");
  lcd.setCursor(0, 1);   
  lcd.print("                ");
  lcd.setCursor(0, 0);        
  // Выводим служебное сообщение 
  lcd.print("Paused");       
  lcd.setCursor(0, 1);              
  lcd.print("press SELECT"); 
  gameStatus = PAUSE;
  // Во время паузы не считаем игровое время
  endGameTime += (millis()-startGameTime);
}

void setup()
{
  gameStatus = MAIN_MENU;
  button = BUTTON_NONE;
  bestGameTime = 0;
  
  // Анимация первой загрузки
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);              
  lcd.print("press SELECT");      
  for(byte i=0;i<16;i++){
    lcd.setCursor(i,1);
    lcd.print(i%10);
    delay(100);
  }
}

void loop()
{
  // Вычисляем нажатую клавишу
  button = getPressedButton();

  switch (gameStatus)
  {
     case MAIN_MENU:
       // Из меню возможен переход на начало игры
       // по нажатию на SELECT
       if (button == BUTTON_SELECT)
       {
          startGame();
       } 
       if(button==BUTTON_LEFT){
              lcd.setCursor(0,0);
              lcd.print("Best time:");
              lcd.print(bestGameTime);
              lcd.print(" sec");
              lcd.setCursor(0,1);
              lcd.print("Best distance");
              lcd.print(bestMetres);
              lcd.print("m");
        }
       break;
     case IN_GAME:
       // Устанавливаем стандартную скорость
       gameSpeed = SPEED_NORMAL;
       switch (button)
       {
          // Ускорение
          case BUTTON_RIGHT:
            gameSpeed = SPEED_HIGH;
            break;
          // Пауза
          case BUTTON_LEFT:
            pause();
            break;
          // Перемещение в верхнюю строку
          case BUTTON_UP:
            if (gameFields[0] == BAR)
            {
               gameOver(); 
            } else
            {
              gameFields[0] = PLAYER;
              if (gameFields[FIELD_WIDTH] == PLAYER)
              {
                gameFields[FIELD_WIDTH] = SPACE;
              }
            }
            break;
          // Перемещение в нижнюю строку
          case BUTTON_DOWN:
            if (gameFields[FIELD_WIDTH] == BAR)
            {
               gameOver(); 
            } else
            {
              gameFields[FIELD_WIDTH] = PLAYER;
              if (gameFields[0] == PLAYER)
              {
                gameFields[0] = SPACE;
              }
            }
            break;
       }
       // Если прошло время отрисовки, рисуем поле
       if (millis() - lastMovementTime > gameSpeed)
       {
          lastMovementTime = millis();
          moveGameField();  
       }
       // Если прошло время изменения скорости, изменяем
       if (millis() - lastChangeSpeedTime > changeSpeed)
       {
          lastChangeSpeedTime = millis();
          SPEED_NORMAL -= 40;
          // Предельная скорость 
          if (SPEED_NORMAL < 50)
          {
            SPEED_NORMAL = 50;
            SPEED_HIGH = 50; 
          }
       }
       // Печатаем игровое поле, если не перешли в другой режим
       if (gameStatus == IN_GAME)
         printGameField();
       break;
     case PAUSE:
       // Продолжаем игру по нажатию на SELECT
       if (button == BUTTON_SELECT)
       {
         gameStatus = IN_GAME;
         startGameTime = millis();
       }  
       break;
     case ENDING:
       // По любому нажатию переходим в главное меню
       if (button != BUTTON_NONE)
       {
         lcd.setCursor(0, 0);  
         lcd.print("                ");
         lcd.setCursor(0, 1);   
         lcd.print("                ");
         lcd.setCursor(0, 0);         
         lcd.print("Play - SELECT");       
         lcd.setCursor(0, 1);              
         lcd.print("Best scores-LEFT");  
         gameStatus = MAIN_MENU;
       }  
       break;
  }
}
