#include<iostream>
#include<cstdlib>
#include<ctime>
#include<stdio.h>
#include<termios.h>
#include<unistd.h>
#define HEIGHT 50 ///любое кол-во строк
#define WIDTH 100 ///любое кол-во длины строки
#define WALL '0' ///значок стены
using namespace std;
bool deadend(int, int, int**, int, int); // Вспомогательная функция, определяет тупики
void visual(int**, int, int); // Изображение результата с помощью консольной графики
void mazemake(int**, int, int); // Собственно алгоритм


class person{
 int x,y;
 bool iswall(int X, int Y,int** maze){
 if(maze[X][Y]==WALL)return 1;
 else return 0;
 }
 public:
  person(){start();}
  void start(){y=1;x=HEIGHT-3;}
  int getx(){return x;}
  int gety(){return y;}
  void up(int** maze){
  x--;y++;
  if(iswall(x,y,maze)){x++;y--;}
  }
  void down(int** maze){
  x++;y--;
  if(iswall(x,y,maze)){x--;y++;}
  }
  void left(int** maze){
  y--;x--;
  if(iswall(x,y,maze)){y++;}
  }
  void right(int** maze){
  y++;
  if(iswall(x,y,maze)){y--;x--;}
  }
};
person Iam;

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

int main(){
Iam.start();
srand((unsigned)time(NULL));
int height = HEIGHT, width = WIDTH;
if(height%2==0)height--;
if(width%2==0)width--;
int** maze = new int*[height];
for(int i = 0; i < height; i++) maze[i] = new int[width];
mazemake(maze, height, width);
visual(maze,height,width);
if(getch()=='\E'&&getch()=='['&&getch()=='1'&&getch()=='5'&&getch()=='~')main();
while(1){
 switch(getch()){
  case 'w':
 Iam.up(maze);
  case 'a':
 Iam.left(maze);
  case 's':
 Iam.down(maze);
  case 'd':
 Iam.right(maze);
 }
 visual(maze,height,width);
 if(Iam.getx()==1&&Iam.gety()==1){
 cout<<"\nYOU WON!!!\nPRESS ANY KEY TO RESTART...";
 getch();
 main();
 }
}
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

void visual(int** maze, int height, int width){
 system("clear");
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
		    if(i==1&&j==1){cout<<"\E[41m \E[0m";continue;}
		    if(Iam.getx()==i && Iam.gety()==j){
		    cout<<"\E[42m \E[0m";continue;}
			switch(maze[i][j]){
				case 0: cout<<"\E[47m"<<WALL<<"\E[0m"; break;
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
