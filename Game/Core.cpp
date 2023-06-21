#include <conio.h>
#include <iostream>
#include "Core.h"
#include "../System/Console.h"
#include <string>

#define p_board (*_board)

using namespace Game;

Core* Core::_instance = nullptr;

void Core::DrawBoard(void)
{
	System::Console::DrawBoard(_instance->_board);
}

void Core::SelectWorker(char type)
{
	int* indices = new int[_workersNum];
	int j = 0;
	switch (type)
	{
	case WORKER:
		for (int i=0; i<_workersNum; i++)
			if (_workers[i].Dynamites == -1)
				indices[j++] = i;
		if (j < 1)
			printf("There's no worker available!\n");
		break;
	case OMNI:
		for (int i=0; i<_workersNum; i++)
			if (_workers[i].Energy > 0)
				indices[j++] = i;
		if (j < 1)
			printf("There's no fresh omni available!\n");
		break;
	case SAPPER:
		for (int i=0; i<_workersNum; i++)
			if (_workers[i].Dynamites > 0 && _workers[i].Energy < 0)
				indices[j++] = i;
		if (j < 1)
			printf("There's no loaded sapper available!\n");
		break;
	case LIFTER:
		for (int i=0; i<_workersNum; i++)
			if (_workers[i].Dynamites == -2)
				indices[j++] = i;
		break;
	}
	if (j < 1)
		printf("There's no %s available!\n", "lifter");
	else if (j == 1)
	{
		_selectedWorker = indices[0];
		std::cout << "There's only one worker available, he was chosen!\n";
	}
	else
	{
		std::cout << "There are more then one worker of this type.\nWhich one do You want to choose:\n";
		for (int i=0; i<j; i++)
		{
			printf("%d: His position is %d, %d", i+1, _workers[indices[i]].X, _workers[indices[i]].Y);
			if (_workers[indices[i]].Dynamites > 0)
				printf(" and he has %d dynamites left", _workers[indices[i]].Dynamites);
			printf(".\n");
		}
		j = (int)_getch()-49;

		/* user doesn't want to change worker */
		if (j < 0)
			return;
		_selectedWorker = indices[j];
	}
	std::string title = "Selected worker: ";
	if (_workers[_selectedWorker].Energy > 0)
		title += "Omni: Energy["+std::to_string(_workers[_selectedWorker].Energy)+"] Dynamites["+std::to_string(_workers[_selectedWorker].Dynamites)+"]";
	else if (_workers[_selectedWorker].Dynamites == -1)
		title += "Worker";
	else if (_workers[_selectedWorker].Dynamites == -2)
		title += "Lifter";
	else if (_workers[_selectedWorker].Dynamites > 0 && _workers[_selectedWorker].Energy < 0)
		title += "Sapper: Dynamites["+std::to_string(_workers[_selectedWorker].Dynamites)+"]";
	title += " (x="+std::to_string(_workers[_selectedWorker].X)+",y="+std::to_string(_workers[_selectedWorker].Y)+")";
	System::Console::GetInstance()->SetTitle(title.c_str());

} // end of: void Core::SelectWorker(char type)

Core::Core(void)
{
} // end of: Core::Core(void)

Core::~Core(void)
{
	delete _board;
	delete[] _workers;
	delete[] _chests;
}

#pragma region | Public methods |

Core* Core::GetInstance(void)
{
	if (_instance == nullptr)
		_instance = new Core();
	return _instance;
}

void Core::ResetInstance(void)
{
	if (_instance != nullptr)
		delete _instance;
	_instance = nullptr;
}

void Core::ResetInstance(Board* board, int workersNum, Worker workers[],
	int chestsNum, Chest chests[])
{
	ResetInstance();
	_instance = new Core();
	_instance->_board = board;
	_instance->_workersNum = workersNum;
	_instance->_workers = new Worker[workersNum];
	for (int i=0; i<workersNum; i++)
		_instance->_workers[i] = workers[i];
	_instance->_chestsNum = chestsNum;
	_instance->_chests = new Chest[chestsNum];
	for (int i=0; i<chestsNum; i++)
	{
		_instance->_chests[i] = chests[i];
		if (_instance->_chests[i] == Chest::Treasure)
			_instance->_treasuresNum++;
	}
}

