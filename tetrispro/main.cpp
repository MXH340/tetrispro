#include<SFML/Graphics.hpp>
#include"tetris.h"
using namespace sf;
void GameInit();

int main()
{
	GameInit();

	return 0;
}

void GameInit()
{
	RenderWindow window(VideoMode(320, 480), "The Game!");

	while (window.isOpen())
	{
		Event e;
		while (window.pollEvent(e));
		{
			if (e.type == Event::Closed)
			{
				window.close();
			}
		}
	}
	window.clear(Color::White);
	window.display();
}