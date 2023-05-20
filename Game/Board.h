#pragma once

namespace Game
{

	class Board
	{
	private:
		char** _cells;
	public:
		int Width;
		int Height;

	public:
		Board();
		Board(Board* board);
		Board(int width, int height);
		Board(char** cells, int width, int height);
		~Board();
		char* operator[](int index);

	}; // end of: class Board

}; // end of: namespace Game