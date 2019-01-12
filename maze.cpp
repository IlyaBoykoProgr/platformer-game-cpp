/*
 programm made by IllyaBoyko https://github.com/IllyaBoykoProgr
 start programm by terminal: 'maze play' to play or 'maze help' to help
*/
#include<iostream>
#include<cstdlib>
#include<stdio.h>
#include<stdlib.h>
#include<fstream>
#ifdef WINDOWS
 #include<windows.h>
 #include<conio.h>
 #define WAIT(h) Sleep(h)
 #define CLEAR for(int i;i<100;i++)cout<<endl
#else
 #include<ctime>
 #include<termios.h>
 #include<unistd.h>
 #define WAIT(h) usleep(h)
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
#define HEIGHT 23//любое кол-во строк      |any count of strings(vertical)
#define WIDTH 79 //любое кол-во длины строки|any count of column(horisontal)
using namespace std;
bool deadend(int, int, int**, int, int); // Вспомогательная функция, определяет тупики
void visual(int**, int, int, int); // Изображение результата с помощью консольной графики
void mazemake(int**, int, int); // Собственно алгоритм
void win(int**,int,int);
void help(int,int);
int c=rand()%4;
unsigned int mazescomplete,steps,bug;
bool twoplayers;

class person{
 int x,y;
 public:
  void start(){y=3;x=3;}
  int getx(){return x;}
  int gety(){return y;}
  void up(int** maze,bool cheats){
  if(maze[x-1][y]==0&&!cheats)return;//if wall
  x--;
  steps++;}
  void down(int** maze,bool cheats){
  if(maze[x+1][y]==0&&!cheats)return;//if wall
  x++;
  steps++;}
  void left(int** maze,bool cheats){
  if(maze[x][y-1]==0&&!cheats)return;//if wall
  y--;
  steps++;}
  void right(int** maze,bool cheats){
  if(maze[x][y+1]==0&&!cheats)return;//if wall
  y++;
  steps++;}
};
person Iam,second;

int main(int argc, char *argv[]){
ifstream temp1("data",ios::binary);
if(temp1.is_open()==0){
 ofstream temp0("data",ios::binary);
 temp0<<sizeof('0')<<sizeof('0');
 temp0.close();
}
temp1>>bug>>mazescomplete>>steps;
temp1.close();
bool walkthroughwalls=0;
twoplayers=0;
int height = HEIGHT, width = WIDTH;
if(height%2==0)height++;
if(width%2==0)width++;
if(height<7)height=7;
if(width<13)width=13;
if(argc>1)switch(*argv[1]){
 case 'h':
  help(height,width);
  cout<<"maze version- version\nmaze play- play\nmaze cheat- cheats(walk through walls)\nmaze invisible- invisible walls\nmaze two- two players\n\nThanks for using terminal!\n";
  return 0;
 case 'v':
  cout<<"Version: 2.6\nBugs kill...\n";
  return 0;
 case 'c':
  walkthroughwalls=1;
  cout<<"You can walk through walls\n";
 case 'p':
 break;
 case 'i':
  c=4;
  cout<<"Walls are invisible\n";
 break;
 case 't':
  twoplayers=1;
  cout<<"2 players mode\n";
  break;
 default:
  cout<<"start programm using terminal!'./maze help' to help menu\n";
 return 0;
}
Iam.start(); second.start();
int** maze=new int*[height];
for(int i=0; i<height; i++) maze[i]=new int[width];
mazemake(maze, height, width);
visual(maze,height,width,c);
cout<<"\n press N to new maze.Press ? to see the help menu.Press Esc to quit\nTwo players mode- 2\n";
switch(getch()){
 case '2':
  twoplayers=1;
  break;
 case 'n':
 case 'N':
  main(argc,argv);
  return 0;
  break;
 case '?':
 case '/':
   help(height,width);
  break;
 case '':
  return 0;
  }
while(1){
 switch(getch()){
  case 'w':
 Iam.up(maze,walkthroughwalls);
 maze[Iam.getx()][Iam.gety()]=2;
 Iam.up(maze,walkthroughwalls);
 break;
  case 'a':
 Iam.left(maze,walkthroughwalls);
 maze[Iam.getx()][Iam.gety()]=2;
 Iam.left(maze,walkthroughwalls);
 break;
  case 's':
 Iam.down(maze,walkthroughwalls);
 maze[Iam.getx()][Iam.gety()]=2;
 Iam.down(maze,walkthroughwalls);
 break;
  case 'd':
 Iam.right(maze,walkthroughwalls);
 maze[Iam.getx()][Iam.gety()]=2;
 Iam.right(maze,walkthroughwalls);
 break;
  case '0':
 c=rand()%4;
 break;
  case '\E':
 main(argc,argv);
 return 0;
 break;
  case '?':
  case '/':
 help(height,width);
 getch();
 break;
 case 'i':
 second.up(maze,walkthroughwalls);
 maze[second.getx()][second.gety()]=2;
 second.up(maze,walkthroughwalls);
 break;
  case 'j':
 second.left(maze,walkthroughwalls);
 maze[second.getx()][second.gety()]=2;
 second.left(maze,walkthroughwalls);
 break;
  case 'k':
 second.down(maze,walkthroughwalls);
 maze[second.getx()][second.gety()]=2;
 second.down(maze,walkthroughwalls);
 break;
  case 'l':
 second.right(maze,walkthroughwalls);
 maze[second.getx()][second.gety()]=2;
 second.right(maze,walkthroughwalls);
 break;
 }
 visual(maze,height,width,c);
 maze[Iam.getx()][Iam.gety()]=2;
 if(Iam.getx()==height-2&&Iam.gety()==width-2){
  win(maze,height,width);
  cout<<"\nFIRST WON!!!\n\a";}
  if(second.getx()==height-2&&second.gety()==width-2){
  win(maze,height,width);
  cout<<"\nSECOND WON!!!\n\a";}
  if(Iam.getx()==height-2&&Iam.gety()==width-2 || second.getx()==height-2&&second.gety()==width-2){remove("data");
  mazescomplete++;
  ofstream temp2("data",ios::binary);
  temp2<<sizeof(mazescomplete)<<sizeof(steps);
  temp2.close();
  main(argc,argv);
  return 0;}
 }
}

