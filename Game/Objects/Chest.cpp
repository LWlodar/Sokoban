#include "Chest.h"

using namespace Game;

Chest::Chest(int y, int x, Type type) :
	Object(y, x), _type(type)
{
}

MoveEffect Chest::Move(Direction direction, Board* board)
{
	int x = _x, y = _y;
	// set new coordinates
	switch (direction)
	{
	case Direction::Up:
		y--;
		break;
	case Direction::Down:
		y++;
		break;
	case Direction::Left:
		x--;
		break;
	case Direction::Right:
		x++;
		break;
	}
	// checking if the object is of WheeledCrate type
	if (_type == Type::Wheeled)
	{
		// the WheeledCrate moves until an obstacle is met
		while ((*board)[y][x] == ' ')
		{
			// clear the place on board crate leaves
			(*board)[_y][_x] = ' ';
			_x = x;
			_y = y;
			(*board)[_y][_x] = '@';

			// set new coordinates
			switch (direction)
			{
			case Direction::Up:
				y--;
				break;
			case Direction::Down:
				y++;
				break;
			case Direction::Left:
				x--;
				break;
			case Direction::Right:
				x++;
				break;
			}
		} // end of: while (board[y][x] == ' ')
		// crate moved successfully
		return MoveEffect::Success;
	} // end of: if (_type == Type::WheeledCrate)

	MoveEffect ret = Object::Move(direction, board);
	if (ret == MoveEffect::ExitAttempt &&
		_type == Type::Treasure)
	{
		(*board)[_y][_x] = ' ';
		return CrateDestroyed;
	}
	return Success;
}