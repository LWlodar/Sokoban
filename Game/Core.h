#pragma once
#include "Board.h"
#include "Objects/Worker.h"
#include "Objects/Chest.h"

/// <summary>
/// Game classes.
/// </summary>
namespace Game
{
	/// <summary>
	/// Main class of the game.
	/// </summary>
	class Core
	{
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
		/// <summary>
		/// Default constructor.
		/// </summary>
		Core(void);

		/// <summary>
		/// Default destructor.
		/// </summary>
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
		/// Reset (clear the memory) the only instance of the class.<para/>
		/// Create a new one with the given values.
		/// </summary>
		static void ResetInstance(Board* board, int workersNum, Worker workers[],
			int chestsNum, Chest chests[]);

		/// <summary>
		/// Starts the game.
		/// </summary>
		static void StartGame(void);

	#pragma endregion | Public methods |

	}; // end of: class Core

};// end of: namespace Game