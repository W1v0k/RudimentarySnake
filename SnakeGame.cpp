// SnakeGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//without classes, first broken attempt
#include <iostream>
#include <conio.h> // pt input; conio = console input/output
#include <Windows.h>
#include <ctime>

using namespace std;

#define ESCAPE 27

//COLORS
#define GREEN "\033[92m"
#define RESET "\033[0m" //alb
#define RED  "\033[91m" 
#define YELLOW  "\033[93m" 
#define CYAN "\033[96m"

bool gameOver;
const int width = 20; //dim Mapa
const int height = 20;
int x, y, fruitX, fruitY;//coordonate pt cap + fructe
int score;
int tailX[100], tailY[100];
int lenTail; //length of the tail
enum Direction { STOP=0, LEFT, RIGHT, UP, DOWN };
Direction dir;//directia sarpelui

void Setup()
{
    gameOver = false;
    dir = STOP; //nu se va misca
    x = width / 2; //pt a incepe in mijlocul mapei
    y = height / 2;
    fruitX = rand() % width; //pozitionam un fruct aleatoriu
    fruitY = rand() % height;
    score = 0;
}

void Draw()
{
    system("cls"); //clear the screen
    cout <<CYAN "Score: " << score << endl<<endl<<RESET;
    for (int i = 0; i <= width; ++i) //bordura de sus
    {
        cout <<YELLOW<< "#"<<RESET;
    }
    cout << endl;

    for (int i = 0; i < height; i++) // marginile mapei
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0 || j == width-1)
            {
                cout <<YELLOW<< "#"<<RESET;
            }
            if (i == y && j == x)
                cout <<GREEN<< "O"<<RESET;
            else if (i == fruitY && j == fruitX)
                cout <<RED<< "F"<<RESET;
            else
            {
                bool print = false;
                for (int k = 0; k < lenTail; k++)
                {
                    
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout <<GREEN<< "o"<<RESET;
                        print = true;
                    }
                    
                }
                if (!print)
                    cout << " ";
            }
        }
        cout << endl;
    }

    for (int i = 0; i <= width; ++i) //bordura de jos
    {
        cout <<YELLOW<< "#"<<RESET;
    }
    cout << endl;
    
}

void Input()
{
    if (_kbhit()) //kbhit daca este apasata o tasta
    {
        switch (_getch()) // _getch tasta care este apasata
        {
        case 'a':
            dir = LEFT;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        }
        
        if (_getch() == ESCAPE) //dorim sa iesim din joc
        {
            gameOver = true;
        }
    }
}

void Logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < lenTail; i++)
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
    case DOWN:
        y++;
        break;
    case UP:
        y--;
        break;
    default:
        break;
    }
   /* if ( x > width  || x < 0 || y > height || y < 0) //pt a muri la pereti
    {
        gameOver = true;
    }*/

    if (x >= width)
        x = 0;
    else if (x < 0)
        x = width - 1;

    if (y >= height)
    {
        y = 0;
    }
    else if (y < 0)
    {
        y = height-1;
    }
    for (int i = 0; i < lenTail; i++)
    {
        if (tailX[i] == x && tailY[i] == y)
        {
            gameOver = true;
        }
    }
    if (x == fruitX && y == fruitY)
    {
        score+=10;
        fruitX = rand() % width; //pozitionam un fruct aleatoriu
        fruitY = rand() % height;
        lenTail++;
    }
}
int main()
{
    srand(time(0));
    Setup();
    while (!gameOver)
    {
        Draw();
        Input();
        /*if (dir == LEFT || dir == RIGHT) //pt a se misca mai natural 
        {
            Sleep(5);
        }

        Sleep(100);

        if (dir == UP || dir == DOWN)
        {
            Sleep(60);
        }*/
        Logic();
        
        //Sleep(10); //pentru a incetini jocul
    }
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
