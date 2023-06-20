#include <iostream>
#include <string>
#include <conio.h>
#include "../../System/Console.h"
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

	// check if new coordinates is a usable chest, if yes, "use" it
	bool chest = false;
	switch ((*board)[y][x])
	{
	case FRAGILE:
		if (Dynamites == -1)
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
		break;
	case TREASURE:
		// lifter and sapper can do nothing with treasure chest
		if (Dynamites == -2 || (Dynamites >= 0 && Energy < 0))
			return NotCompatibileChest;
		[[fallthrough]];
	case WHEELED:
		chest = true;
		break;
	}
	// show info about the worker
	std::string title = "Selected worker: ";
	MoveEffect chestmove = Success;
	if (chest)
	{
		char c = (*board)[y][x];
		for (int i=0; i<1000; i++)
		{
			if (chests[i].X == x && chests[i].Y == y)
			{
				if (Dynamites > 0)
				{
					std::cout << "\nWhat do You want to do with this crate?\n" <<
						"Press:\n" <<
						((*board)[y][x] == TREASURE ? "" : "\'d\' to destroy,\n") <<
						(Energy > 0 ? "\'m\' to move,\n" : "") <<
						"\'0\' to do nothing\n";
					while (true)
					{
						switch (_getch())
						{
						case 'd':
							if ((*board)[y][x] == TREASURE)
								continue;
							(*board)[y][x] = ' ';
							Object::Move(direction, board);
							_dynamites--;
							if (Energy > 0)
								_energy--;
							// show info about the worker
							if (Energy > 0)
								title += "Omni: Energy["+std::to_string(Energy)+"] Dynamites["+std::to_string(Dynamites)+"]";
							else if (Dynamites > 0 && Energy < 0)
								title += "Sapper: Dynamites["+std::to_string(Dynamites)+"]";
							title += " (x="+std::to_string(x)+",y="+std::to_string(y)+")";
							System::Console::GetInstance()->SetTitle(title.c_str());
							return (Energy >= 0 ? CrateDestroyedOmni : CrateDestroyed);
						case '0':
							return Success;
						case 'm':
							break;
						default:
							continue;
						}
						break;
					}
				}
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
	// show info about the worker
	if (Energy > 0)
		title += "Omni: Energy["+std::to_string(Energy)+"] Dynamites["+std::to_string(Dynamites)+"]";
	else if (Dynamites == -1)
		title += "Worker";
	else if (Dynamites == -2)
		title += "Lifter";
	else if (Dynamites > 0 && Energy < 0)
		title += "Sapper: Dynamites["+std::to_string(Dynamites)+"]";
	title += " (x="+std::to_string(x)+",y="+std::to_string(y)+")";
	System::Console::GetInstance()->SetTitle(title.c_str());
	return chest ? chestmove : Success;

} // end of: MoveEffect Worker::Move(Direction direction, Board* board, Chest* chests)