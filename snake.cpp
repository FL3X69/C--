#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;
bool gameOver;
const int height = 20;
const int width = 20;
int x, y, fruitx, fruity, score;
int tailx[100], taily[100];
int ntail;
enum eDirection
{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};
eDirection dir;
void Setup()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitx = rand() % width;
    fruity = rand() % height;
    score = 0;
}
void Draw()
{
    int i, j, k;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 0});
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    for (i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            if (j == 0)
            {
                cout << "#";
            }
            if (i == y && j == x)
            {
                cout << "O";
            }
            else if (i == fruity && j == fruitx)
            {
                cout << "F";
            }
            else
            {
                bool print = false;
                for (k = 0; k < ntail; k++)
                {
                    if (tailx[k] == j && taily[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                {
                    cout << " ";
                }
            }
            if (j == width - 1)
            {
                cout << "#";
            }
        }
        cout << endl;
    }
    for (i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;
    cout << "Score: " << score << endl;
}
void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'w':
            dir = UP;
            break;
        case 'a':
            dir = LEFT;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'd':
            dir = RIGHT;
            break;
        default:
            gameOver = true;
            break;
        }
    }
}
void Logic()
{
    int prevx = tailx[0];
    int prevy = taily[0];
    int prev2x, prev2y;
    tailx[0] = x;
    taily[0] = y;
    for (int i = 1; i < ntail; i++)
    {
        prev2x = tailx[i];
        prev2y = taily[i];
        tailx[i] = prevx;
        taily[i] = prevy;
        prevx = prev2x;
        prevy = prev2y;
    }
    switch (dir)
    {
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    default:
        break;
    }
    if (x >= width)
        x = 0;
    else if (x < 0)
        x = width - 1;
    if (y >= height)
        y = 0;
    else if (y < 0)
        y = height - 1;
    for (int i = 0; i < ntail; i++)
    {
        if (tailx[i] == x && taily[i] == y)
        {
            gameOver = true;
        }
    }
    if (x == fruitx && y == fruity)
    {
        score += 10;
        fruitx = rand() % width;
        fruity = rand() % height;
        ntail++;
    }
}
int main()
{
    Setup();
    while (!gameOver)
    {
        Draw();
        if (dir == LEFT || dir == RIGHT)
        {
            Sleep(70);
        }
        if (dir == UP || dir == DOWN)
        {
            Sleep(90);
        }
        Input();
        Logic();
    }
    return 0;
}
