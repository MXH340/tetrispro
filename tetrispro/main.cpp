#include<SFML/Graphics.hpp>
#include<time.h>
//#include"tetris.h"
using namespace sf;

struct Point
{
	int x, y;
};
Point a[4];
Point b[4];
const int SIZE = 18;
const int WIDTH = 10;
const int HEIGHT = 20;
int figures[7][4] =
{
	1,3,5,7, // I
	2,4,5,7, // Z
	3,5,4,6, // S
	3,5,4,7, // T
	2,3,5,7, // L
	3,5,7,6, // J
	2,3,4,5, // O
};
int map[HEIGHT][WIDTH] = { 0 };
bool tetrisExist = 0;
//int colorNum = 1;
float timer = 0, delay = 0.3;

void GameInit();
void Draw();
void CreateTetris();
void ControlTetris(Event e);
void Rotate();
void Move(int dx);
void Tick(float time);

Texture t;
Sprite s;
RenderWindow window(VideoMode(320, 480), "The Game");

int main()
{
	Clock clock;
	GameInit();
	while (window.isOpen())
	{
		Event e;
		if (!tetrisExist)
			CreateTetris();
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		Tick(time);
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
			{
				window.close();
			}
			else if (e.type == Event::KeyPressed)
			{
				ControlTetris(e);
			}
		}
		Draw();
	}
	return 0;
}

//��ʼ���ز�
void GameInit()
{
	t.loadFromFile("tiles.png");
	s = Sprite(t);
	s.setTextureRect(IntRect(0, 0, SIZE, SIZE));
}

//��ͼ
void Draw()
{
	window.clear(Color::White);
	for (int i = 0; i < 4; i++)
	{
		s.setPosition(a[i].x * 18, a[i].y * 18);
		window.draw(s);
	}
	window.display();
}

void CreateTetris()
{
	int n = 3;
	for (int i = 0; i < 4; i++)
	{
		a[i].x = figures[n][i] % 2 + 4;
		a[i].y = figures[n][i] / 2;
	}
	tetrisExist = 1;
}

void ControlTetris(Event e)
{
	if (e.key.code == Keyboard::Up)
		Rotate();
	else if (e.key.code == Keyboard::Left)
		Move(-1);
	else if (e.key.code == Keyboard::Right)
		Move(1);
}

void Rotate()
{

	Point p = a[1];
	for (int i = 0; i < 4; i++)
	{
		int x = a[i].y - p.y;
		int y = a[i].x - p.x;
		a[i].x = p.x - x;
		a[i].y = p.y + y;
	}
}

void Move(int dx)
{
	for (int i = 0; i < 4; i++)
	{
		a[i].x += dx;
	}
}

void Tick(float time)
{
	timer += time;
	if (timer > delay)
	{
		for (int i = 0; i < 4; i++)
			a[i].y += 1;
		timer = 0;
	}
}