void help(int height, int width){
 CLEAR;
   cout<<"\aThis game is a maze game.\n"<<
   "All you need is come to the exit(it's red).Press WASD(IJKL for 2nd player) to move a person.\n"<<
   "ESC-quit.Different colour-0.\n"<<
   "If you want to change size of maze, you need to find this in the code of programm:\n"<<
   "'#define HEIGHT\n#define WIDTH'\n"<<
   "What is what you'll read.\nThen rebuild the programm.\n"<<
   "Completed mazes now: ";
   ifstream temp4("data",ios::binary);
   temp4>>bug>>mazescomplete>>steps;
   cout<<mazescomplete<<"\nHow many steps you did: "<<steps<<'\n'
   <<"Size of current maze: "<<width<<"x"<<height<<'\n'<<'\a';
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

void win(int** maze, int height,int width){
 int cels=0;
 for(int x=0;x<height;x++)for(int y=0;y<width;y++)if(maze[x][y]==0)cels++;
 for(int i=0;i<height*width-cels;i++){
  int x=rand()%height,y=rand()%width;
  if(maze[x][y]==0){i--;continue;}
  maze[x][y]=0;
  visual(maze,height,width,rand()%4);
  WAIT(100);
 }
}

void visual(int** maze, int height, int width,int c){
 CLEAR;
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
		    if(i==height-2&&j==width-2){
		    #ifdef WINDOWS
		    cout<<"O";
		    #else
		    cout<<"\E[41m \E[0m";
		    #endif
		    continue;}
		    if(Iam.getx()==i && Iam.gety()==j){
		    #ifdef WINDOWS
		    cout<<"1";
		    #else
		    cout<<"\E[42m \E[0m";
		    #endif
		    continue;}
		    if(twoplayers && second.getx()==i && second.gety()==j){
		    #ifdef WINDOWS
		    cout<<"2";
		    #else
		    cout<<"\E[42m \E[0m";
		    #endif
		    continue;}
			switch(maze[i][j]){
				case 0:
				#ifdef WINDOWS
				if(c<4)cout<<"%";
				else cout<<" ";
				break;
				#else
				switch(c){
				 case 0:
				 cout<<"\E[43;33m";break;
				 case 1:
				 cout<<"\E[44;34m";break;
				 case 2:
				 cout<<"\E[45;35m";break;
				 case 3:
				 cout<<"\E[46;36m";break;
				 case 4:
				 cout<<"\E[40;30m";break;//invisible
				}
				cout<<"0\E[0m"; break;
				 #endif
				case 1: cout<<" "; break;
				case 2: cout<<"\E[47m*\E[0m";break;
			}
        }
		cout<<endl;
    }
   // cout<<"x:"<<Iam.getx()<<" y:"<<Iam.gety()<<'\n';
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
