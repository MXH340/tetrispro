#ifndef TETRIS_H_
#define TETRIS_H_
#include<SFML/Graphics.hpp>
#include<time.h>

namespace Tetris
{
	class Tetri
	{
	public:
		Tetri();
		~Tetri();

	private:
		const int SIZE = 18;
		const int WIDTH = 10;
		const int HEIGHT = 20;
		//·½¿éÐÎ×´
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
	};

	Tetri::Tetri()
	{
	}

	Tetri::~Tetri()
	{
	}
}

#endif // !TETRIS_H_
#pragma once