void Core::PrintHelp(void)
{
	System::Console::Clear();
	System::Console::SetFont(L"Consolas", 0);
	std::cout << "The goal of the game is to put all the treasure chests ($) in the exit (X). To do so " <<
		"You can ask several types of workers for help. Depending on their skills, they will help with " <<
		"different chests.\nTo exit the game press '0'.\nFor more, press:\n'w' - workers,\n'c' - chests.\n" <<
		"To get back to game press any other key.\n";
	char shown = '0';
	for (int i=0; i<3; i++)
	{
		switch (_getch())
		{
		case 'w':
			if (shown == 'w')
			{
				i--;
				continue;
			}
			std::cout << "Workers:\n" <<
				"'w' - \"worker\" pushes chests/crates,\n" <<
				"'s' - \"sapper\" destroys crates (has finite number of dynamites),\n" <<
				"'l' - \"lifter\" moves the fragile crates,\n" <<
				"'o' - \"omni\" can move a chest/crate or destroy it.\n";
			shown = 'w';
			break;
		case 'c':
			if (shown == 'c')
			{
				i--;
				continue;
			}
			std::cout << "Chests:\n" <<
				"'$' - \"treasure chest\" must be moved to the exit,\n" <<
				"'@' - \"wheeled crate\" rolls to the first obstacle,\n" <<
				"'%' - \"heavy crate\" cannot be moved, but it's possible to destroy it with a dynamite,\n" <<
				"'!' - \"fragile crate\" can be moved only by lifters.\n";
			shown = 'c';
			break;
		default:
			return;
		}
	}

} // end of: void Core::PrintHelp(void)

