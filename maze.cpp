/*
 programm made by IllyaBoyko https://github.com/IllyaBoykoProgr
 start programm via terminal: 'maze p' to play or 'maze h' to help
*/
#include<iostream>
#include<cstdlib>
#include<stdio.h>
#include<stdlib.h>
#ifdef WINDOWS
 #include<windows.h>
 #include<conio.h>
 #define WAIT(h); Sleep(h);
 #define CLEAR for(int i;i<100;i++)cout<<'\n'
#else
 #include<ctime>
 #include<termios.h>
 #include<unistd.h>
 #define WAIT(h); usleep(h);
 #define CLEAR system("clear");
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
#endif
#define HEIGHT rand()%30///любое кол-во строк      |any count of strings(vertical)
#define WIDTH HEIGHT*2 ///любое кол-во длины строки|any count of column(horisontal)
using namespace std;
bool deadend(int, int, int**, int, int); // Вспомогательная функция, определяет тупики
void visual(int**, int, int, int); // Изображение результата с помощью консольной графики
void mazemake(int**, int, int); // Собственно алгоритм
void win(int**,int,int,int);
void help();

class person{
 int x,y;
 public:
  void start(){y=3;x=3;}
  int getx(){return x;}
  int gety(){return y;}
  void up(int** maze){
  if(maze[x-1][y]==0)return;//if wall
  x-=2;}
  void down(int** maze){
  if(maze[x+1][y]==0)return;//if wall
  x+=2;}
  void left(int** maze){
  if(maze[x][y-1]==0)return;//if wall
  y-=2;}
  void right(int** maze){
  if(maze[x][y+1]==0)return;//if wall
  y+=2;}
};
person Iam;

int main(int argc, char *argv[]){
if(argc>1)switch(*argv[1]){
 case 'h':
  help();
  cout<<"maze v- version\nmaze p- play\n";
  return 0;
 case 'v':
  cout<<"Version: 2.2\nWindows and terminal update\n";
  return 0;
 case 'p':
 break;
 case '\0':
 default:
  cout<<"\nstart programm by terminal!./maze h' to help menu";
}
Iam.start();
setlocale(LC_ALL,"Russian");
int c=rand()%5;
srand((unsigned)time(NULL));
int height = HEIGHT, width = WIDTH;
if(height%2==0)height++;
if(width%2==0)width++;
if(height<6)height=7;
if(width<6)width=7;
int** maze = new int*[height];
for(int i = 0; i < height; i++) maze[i] = new int[width];
mazemake(maze, height, width);
visual(maze,height,width,c);
cout<<"\n press N to new maze.Press ? to see the help menu.\n";
switch(getch()){
 case 'n':
 case 'N':
  main(argc,argv);
  break;
 case '?':
   help();
  break;
  }
while(1){
 switch(getch()){
  case 'w':
  case 'ц':
 Iam.up(maze);
 break;
  case 'a':
  case 'ф':
 Iam.left(maze);
 break;
  case 's':
  case 'ы':
 Iam.down(maze);
 break;
  case 'd':
  case 'в':
 Iam.right(maze);
 break;
  case '0':
 c=rand()%5;
 break;
  case '\E':
 main(argc,argv);
 break;
 }
 visual(maze,height,width,c);
 if(Iam.getx()==height-2&&Iam.gety()==width-2){
  win(maze,height,width,c);
  main(argc,argv);
 }
}
}

void help(){
 CLEAR;
   cout<<"This game is a maze game.\n"<<
   "All you need is come to the exit(it's red).Press WASD to move your person.\n"<<
   "ESC-quit.Different colour-0.\n"<<
   "If you want to change size of maze, you need to find this in the code of programm:\n"<<
   "'#define HEIGHT\n#define WIDTH'\n"<<
   "What is what you'll read.\nThen rebuild the programm.\n";
}

bool deadend(int x, int y, int** maze, int height, int width){
	int a = 0;

	if(x != 1){
		if(maze[y][x-2] == 1)
			a+=1;
		}
	else a+=1;

	if(y != 1){
		if(maze[y-2][x] == 1)
			a+=1;
		}
	else a+=1;

	if(x != width-2){
		if(maze[y][x+2] == 1)
			a+=1;
		}
	else a+=1;

	if(y != height-2){
		if(maze[y+2][x] == 1)
			a+=1;
		}
	else a+=1;

	if(a == 4)
		return 1;
	return 0;
}

void win(int** maze, int height,int width,int c){
 for(int x=height-1;-1<x;x--){
   for(int y=width-1;-1<y;y--){
    if(maze[x][y]==1)continue;
    maze[x][y]=1;
    visual(maze,height,width,c);
    WAIT(110);
   }
  }
  cout<<"\nYOU WON!!!\n";
}

void visual(int** maze, int height, int width,int c){
 CLEAR;
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
		    if(i==height-2&&j==width-2){cout<<"\E[41m \E[0m";continue;}
		    if(Iam.getx()==i && Iam.gety()==j){
		    cout<<"\E[42m \E[0m";continue;}
			switch(maze[i][j]){
				case 0:
				#ifdef WINDOWS
				cout<<"%";break;
				#else
				switch(c){
				 case 0:
				 cout<<"\E[47m";break;
				 case 1:
				 cout<<"\E[43;33m";break;
				 case 2:
				 cout<<"\E[44;34m";break;
				 case 3:
				 cout<<"\E[45;35m";break;
				 case 4:
				 cout<<"\E[46;36m";break;
				}
				cout<<"0\E[0m"; break;
				 #endif
				case 1: cout<<" "; break;
			}
        }
		cout<<endl;
    }
    //cout<<Iam.getx()<<' '<<Iam.gety();
}

void mazemake(int** maze, int height, int width){
	int x, y, c, a;

	for(int i = 0; i < height; i++) // Массив заполняется землей-ноликами
		for(int j = 0; j < width; j++)
			maze[i][j] = 0;

	x = 3; y = 3; a = 0; // Точка приземления крота и счетчик
	while(a < 1000000){ // Да, простите, костыль, иначе есть как, но лень
		maze[y][x] = 1; a++;
		while(1){ // Бесконечный цикл, который прерывается только тупиком
			c = rand()%4; // Напоминаю, что крот прорывает
			switch(c){  // по две клетки в одном направлении за прыжок
				case 0: if(y != 1)
					if(maze[y-2][x] == 0){ // Вверх
                                        maze[y-1][x] = 1;
					maze[y-2][x] = 1;
					y-=2;
				}
				case 1: if(y != height-2)
					if(maze[y+2][x] == 0){ // Вниз
					maze[y+1][x] = 1;
					maze[y+2][x] = 1;
					y+=2;
				}
				case 2: if(x != 1)
					if(maze[y][x-2] == 0){ // Налево
					maze[y][x-1] = 1;
					maze[y][x-2] = 1;
					x-=2;
				}
				case 3: if(x != width-2)
					if(maze[y][x+2] == 0){ // Направо
					maze[y][x+1] = 1;
					maze[y][x+2] = 1;
					x+=2;
				}
			}
			if(deadend(x,y,maze,height,width))
			   break;
		}

		if(deadend(x,y,maze,height,width)) // Вытаскиваем крота из тупика
			do{
				x = 2*(rand()%((width-1)/2))+1;
				y = 2*(rand()%((height-1)/2))+1;
			}
			while(maze[y][x] != 1);
	}
}
