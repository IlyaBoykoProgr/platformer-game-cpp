#include <iostream>//cout & cin
#ifdef linux
   #include <termios.h>//getch()
   #include <unistd.h>//sleep() & else...
   #include <sys/select.h> //kbhit()
   #include <fcntl.h>
   int kbhit(void){
   struct termios oldt, newt;
   int ch;
   int oldf;
   tcgetattr(STDIN_FILENO, &oldt);
   newt = oldt;
   newt.c_lflag &= ~(ICANON | ECHO);
   tcsetattr(STDIN_FILENO, TCSANOW, &newt);
   oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
   fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
   ch = getchar();
   tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
   fcntl(STDIN_FILENO, F_SETFL, oldf);
   if(ch != EOF){
    ungetc(ch, stdin);
    return 1;}
   return 0;}

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
#elif _WIN32
   #include<conio.h>
   #include<windows.h>
   #define CLEAR for(int i=0;i<100;i++)cout<<"\n";
   #define WAIT Sleep(1);
#else
#error Your platform not supported!
#endif
   using namespace std;

char table[4][10]={
{' ',' ',' ',' ',' ',' ',' ',' ',' '},
{' ',' ',' ',' ',' ',' ',' ',' ',' '},
{' ',' ',' ',' ',' ',' ',' ',' ',' '},
{' ',' ',' ',' ',' ',' ',' ',' ',' '}
};
char person='&';
char block='%';
int pos;//позиция персонажа
char Play[7]= "Play";//в меню когда не играл еще

// \x1b[ <аттрибуты вывода> m
// \x1b[0m  -сброс настроек вывода


void logic(){
table[0][0]=table[0][1];
table[0][1]=table[0][2];
table[0][2]=table[0][3];
table[0][3]=table[0][4];
table[0][4]=table[0][5];//уничтожение не нужного
table[0][5]=table[0][6];
table[0][6]=table[0][7];
table[0][7]=table[0][8];
table[0][8]=table[0][9];
table[0][9]=' ';
table[1][0]=table[1][1];
table[1][1]=table[1][2];
table[1][2]=table[1][3];
table[1][3]=table[1][4];
table[1][4]=table[1][5];
table[1][5]=table[1][6];//Перерисовка карты
table[1][6]=table[1][7];//справа налево.
table[1][7]=table[1][8];
table[1][8]=table[1][9];
table[1][9]=' ';
table[2][0]=table[2][1];
table[2][1]=table[2][2];
table[2][2]=table[2][3];
table[2][3]=table[2][4];
table[2][4]=table[2][5];
table[2][5]=table[2][6];//Перерисовка карты
table[2][6]=table[2][7];//справа налево.
table[2][7]=table[2][8];
table[2][8]=table[2][9];
table[2][9]=' ';
table[3][0]=table[3][1];
table[3][1]=table[3][2];
table[3][2]=table[3][3];
table[3][3]=table[3][4];
table[3][4]=table[3][5];
table[3][5]=table[3][6];//Перерисовка карты
table[3][6]=table[3][7];//справа налево.
table[3][7]=table[3][8];
table[3][8]=table[3][9];
table[3][9]=' ';
}//МНОГО

void showtable(){//показ текущей карты
cout<<"___________\n";//потолок
cout<<table[0][0]<<table[0][1]<<table[0][2]<<table[0][3]<<table[0][4]<<table[0][5]<<table[0][6]<<table[0][7]<<table[0][8]<<table[0][9]<<"\n";
cout<<table[1][0]<<table[1][1]<<table[1][2]<<table[1][3]<<table[1][4]<<table[1][5]<<table[1][6]<<table[1][7]<<table[1][8]<<table[1][9]<<"\n";
cout<<table[2][0]<<table[2][1]<<table[2][2]<<table[2][3]<<table[2][4]<<table[2][5]<<table[2][6]<<table[2][7]<<table[2][8]<<table[2][9]<<"\n";
cout<<table[3][0]<<table[3][1]<<table[3][2]<<table[3][3]<<table[3][4]<<table[3][5]<<table[3][6]<<table[3][7]<<table[3][8]<<table[3][9]<<"\n";
cout<<"==========\n";//это 'лава'
}//по другому мой комп не считывает.Прямо надо.

void options(){
cout<<"OPTIONS:\n background:\n(1.black,2.green,3.yellow,4.blue,5.white\n6.red,7.purple,8.light-blue)\n";

char otvet=getch();
switch(otvet){
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
 }//                                  настройки фона
CLEAR

cout<<"OPTIONS:\n foreground:\n(1.black,2.green,3.yellow,4.blue,5.white\n6.red,7.purple,8.light-blue)\n";

otvet=getch();
switch(otvet){
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
 }//                                  настройки букв

CLEAR
cout<<"OPTIONS:\n your persone:\n(enter symbol)\n";
cin>>person;
WAIT
//                                   настройка персонажа

CLEAR
cout<<"OPTIONS:\n blocks:\n(enter symbol)\n";
cin>>block;
WAIT
//                                  настройка формы блоков
}

void play(){//                        ИГРА
cout<<"3\n";        //|
cout<<"2\n";        //|красивое
cout<<"1\n";        //|начало       
cout<<"start!!!\n"; //|
WAIT           //|
CLEAR      //|

table[3][0]=block;table[3][1]=block;table[3][2]=block;table[3][3]=block; //
table[3][4]=block;table[3][5]=block;table[3][6]=block;table[3][7]=block; //начало карты
table[3][8]=block;table[3][9]=block;                                     //

bool lose=false;//в ином случае проиграешь
pos=0;

while(lose==false){

table[pos][0]=person;//появление персонажа

WAIT
CLEAR//основная логика
showtable();
if(table[pos][1]==block){lose=true;}//врезался-умер
logic();

int flat=rand()%3+1; //|где блок ставить?
table[flat][9]=block;//|а теперь ставим.

if(table[pos+1][0]==' '){pos++;}//падаем
else if(kbhit()){pos--;}//прыг!(только не по воздуху)

if(pos==3){lose=true;}//падаем-умираем
}
CLEAR
showtable();
cout<<"\nGAME OVER!!!\n";//когда все кончено...
for(int i; i<5;i++)getch();
Play[0]='R';Play[1]='e';Play[2]='s';Play[3]='p';Play[4]='a';Play[5]='w';Play[6]='n';//это пишем в меню когда проиграл вместо плей
}

int main(){
CLEAR	
cout<<"MENU:\n1."<<Play<<"\n2.Options\n3.Help\n";
char num=getch();
switch(num){
case '1':
 CLEAR play();break;
case '2':
 CLEAR options();break;
case '3':
 CLEAR cout<<"HELP:\nThis game is 'platformer'.You need jump trough the abysses & don't birn into a block.Any key to jump, but not keys with numbers.\n";
getch();break;
default:
main();
 break;
 }
main();
}