/*
 programm made by IlyaBoyko https://github.com/IlyaBoykoProgr
 start programm by terminal: 'maze play' to play or 'maze help' to help
*/
#include<iostream>
#include<time.h>
#include<cstdlib>
#include<stdio.h>
#include<stdlib.h>
#include<fstream>
#ifdef _unix_
    #include<ctime>
    #include<termios.h>
    #include<unistd.h>
    #define WAIT(h) usleep(h)
    #define CLEAR system("clear");
    char getch(){
        struct termios oldt,newt;
        char ch;
        tcgetattr( STDIN_FILENO, &oldt );
        newt = oldt;
        newt.c_lflag &= ~( ICANON | ECHO );
        tcsetattr( STDIN_FILENO, TCSANOW, &newt );
        ch = getchar();
        tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
    return ch;
    }
#else
    #include<windows.h>
    HANDLE hCmd=GetStdHandle(STD_OUTPUT_HANDLE);
    #include<conio.h>
    #define WAIT(h) Sleep(h)
    #define CLEAR system("cls")//for(int i=0;i<20;i++)cout<<endl
#endif
#define HEIGHT 23//любое кол-во строк       |any count of strings(vertical)
#define WIDTH 79 //любое кол-во длины строки|any count of column(horisontal)
using namespace std;
bool deadend(int, int, int**, int, int); // Вспомогательная функция, определяет тупики
void visual(int**, int, int, int); // Изображение результата с помощью консольной графики
void mazemake(int**, int, int); // Собственно алгоритм
void help(int,int);
int c=1;
bool twoplayers=0;
bool walkthroughwalls=0;
int **maze;

class person{
public:
    int x,y;
    void start(){y=3;x=3;maze[x][y]=2;}
    void move(int ax,int ay){// a vector
        if(maze[x+ax][y+ay]==0&&!walkthroughwalls)return; //if wall
        x+= ax;
        y+= ay;
        maze[x][y]=2;
    }
    inline void up(){move(-1,0);}
    inline void down(){move(1,0);}
    inline void left(){move(0,-1);}
    inline void right(){move(0,1);}
};
person Iam,second;

int main(int argc, char *argv[]){
    srand(time(nullptr));
    int height = HEIGHT, width = WIDTH;
    if(height%2==0)height++;
    if(width%2==0)width++;
    if(height<7)height=7;
    if(width<13)width=13;
    if(argc>1)switch(*argv[1]){
    case 'h':
        help(height,width);
        cout<<"maze version- version\nmaze play- play\nmaze cheat- walkthrougwals(walk through walls)\nmaze invisible- invisible walls\nmaze two- two players\n\nThanks for using terminal!\n";
        return 0;
    case 'v':
        cout<<"Version: 3.1\nCode refactor\n";
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
    maze = new int*[height];
    for(int i=0;i<height;i++) maze[i]=new int[width];
gameLoop:
    Iam.start(); second.start();
    mazemake(maze, height, width);
    visual(maze,height,width,c);
    cout<<"N - new maze. ? - help menu. 0 -switch color.\nEsc - quit. 2 - 2nd player(IJKL)";
    switch(getch()){
    case '2':
        twoplayers=1;
        break;
    case 'n':
    case 'N':
        goto gameLoop;
        break;
    case '?':
    case '/':
        help(height,width);
        break;
    case '\E':
        return 0;
    }
    unsigned long long time = clock();
    while(1){
        char choice = getch();
        switch(choice){
        case 'w':Iam.up();break;
        case 'a':Iam.left();break;
        case 's':Iam.down();break;
        case 'd':Iam.right();break;
        case '0':
            c= (c+1)%4;
           break;
        case '\E':
            return 0;
            break;
        case 'i':second.up();break;
        case 'j':second.left();break;
        case 'k':second.down();break;
        case 'l':second.right();break;
        }
        visual(maze,height,width,c);
        if((Iam.x==height-2&&Iam.y==width-2)|| (second.x==height-2&&second.y==width-2)){
            cout<<"Win!                                                              \n";
            WAIT(1000);
            cout<<(clock()-time)/1000<<" seconds elapsed!                               ";
            WAIT(2000);
            goto gameLoop;
        }
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
   "Size of current maze: "<<width<<"x"<<height<<'\n'<<'\a';
}

bool deadend(int x, int y, int** maze, int height, int width){
    int a=0;
    if(x!=1 && maze[y][x-2]==1)
        a++;
    if(x==1)a++;

    if(y!=1 && maze[y-2][x]==1)
        a++;
    if(y==1)a++;

    if(x!=width-2 && maze[y][x+2] == 1)
        a++;
    if(x==width-2)a++;

    if(y!=height-2 && maze[y+2][x] == 1)
        a++;
    if(y==height-2)a++;

    return a==4;
}

void visual(int** maze, int height, int width,int c){
#if defined(WIN32) || defined(WIN64)
    cout.flush();
    SetConsoleCursorPosition(hCmd,(COORD){0,0});
#else
    CLEAR;
#endif
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            if(i==height-2&&j==width-2){
                #ifdef _unix_
                    cout<<"\E[41m \E[0m"
                #else
                    SetConsoleTextAttribute(hCmd,FOREGROUND_GREEN);
                    cout<<'O';
                #endif
                continue;
            }
            if(Iam.x==i && Iam.y==j){
                #ifdef _unix_
                    cout<<"\E[42m \E[0m";
                #else
                    SetConsoleTextAttribute(hCmd,FOREGROUND_RED);
                    cout<<((twoplayers&&Iam.x==second.x&&Iam.y==second.y)?'3':'1');
                #endif
                continue;
            }
            if(twoplayers && second.x==i && second.y==j){
                #ifdef _unix_
                    cout<<"\E[42m \E[0m";
                #else
                    SetConsoleTextAttribute(hCmd,FOREGROUND_RED);
                    cout<<'2';
                #endif
                continue;
            }
            switch(maze[i][j]){
            case 0:
                #ifdef _unix_
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
                #else
                switch(c){
                    case 0:SetConsoleTextAttribute(hCmd,FOREGROUND_RED);break;
                    case 1:SetConsoleTextAttribute(hCmd,FOREGROUND_GREEN);break;
                    case 2:SetConsoleTextAttribute(hCmd,FOREGROUND_RED|FOREGROUND_GREEN);break;
                    case 3:SetConsoleTextAttribute(hCmd,FOREGROUND_RED|FOREGROUND_BLUE);break;
                    default:SetConsoleTextAttribute(hCmd,0);break;
                }
                #endif
                cout<<'@';break;
            case 1:cout<<' ';break;
            case 2:
                #ifndef _unix_
                    SetConsoleTextAttribute(hCmd,FOREGROUND_INTENSITY);
                #endif
                cout<<'%';break;
            }
        }
        cout<<endl;
    }
   // cout<<"x:"<<Iam.x<<" y:"<<Iam.y<<'\n';
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
                }break;
                case 1: if(y != height-2)
                    if(maze[y+2][x] == 0){ // Вниз
                    maze[y+1][x] = 1;
                    maze[y+2][x] = 1;
                    y+=2;
                }
                break;
                case 2: if(x != 1)
                    if(maze[y][x-2] == 0){ // Налево
                    maze[y][x-1] = 1;
                    maze[y][x-2] = 1;
                    x-=2;
                }
                break;
                case 3: if(x != width-2)
                    if(maze[y][x+2] == 0){ // Направо
                    maze[y][x+1] = 1;
                    maze[y][x+2] = 1;
                    x+=2;
                }
                break;
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
