#pragma once
#include "Board.h"
#include "Worker.h"
#include "Chest.h"

/// <summary>
/// Game classes.
/// </summary>
namespace Game
{
	/// <summary>
	/// 
	/// </summary>
	class Core
	{
	private:
		//struct Board
		//{
		//	char** Cells;
		//	int Width;
		//	int Height;
		//};

	#pragma region | Private members |

		/// <summary>
		/// The only instance of the class.
		/// </summary>
		static Core* _instance;

		Board* _board;

		int _workersNum;
		Worker* _workers;

		int _treasuresNum;
		int _chestsNum;
		Chest* _chests;

		int _selectedWorker;

	#pragma endregion | Private members |


	#pragma region | Private methods |

		void DrawBoard(void);
		void SelectWorker(char type);

	#pragma endregion | Private methods |

	public:
		Core(void);
		~Core(void);

	#pragma region | Public methods |

		/// <summary>
		/// Print the information about the game/how to play it.
		/// </summary>
		static void PrintHelp(void);

		/// <summary>
		/// Get the only instance of the class.
		/// </summary>
		/// <returns>The only instance of <see cref="Core"/> class.</returns>
		static Core* GetInstance(void);

		/// <summary>
		/// Reset (clear the memory) the only instance of the class.
		/// </summary>
		static void ResetInstance(void);

		/// <summary>
		/// Starts the game.
		/// </summary>
		static void StartGame(void);

	#pragma endregion | Public methods |

	}; // end of: class Core

};// end of: namespace Game