void Core::StartGame(void)
{
	char pressedkey = '.';
	bool helpshown = false, onlyselect = true;
	Core* core = Core::GetInstance();
	core->DrawBoard();
	MoveEffect effect = Success;
	//bool effect = false;
	char* print = (char*)"";
	// wait for '0' press
	while ((pressedkey = _getch()) != '0')
	{
		switch (pressedkey)
		{
		case 0:
			// numpad arrow pressed
		case -32:
			// arrow pressed
			if (onlyselect)
			{
				if (helpshown)
					continue;
				std::cout << "You can only choose between:" <<
					"\n \'w\' - worker,\n \'s\' - sapper,\n \'l\' - lifter,\n \'o\' - omni," <<
					"Press 'h' for more informations.\n";
				helpshown = true;
				continue;
			}
			if (helpshown)
			{
				helpshown = false;
				System::Console::Clear();
				core->DrawBoard();
			}
			switch (_getch())
			{
			case 72:
				// arrow up pressed
				effect = core->_workers[core->_selectedWorker].Move(Up, core->_board, core->_chests);
				break;
			case 75:
				// arrow left pressed
				effect = core->_workers[core->_selectedWorker].Move(Left, core->_board, core->_chests);
				break;
			case 77:
				// arrow right pressed
				effect = core->_workers[core->_selectedWorker].Move(Right, core->_board, core->_chests);
				break;
			case 80:
				// arrow down pressed
				effect = core->_workers[core->_selectedWorker].Move(Down, core->_board, core->_chests);
				break;
			}
			// react to movement effect
			switch (effect)
			{
			#pragma region | Successfull movement |
			case Success:
				System::Console::Clear();
				core->DrawBoard();
				if (core->_workers[core->_selectedWorker].Energy > 0)
					printf("Your selected omni has now %d energy points left.",
						core->_workers[core->_selectedWorker].Energy);
				else if (core->_workers[core->_selectedWorker].Energy == 0)
				{
					std::cout << "Your selected omni is exhausted (has no energy points left)!\n"<<
						"Leave him alone... Select another worker.\n";
					onlyselect = true;
				}
				break;
			case CrateDestroyed:
				System::Console::Clear();
				core->DrawBoard();
				printf("BOOM!!! The crate was destroyed!\n");
				printf("Your selected sapper has now %d dynamites left.\n",
					core->_workers[core->_selectedWorker].Dynamites);
				break;
			case CrateDestroyedOmni:
				System::Console::Clear();
				core->DrawBoard();
				printf("BOOM!!! The crate was destroyed!\n");
				printf("Your selected omni has now %d dynamites and %d energy points left.\n",
					core->_workers[core->_selectedWorker].Dynamites,
					core->_workers[core->_selectedWorker].Energy);
				break;
			case TreasureGot:
				if (--core->_treasuresNum == 0)
				{
					System::Console::Clear();
					System::Console::SetFont(L"Consolas", 0);
					std::cout << "\t\t\tCongratulations!!!\n\t\tAll Treasures found, You WON!\n\n\n" <<
						"\t\t(press any key to exit)";
					_getch();
					return;
				}
				else
				{
					System::Console::Clear();
					core->DrawBoard();
					System::Console::GetInstance()->SetTitle("Congratulations!");
					printf("Congrats! You've got a treasure!\nThere's only %d left!\n", core->_treasuresNum);
					if (core->_workers[core->_selectedWorker].Energy > 0)
						printf("Your selected omni has now %d energy points left.",
							core->_workers[core->_selectedWorker].Energy);
					else if (core->_workers[core->_selectedWorker].Energy == 0)
					{
						std::cout << "Your selected omni is exhausted (has no energy points left)!\n"<<
							"Leave him alone... Select another worker.\n";
						onlyselect = true;
					}
				}
				break;
			#pragma endregion | Successfull movement |

			#pragma region | Unsuccessfull movement |
			case Obstacle:
				break;
			case ExitAttempt:
				printf("Whoa, hey You cannot exit the board!\n");
				break;
			case NotCompatibileChest:
				printf("This worker can do nothing with that crate!\n");
				break;
			case ChestNotInTable:
				printf("An error occured (chests table)\n");
				break;
			case DestroyTeasure:
				printf("Whoa, hey You cannot destroy the treasure chest!!!\n");
				break;
			case NoDynamites:
				printf("Your selected sapper has no dynamites left!\n");
				break;
			case NoDynamitesOmni:
				printf("Your selected omni has no dynamites left!\n");
				break;
			case NoEnergy:
				printf("Your selected omni is exhausted (has no energy points left)! Leave him alone...\n");
				break;
			default:
				printf("Error\n");
				break;
			#pragma endregion | Unsuccessfull movement |
			}
			break;
		case 'h':
			// help display
			PrintHelp();
			System::Console::Clear();
			System::Console::SetFont(L"Sim Sun", 20);
			core->DrawBoard();
			helpshown = false;
			break;
		case 'w':
			// select worker
		case 's':
			// select sapper
		case 'l':
			// select lifter
		case 'o':
			// select omni
			core->SelectWorker(pressedkey);
			System::Console::Clear();
			core->DrawBoard();
			onlyselect = false;
			break;
		default:
			if (helpshown)
				break;
			if (onlyselect)
				std::cout << "You can only choose between:" <<
					"\n \'w\' - worker,\n \'s\' - sapper,\n \'l\' - lifter,\n \'o\' - omni," <<
					"Press 'h' for more informations.\n";
			helpshown = true;
			std::cout << "You can only choose between:" <<
				"\n \'w\' - worker,\n \'s\' - sapper,\n \'l\' - lifter,\n \'o\' - omni," <<
				"\n arrows to move selected worker.\nPress 'h' for more informations.\n";
			break;

		} // end of: switch (pressedkey) - clicked button
	}

} // end of: void Core::StartGame(void)

#pragma endregion | Public methods |