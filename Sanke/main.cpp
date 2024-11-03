#include <iostream>
#include<conio.h>>
#include<windows.h>
#define MAX 100
using namespace std;
struct _POINT
{
    int x,y;
};

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

class SNAKE
{
private:
    _POINT Body[MAX];
    int leng;
public:
    SNAKE()
    {
        leng=6;
        Body[0].x=6;
        Body[0].y=5;
        Body[1].x=5;
        Body[1].y=5;
        Body[2].x=5;
        Body[2].y=4;
        Body[3].x=5;
        Body[3].y=3;
        Body[4].x=4;
        Body[4].y=3;
        Body[5].x=3;
        Body[5].y=3;
    }
    void DRAW()
    {
        for(int i=0; i<leng; i++)
        {
            gotoxy(Body[i].x,Body[i].y);
            cout<<"X";
        }
    }
    void Go (int dir)
    {
        for (int i = leng -1; i > 0 ; i--)
            Body [i] = Body [i-1];
        if (dir == 1) Body [0].x = Body [0].x + 1;
        else if (dir == 3) Body [0].x = Body [0].x -1;
        else if (dir == 2) Body [0].y = Body [0].y + 1;
        else if (dir == 4) Body [0].y = Body [0].y - 1;
    }
};
int main()
{
    SNAKE s;
    int dir=1;
    while(1){
        if(kbhit()){
            char c=getch();
            if(c=='a') dir=3;
            else if(c=='w') dir=4;
            else if(c=='s') dir=2;
            else if(c=='d') dir=1;
            else if(c=='q') return 0;
        }
       s.DRAW();
       Sleep(100);
       system("cls");
       s.Go(dir);
    }


    return 0;
}
