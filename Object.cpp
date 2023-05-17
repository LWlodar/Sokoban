#include "Object.h"
#include "Basics.h"

using namespace Game;

Object::Object(int y, int x) : _y(y), _x(x)
{
}

MoveEffect Object::Move(Direction direction, Board* board)
{
	// new coordinates
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

	// check if new coordinates are correct
	switch ((*board)[y][x])
	{
	case WALL:
	case WORKER:
	case SAPPER:
	case OMNI:
	case LIFTER:
	case TREASURE:
	case WHEELED:
	case FRAGILE:
	case HEAVY:
		return Obstacle;
	case EXIT:
		return ExitAttempt;
	default:
		// by default: it's a successful move
		char object = (*board)[_y][_x];
		(*board)[_y][_x] = ' ';
		_x = x;
		_y = y;
		(*board)[_y][_x] = object;
		return Success;
	}

	return UnknownError;

} // end of: MoveEffect Object::Move(Direction direction, Board* board)