#include <iostream>
#include "Worker.h"

using namespace Game;

Worker::Worker(int y, int x, int dynamites, int energy) :
	Object(y, x), _dynamites(dynamites), _energy(energy)
{
}

MoveEffect Worker::Move(Direction direction, Board* board, Chest* chests)
{
	if (Energy == 0)
		return NoEnergy;
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

	// check if new coordinates is a usable chest, if yes, move it
	bool chest = false;
	switch ((*board)[y][x])
	{
	case FRAGILE:
		if (Dynamites != -2)
			return NotCompatibileChest;
		chest = true;
		break;
	case HEAVY:
		if (Dynamites < 0)
			return NotCompatibileChest;
		if (Dynamites < 1)
		{
			if (Energy > 0)
				return NoDynamitesOmni;
			return NoDynamites;
		}
	case WHEELED:
	case TREASURE:
		// lifter and sapper can do nothing with treasure chest
		if (Dynamites == -2 || (Dynamites >= 0 && Energy < 0))
			return NotCompatibileChest;
		chest = true;
		break;
	}
	MoveEffect chestmove;
	if (chest)
	{
		char c = (*board)[y][x];
		for (int i=0; i<1000; i++)
		{
			if (chests[i].X == x && chests[i].Y == y)
			{
				chestmove = chests[i].Move(direction, board);
				if (c == TREASURE && chestmove == CrateDestroyed)
				{
					chestmove = TreasureGot;
					break;
				}
				else if (chestmove != Success)
					return chestmove;
				break;
			}
		}
	}
	// move the worker
	Object::Move(direction, board);
	if (Energy > 0)
		_energy--;
	return chest ? chestmove : Success;

} // end of: MoveEffect Worker::Move(Direction direction, Board* board, Chest* chests)