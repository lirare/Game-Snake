#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;
bool gameOver;
const int width = 80;
const int height = 15;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirecton dir;

void Setup()
{
	 dir = STOP;
	 gameOver = false;
	 score = 0;
	 x = width / 2;
	 y = height / 2;
	 fruitX = (rand() % (width  - 1 )) +  1;
	 fruitY = (rand() % (height - 1 )) +  1;	
}
void Draw()
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0 , 0 });
	for (int i = 0; i < width; i++)
		cout << "_";
	cout << endl;
	
	for (int i = 0; i < height; i++) {
	 
		for (int j = 0; j < width; j++) {
			if (j == 0 || j == width - 1)
				cout << "|";
			else {
				if (i == y && j == x) {
					cout << "O";
				}
				else if (i == fruitY && j == fruitX) {
					cout << "X";
				}
				else if (nTail) {
					int p = 0;
					for (int k = 0; k < nTail; k++) {
						if (i == tailY[k] && j == tailX[k]) {
							cout << "o";
							p = 1;
						}
					}
					if (!p)
						cout << " ";
				}
			   else
				cout << " ";
            }
		}
		cout << endl;
			 
	}
	
	for (int i = 0; i < width; i++)
		cout << "-";
	cout << endl;
	cout << "Score : " << score << endl;
}
void Input()
{
	static char prevK;
    char currK;
	if (_kbhit())
	{
		currK = _getch();
		if (prevK != currK)
		switch (currK)
		{
		case 'q':
			if(prevK != 'd')
			dir = LEFT;
			break;
		case 'd':
			if (prevK != 'q')
			dir = RIGHT;
			break;
		case 'z':
			if (prevK != 's')
			dir = UP;
			break;
		case 's':
			if (prevK != 'z')
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
		}
		prevK = currK;
	}
}
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
	
	if (x >= width - 1) x = 1; else if (x <= 0) x = width - 2;
	if (y >= height) y = 0; else if (y < 0) y = height - 1;

	for (int i = 0; i < nTail; i++)
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;

	if (x == fruitX && y == fruitY)
	{
		score += 10;
		fruitX = (rand() % (width  - 1)) + 1 ;
		fruitY = (rand() % (height - 1)) + 1 ;
		nTail++;
	}
}
int main()
{
	srand(time(NULL));
	Setup();
	int speed;
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
		speed = 150 - 10 * nTail;
		if (speed > 0)
			Sleep(150 - 10 * nTail);
		else
			Sleep(0);
	}
	cout << "GAME OVER" << endl;
	system("pause");
	return 0;
}