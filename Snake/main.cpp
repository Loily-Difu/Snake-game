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
void Setup()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
    HideCursor();
}

void Draw()
{
    gotoxy(0, 0); // Đặt con trỏ lên đầu để vẽ lại khung hình
    // Vẽ viền trên
    SetColor(14); // Màu vàng cho viền
    for (int i = 0; i < width + 2; i++)
        cout << "*";
    cout << endl;

    // Vẽ thân màn hình với rắn và quả
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
            {
                SetColor(14); // Màu vàng cho viền dọc
                cout << "*";
            }

            if (i == y && j == x)
            {
                SetColor(10); // Màu xanh lá cho đầu rắn
                cout << "O";
            }
            else if (i == fruitY && j == fruitX)
            {
                SetColor(12); // Màu đỏ cho quả
                cout << "o";
            }
            else if (specialFruitActive && i == specialFruitY && j == specialFruitX) // kiểm tra thức ăn đặc biệt
            {
                SetColor(13); // Màu tím cho thức ăn đặc biệt
                cout << "O";
            }
            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {

                        SetColor(10); // Màu xanh lá cho thân rắn
                        cout << "o";
                        print = true;

                    }
                }
                if (!print)
                {
                    SetColor(15); // Màu trắng cho nền
                    cout << " ";
                }
            }

            if (j == width - 1)
            {
                SetColor(14); // Màu vàng cho viền dọc
                cout << "*";
            }
        }
        cout << endl;
    }

    // Vẽ viền dưới
    for (int i = 0; i < width + 2; i++)
        cout << "*";
    cout << endl;

    SetColor(11); // Màu xanh dương nhạt cho chữ
    cout << "Diem: " << score << endl;
}
