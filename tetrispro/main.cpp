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
int colorNum = 1;
float timer = 0, delay = 0.3f;

void GameInit();
void Draw();
void CreateTetris();
void ControlTetris(Event e);
void Rotate();
void Move(int dx);
void Tick(float time);
bool Check();
void CheckLines();

Texture t1, t2, t3;
Sprite s, background, frame;
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
		if (Keyboard::isKeyPressed(Keyboard::Down))
			delay = 0.05f;
		Tick(time);
		CheckLines();
		Draw();
	}
	return 0;
}

//³õÊ¼»¯ËØ²Ä
void GameInit()
{
	t1.loadFromFile("images/tiles.png");
	t2.loadFromFile("images/background.png");
	t3.loadFromFile("images/frame.png");
	s = Sprite(t1);
	background = Sprite(t2);
	frame = Sprite(t3);
}

//»­Í¼
void Draw()
{
	window.clear(Color::White);
	window.draw(background);

	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (map[i][j] == 0)
				continue;
			s.setTextureRect(IntRect(map[i][j]*SIZE, 0, SIZE, SIZE));
			s.setPosition(j * SIZE, i * SIZE);
			s.move(28, 31);
			window.draw(s);
		}
	}
	for (int i = 0; i < 4; i++)
	{
		s.setTextureRect(IntRect(colorNum*SIZE, 0, SIZE, SIZE));
		s.setPosition(a[i].x * SIZE, a[i].y * SIZE);
		s.move(28, 31);
		window.draw(s);
	}
	window.draw(frame);
	window.display();
}


//Éú³É·½¿é
void CreateTetris()
{
	srand(time(0));
	colorNum = 1 + rand() % 7;
	int n = rand() % 7;
	for (int i = 0; i < 4; i++)
	{
		a[i].x = figures[n][i] % 2 + 4;
		a[i].y = figures[n][i] / 2;
	}
	tetrisExist = 1;
}

//¿ØÖÆ
void ControlTetris(Event e)
{
	if (e.key.code == Keyboard::Up)
		Rotate();
	else if (e.key.code == Keyboard::Left)
		Move(-1);
	else if (e.key.code == Keyboard::Right)
		Move(1);
}

//Ðý×ª
void Rotate()
{

	Point p = a[1];
	for (int i = 0; i < 4; i++)
	{
		b[i] = a[i];
		int x = a[i].y - p.y;
		int y = a[i].x - p.x;
		a[i].x = p.x - x;
		a[i].y = p.y + y;
	}
	if (!Check())
	{
		for (int i = 0; i < 4; i++)
		{
			a[i] = b[i];
		}
	}
}

//ÒÆ¶¯
void Move(int dx)
{
	for (int i = 0; i < 4; i++)
	{
		b[i] = a[i];
		a[i].x += dx;
	}
	if (!Check())
	{
		for (int i = 0; i < 4; i++)
		{
			a[i] = b[i];
		}
	}
}

//ÏÂÂä
void Tick(float time)
{
	timer += time;
	if (timer > delay)
	{
		for (int i = 0; i < 4; i++)
		{
			b[i] = a[i];
			a[i].y += 1;
		}
		if (!Check())
		{
			for (int i = 0; i < 4; i++)
			{
				map[b[i].y][b[i].x] = colorNum;
			}
			tetrisExist = 0;
		}
		timer = 0;
		delay = 0.3f;
	}
}

//±ß½çÅö×²¼ì²â
bool Check()
{
	for (int i = 0; i < 4; i++)
	{
		if (a[i].x < 0 || a[i].x >= WIDTH || a[i].y >= HEIGHT)
			return 0;
		else if (map[a[i].y][a[i].x])
			return 0;
	}
	return 1;
}

//Ïû³ý¼ì²â
void CheckLines()
{
	int line = HEIGHT - 1;
	for (int i = HEIGHT - 1; i > 0; i--)
	{
		int count = 0;
		for (int j = 0; j < WIDTH; j++)
		{
			if (map[i][j])
				count++;
			map[line][j] = map[i][j];
		}
		if (count < WIDTH)
			line--;
	}
}
