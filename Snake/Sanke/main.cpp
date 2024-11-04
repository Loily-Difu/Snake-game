#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

bool gameOver;
const int width = 40;
const int height = 15;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;
int specialFruitX, specialFruitY;
bool specialFruitActive = false;
int specialFruitTimer = 0;
const int specialFruitDuration = 5; // thời gian thức ăn đặc biệt xuất hiện (giây)
int fruitsEaten = 0;
int specialFruitScore = 30; // Điểm cho thức ăn đặc biệt
bool speedBoostActive = false; // Biến kiểm soát trạng thái tăng tốc
int speed = 150; // Tốc độ di chuyển mặc định
// Hàm đổi màu chữ
void SetColor(int value)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), value);
}

// Hàm di chuyển con trỏ tới vị trí (x, y) trên console
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Hàm ẩn con trỏ chuột để không bị chớp nháy khi di chuyển rắn
void HideCursor()
{
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.bVisible = false;
    cursorInfo.dwSize = 1;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

// Hàm hiện con trỏ chuột khi cần
void ShowCursor()
{
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.bVisible = true;
    cursorInfo.dwSize = 1;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}
