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
void Logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }

    // Kiểm tra va chạm với tường
    //if (x >= width || x < 0 || y >= height || y < 0)
    //gameOver = true;
    // Kiểm tra nếu rắn đi xuyên tường
    if (x >= width) x = 0; // Đi ra bên phải sẽ trở về bên trái
    else if (x < 0) x = width - 1; // Đi ra bên trái sẽ trở về bên phải
    if (y >= height) y = 0; // Đi ra dưới cùng sẽ trở về trên cùng
    else if (y < 0) y = height - 1; // Đi ra trên cùng sẽ trở về dưới cùng

    // Kiểm tra va chạm với đuôi rắn
    for (int i = 1; i < nTail; i++)
    {
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;
    }
    // Kiểm tra ăn trái cây
    if (x == fruitX && y == fruitY)
    {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++; // Tăng kích thước đuôi
        fruitsEaten++; // Tăng biến đếm số trái cây đã ăn

        // Kiểm tra ăn đủ 5 trái cây để tạo thức ăn đặc biệt
        if (fruitsEaten == 5) // Sau khi ăn 5 trái cây
        {
            specialFruitX = rand() % width;
            specialFruitY = rand() % height;
            specialFruitActive = true;
            specialFruitTimer = 0; // reset timer
            specialFruitScore = 30; // Reset điểm cho thức ăn đặc biệt
            fruitsEaten = 0; // Reset số trái cây đã ăn
        }
    }
    // Xử lý bộ đếm thời gian thức ăn đặc biệt
    if (specialFruitActive)
    {
        specialFruitTimer++;
        if (specialFruitTimer >= specialFruitDuration * 15) // Điều chỉnh timer cho phù hợp với Sleep(150) trong Draw
        {
            specialFruitActive = false; // tắt thức ăn đặc biệt sau thời gian
        }
        else if (specialFruitTimer % 10 == 0) // Giảm điểm số sau mỗi giây
        {
            specialFruitScore -= 5; // Giảm 5 điểm mỗi giây (hoặc giá trị bạn muốn)
            if (specialFruitScore < 0)
                specialFruitScore = 0; // Đảm bảo điểm không âm
        }
    }
        // Kiểm tra va chạm với thức ăn đặc biệt
    if (specialFruitActive && x == specialFruitX && y == specialFruitY)
    {
        score += specialFruitScore; // Điểm cho thức ăn đặc biệt
        specialFruitActive = false; // Tắt thức ăn đặc biệt sau khi ăn
    }

}
