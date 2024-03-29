#pragma once

#include <Windows.h>
#include "../Game/Board.h"

namespace System
{
	/// <summary>
	/// A singleton class to operate on console.
	/// </summary>
	class Console
	{
		/// <summary>
		/// Color "codes".
		/// </summary>
		enum EColors
		{
			Red = 1,
			Green = 2,
			Blue = 4
		};

	#pragma region | Private members |

		static Console* _instance;

		HANDLE _screen;
		HANDLE _keyboard;

		WORD _textColor;
		WORD _backgroundColor;

	#pragma endregion | Private members |

	#pragma region | Constructors/Destructor |

		/// <summary>
		/// Default constructor, gets the standard handles of screen and keyboard.
		/// </summary>
		Console();

		Console(Console const&);

	#pragma endregion | Constructors/Destructor |

	public:

		/// <summary>
		/// Destructor.
		/// </summary>
		~Console(){}

	#pragma region | Public methods |

		/// <summary>
		/// Change background color of the console.
		/// </summary>
		/// <param name="color"><see cref="WORD"/> value - the color.</param>
		void SetBackgroundColor(WORD color);

		/// <summary>
		/// Change text color of the console.
		/// </summary>
		/// <param name="color"><see cref="WORD"/> value - the color.</param>
		void SetTextColor(WORD color);

		/// <summary>
		/// Change the text on the console bar.
		/// </summary>
		/// <param name="title">An array of <see cref="char"/> - new title.</param>
		void SetTitle(const char* title);

		/// <summary>
		/// Set the position of the cursor.
		/// </summary>
		/// <param name="position">New position of the cursor.</param>
		void SetPosition(COORD position);

		/// <summary>
		/// Set the current font on the whole console.
		/// </summary>
		/// <param name="font">Name of the font.</param>
		/// <param name="size">Size of the font.</param>
		static void SetFont(const wchar_t* font, int size);

		/// <summary>
		/// Get the only instance of the class.
		/// </summary>
		/// <returns>The only instance of <see cref="Console"/> class.</returns>
		static Console* GetInstance(void);

		/// <summary>
		/// Reset (clear the memory) the only instance of the class.
		/// </summary>
		static void ResetInstance(void);

	#pragma region | Output methods |

		/// <summary>
		/// Clears the console.
		/// </summary>
		static void Clear(void);

		/// <summary>
		/// Draws the board.
		/// </summary>
		/// <param name="board">Pointer to the game's board to draw.</param>
		static void DrawBoard(Game::Board* board);

	#pragma endregion | Output methods |

	#pragma region | Input methods |

		/// <summary>
		/// Returns the number of a key if tapped on the keyboard by default it returns 0 (nothing was tapped).
		/// </summary>
		/// <returns>The number of the key returned by <see cref="ReadConsoleInput"/> function.</returns>
		static int GetKey(void);

	#pragma endregion | Input methods |

	#pragma endregion | Public methods |

	}; // end of: class Console

}; // end of: namespace System