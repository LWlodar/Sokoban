#pragma once
#include "Board.h"

namespace Game
{

	/// <summary>
	/// Move direction.
	/// </summary>
	enum Direction
	{
		Up, Down, Left, Right
	};

	enum MoveEffect
	{
		// success
		Success = 0,
		// unknown error
		UnknownError,
		// a wall was met during move
		Obstacle,
		// an exit attempt,
		ExitAttempt,
		// sapper tries to destroy the treasure chest
		DestroyTeasure,
		// there's a chest on the board, but it's not within the chests table
		ChestNotInTable,
		// sapper destroyed a crate
		CrateDestroyed,
		// omni destroyed a crate
		CrateDestroyedOmni,
		// the chest type is not compatibile with the worker type (i.e. worker & heavy chest)
		NotCompatibileChest,
		// sapper has no more dynamites
		NoDynamites,
		// omni has no more dynamites
		NoDynamitesOmni,
		// no more energy
		NoEnergy,
		// treasure got
		TreasureGot
	}; // end of: enum MoveEffect

	/// <summary>
	/// A single object on the board.
	/// </summary>
	class Object
	{
	protected:
		/// <summary>
		/// Column.
		/// </summary>
		int _x;

		/// <summary>
		/// Row.
		/// </summary>
		int _y;

	public:

	#pragma region | Public members |

		/// <summary>
		/// Column.
		/// </summary>
		const int& X = _x;

		/// <summary>
		/// Row.
		/// </summary>
		const int& Y = _y;

	#pragma endregion | Public members |

		/// <summary>
		/// Default constructor.
		/// </summary>
		/// <param name="y">Row in which the worker stands.</param>
		/// <param name="x">Column in which the worker stands.</param>
		Object(int y, int x);

		/// <summary>
		/// Move the object to the specified <see cref="Direction"/> on the <see cref="Board"/>.
		/// </summary>
		/// <param name="direction"><see cref="Direction"/> to which the object should be moved.</param>
		/// <param name="board">The game's <see cref="Board"/>.</param>
		/// <returns><see cref="MoveEffect"/> value indicating what happened after the movement.</returns>
		MoveEffect Move(Direction direction, Board* board);

	}; // end of: class Object

} // end of: namespace Game