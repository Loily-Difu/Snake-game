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

}
