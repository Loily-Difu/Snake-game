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
