#include <iostream>//cout & cin
#include <cstdlib>
#include <stdio.h>
#ifdef linux
   #include <unistd.h>//sleep() & else...
   #include <sys/select.h> //kbhit()
   #include <fcntl.h>
   #include <termios.h>
   
   void nonblock(int state)
   {
    struct termios ttystate;
    tcgetattr(STDIN_FILENO, &ttystate);

    if ( state == 1)
    {
        ttystate.c_lflag &= (~ICANON & ~ECHO); //Not display character
        ttystate.c_cc[VMIN] = 1;
    }
    else if (state == 0)
    {
        ttystate.c_lflag |= ICANON;
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
   }
  
   int kbhit()
   {nonblock(1);
   struct timeval tv;
   fd_set fds;
   tv.tv_sec = 0;
   tv.tv_usec = 0;
   FD_ZERO(&fds);
   FD_SET(STDIN_FILENO, &fds);
   select(STDIN_FILENO+1, &fds, NULL, NULL, &tv);
   return FD_ISSET(STDIN_FILENO, &fds);
   nonblock(0);
   }

   char getch(){
   struct termios oldt,newt;
   int ch;
   tcgetattr( STDIN_FILENO, &oldt );
   newt = oldt;
   newt.c_lflag &= ~( ICANON | ECHO );
   tcsetattr( STDIN_FILENO, TCSANOW, &newt );
   ch = getchar();
   tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
   return ch;}
   
   #define WAIT sleep(1);
   #define CLEAR system("clear");
#elif WINDOWS
   #include<conio.h>
   #include<windows.h>
   #define WAIT Sleep(500);
   #define CLEAR for(int i=0;i<30;i++)cout<<"\n";
#else
#error Your platform not supported!
#endif
using namespace std;

char table[5][10]={
{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}
};
char person='L';
char block='Z';
char Play[7]= "Play";//в меню когда не играл еще

// \x1b[ <аттрибуты вывода> m
// \x1b[0m  -сброс настроек вывода


void logic(){
for(int i=0; i<6; i++){
table[i][0]=table[i][1];
table[i][1]=table[i][2];
table[i][2]=table[i][3];
table[i][3]=table[i][4];
table[i][4]=table[i][5];//уничтожение не нужного
table[i][5]=table[i][6];
table[i][6]=table[i][7];
table[i][7]=table[i][8];
table[i][8]=table[i][9];
table[i][9]=' ';}
}//МНОГО

void showtable(){//показ текущей карты
CLEAR
cout<<"___________\n";//потолок
cout<<table[0][0]<<table[0][1]<<table[0][2]<<table[0][3]<<table[0][4]<<table[0][5]<<table[0][6]<<table[0][7]<<table[0][8]<<table[0][9]<<"\n";
cout<<table[1][0]<<table[1][1]<<table[1][2]<<table[1][3]<<table[1][4]<<table[1][5]<<table[1][6]<<table[1][7]<<table[1][8]<<table[1][9]<<"\n";
cout<<table[2][0]<<table[2][1]<<table[2][2]<<table[2][3]<<table[2][4]<<table[2][5]<<table[2][6]<<table[2][7]<<table[2][8]<<table[2][9]<<"\n";
cout<<table[3][0]<<table[3][1]<<table[3][2]<<table[3][3]<<table[3][4]<<table[3][5]<<table[3][6]<<table[3][7]<<table[3][8]<<table[3][9]<<"\n";
cout<<table[4][0]<<table[4][1]<<table[4][2]<<table[4][3]<<table[4][4]<<table[4][5]<<table[4][6]<<table[4][7]<<table[4][8]<<table[4][9]<<"\n";
cout<<"==========\n";//это 'лава'
}//по другому мой комп не считывает.Прямо надо.

void options(){
cout<<"OPTIONS:\n1.background\n2.foreground\n3.your person\n4.blocks\n\nwarning: 1&2 not supported on Windows!";
char t=getch();
CLEAR
if(t=='1'){

cout<<"OPTIONS:\n background:\n(1.black,2.green,3.yellow,4.blue,5.white\n6.red,7.purple,8.light-blue)\n";
//                                  настройки фона
char answer=getch();
switch(answer){
case '1':
 cout<<"\x1b[40m";break;
case '2':
 cout<<"\x1b[42m";break;
case '3':
 cout<<"\x1b[43m";break;
case '4':
 cout<<"\x1b[44m";break;
case '5':
 cout<<"\x1b[47;30m";break;
case '6':
 cout<<"\x1b[41m";break;
case '7':
 cout<<"\x1b[45m";break;
case '8':
 cout<<"\x1b[46m";break;
default:
CLEAR
cout<<"ERROR";
WAIT
return;
 }
 
 }else if(t=='2'){

cout<<"OPTIONS:\n foreground:\n(1.black,2.green,3.yellow,4.blue,5.white\n6.red,7.purple,8.light-blue)\n";
 //                                  настройки букв
char answer=getch();
switch(answer){
case '1':
 cout<<"\x1b[30m";break;
case '2':
 cout<<"\x1b[32m";break;
case '3':
 cout<<"\x1b[33m";break;
case '4':
 cout<<"\x1b[34m";break;
case '5':
 cout<<"\x1b[37m";break;
case '6':
 cout<<"\x1b[31m";break;
case '7':
 cout<<"\x1b[35m";break;
case '8':
 cout<<"\x1b[36m";break;
default:
CLEAR
cout<<"ERROR";
WAIT
return;
 }//                                   настройка персонажа
}else if(t=='3'){
cout<<"OPTIONS:\n your persone:\n(enter symbol)\n";
person=getchar();
WAIT
}else if(t=='4'){
cout<<"OPTIONS:\n blocks:\n(enter symbol)\n";
block=getchar();
WAIT //                                  настройка формы блоков
}else{
options();
return;}
}

void play(){//                     '''''''   ИГРА   ''''''''  
cout<<"start!!!\n";
WAIT
CLEAR

table[4][0]=block;table[4][1]=block;table[4][2]=block;table[4][3]=block; //
table[4][4]=block;table[4][5]=block;table[4][6]=block;table[4][7]=block; //начало карты
table[4][8]=block;table[4][9]=block;                                     //

int pos=0;//начальная позиция
int score=0;//наш будущий счет

while(1){
table[pos][0]=person;//появление персонажа

WAIT //чуть-чуть ждем
showtable();//показ карты

int flat=rand()%4+1; //где блок ставить?
table[flat][9]=block;//а теперь ставим.

if(table[pos][1]==block)break;//врезался-умер
if(pos==3)break;//падаем-умираем
score++;//здесь мы прошли блок,счет растет.Можно играть дальше

if(table[pos+1][0]==' ')pos++;//падаем
else if(kbhit()){pos--;score++;}//прыг!.пусть за прыжок дополнительные очки
logic(); //перерисовка
}
cout<<"\nGAME OVER!\npress 'q' to exit.\n";//когда все кончено...
while(!(getch()=='q'));
Play[0]='R';Play[1]='e';Play[2]='s';Play[3]='p';Play[4]='a';Play[5]='w';Play[6]='n';
cout<<"Your score is "<<score<<'\n';//cчет возвращаем
WAIT
}

int main(){
CLEAR	
cout<<"PLATFORMER:\n\nMENU:\n1."<<Play<<"\n2.Options\n3.Help\n4.Exit...\n";
char num=getch();
CLEAR
if(num=='1'){ 
   play();
}else if(num=='2'){
   options();
}else if(num=='3'){
   cout<<"HELP:\nThis game is 'platformer'.You need jump trough the abysses & don't birn into a block.Space to jump.\n\nA fact:'Escape'to exit!\nP.S. Programm made by ilya https://github.com/IlyaBoykoProgr";
   getch(); 
}else if(num=='4'||num=='\E')return 0;
main();
}