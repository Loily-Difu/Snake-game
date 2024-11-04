void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            if (dir != RIGHT) dir = LEFT; // Không cho di chuyển ngược lại
            break;
        case 'd':
            if (dir != LEFT) dir = RIGHT; // Không cho di chuyển ngược lại
            break;
        case 'w':
            if (dir != DOWN) dir = UP; // Không cho di chuyển ngược lại
            break;
        case 's':
            if (dir != UP) dir = DOWN; // Không cho di chuyển ngược lại
            break;
        case 'x':
            gameOver = true;
            break;
        case 'e': // Phím để bật/tắt tăng tốc
            speedBoostActive = !speedBoostActive; // Đảo ngược trạng thái tăng tốc
            speed = speedBoostActive ? 80 : 150; // Giảm tốc độ khi bật tăng tốc
            break;
        }
    }
}
