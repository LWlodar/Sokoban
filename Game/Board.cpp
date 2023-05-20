#include "Board.h"

using namespace Game;

#pragma region | Constructors/Destructor |

Board::Board()
{
}

Board::Board(Board* board) :
	Width(board->Width), Height(board->Height)
{
	_cells = new char*[Height];
	for (int i=0; i<Height; i++)
	{
		_cells[i] = new char[Width];
		for (int j=0; j<Width; j++)
			_cells[i][j] = (*board)[i][j];
	}
}

Board::Board(int width, int height) :
	Width(width), Height(height)
{
	_cells = new char*[Height];
	for (int i=0; i<Height; i++)
		_cells[i] = new char[Width];
}

Board::Board(char** cells, int width, int height) :
	Board::Board(width, height)
{
	for (int i=0; i<Height; i++)
		for (int j=0; j<Width; j++)
			_cells[i][j] = cells[i][j];
}

Board::~Board()
{
	for (int i=0; i<Height; i++)
		delete[] _cells[i];
	delete[] _cells;
}

#pragma endregion | Constructors/Desctructor |


char* Board::operator[](int index)
{
	if (_cells == nullptr)
	{
		_cells = new char*[Height];
		for (int i=0; i<Height; i++)
			_cells[i] = new char[Width];
	}

	return _cells[index];
}