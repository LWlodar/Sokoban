#include "Files.h"
#include "../Game/Objects/Worker.h"
#include <cstdio>
#include <filesystem>
#include <iostream>
#include <fstream>	
#include <string>

using namespace System;

void Files::LoadLevel(const char* filename)
{
	std::fstream file;
	file.open((std::filesystem::current_path().string()+"\\Level files\\"+filename).c_str(), std::ios::in);
	if (!file)
		throw (std::string)filename+" not found";
	else
	{
		int workernum = 0, chestnum = 0, boardWidth, boardHeight;
		// getting the board size from file
		file >> boardWidth >> boardHeight;
		// checking if the size is correct
		if (boardWidth < 1 || boardHeight < 1)
			throw "";
		// initialization of the board
		char** board = new char*[boardHeight];
		for (int i=0; i<boardHeight; i++)
			board[i] = new char[boardWidth];
		// loading the board
		int j = 0, dynamites = -1, energy = -1;
		char c;
		std::vector<Game::Worker> workers;
		std::vector<Game::Chest> chests;
		for (int i=0; i<boardWidth; i++)
			board[0][i] = '#';
		for (int i=1; i<boardHeight-1; i++)
		{
			//j=1;
			board[i][0] = '#';
			file >> c;
			for (int j=1; j<boardWidth-1; j++)
			{
				if (c == '.')
					board[i][j] = ' ';
				else
				{
					board[i][j] = c;
					if (c == LIFTER)
					{
						workernum++;
						workers.push_back(Game::Worker(i, j, -2, -1));
					}
					else
						switch (c)
						{
						case TREASURE:
							chestnum++;
							chests.push_back(Game::Chest(i, j, Game::Chest::Treasure));
							break;
						case HEAVY:
							chestnum++;
							chests.push_back(Game::Chest(i, j, Game::Chest::Heavy));
							break;
						case WHEELED:
							chestnum++;
							chests.push_back(Game::Chest(i, j, Game::Chest::Wheeled));
							break;
						case FRAGILE:
							chestnum++;
							chests.push_back(Game::Chest(i, j, Game::Chest::Fragile));
							break;
						case OMNI:
							// reading energy
							file >> energy;
							[[fallthrough]];
						case SAPPER:
							// reading dynamites
							file >> dynamites;
							[[fallthrough]];
						case WORKER:
							workernum++;
							workers.push_back(Game::Worker(i, j, dynamites, energy));
							energy = -1;
							dynamites = -1;
							break;
						}
				}
				if (j < boardWidth-2)
					file >> c;
			}
			//board[i][j] = '#';
			board[i][boardWidth-1] = '#';
		}
		for (int i=0; i<boardWidth; i++)
			board[boardHeight-1][i] = '#';
		Game::Core::ResetInstance(new Game::Board(board, boardWidth, boardHeight),
			workernum, workers.data(), chestnum, chests.data());
		for (int i=0; i<boardHeight; i++)
			delete[] board[i];
		delete[] board;
		file.close();
	}

} // end of: void Files::LoadLevel(const char* filename)