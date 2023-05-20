#pragma once
#include "../Basics.h"
#include "../Board.h"
#include "Object.h"
#include "Chest.h"

namespace Game
{
	/// <summary>
	/// 
	/// </summary>
	class Worker : public Object
	{
		/// <summary>
		/// Number of dynamites (used to destroy crates) left.
		/// </summary>
		int _dynamites = -1;

		/// <summary>
		/// Number of energy points (used for move by Omni) left.<para/>For lifter it
		/// set to '-2'.
		/// </summary>
		int _energy = -1;

	public:

	#pragma region | Public members |

		/// <summary>
		/// Number of dynamites (used to destroy crates) left.<para/>For lifter it
		/// set to '-2'.
		/// </summary>
		const int& Dynamites = _dynamites;

		/// <summary>
		/// Number of energy points (used for move by Omni) left.
		/// </summary>
		const int& Energy = _energy;

	#pragma endregion | Public members |

		/// <summary>
		/// Default constructor.
		/// </summary>
		/// <param name="y">Row in which the worker stands.</param>
		/// <param name="x">Column in which the worker stands.</param>
		/// <param name="dynamites">Number of dynamites (used by Omni and Sapper).</param>
		/// <param name="energy">Number of energy (used only by Omni).</param>
		Worker(int y=0, int x=0, int dynamites = -1, int energy = -1);
		Worker(const Worker&) = default;
		Worker& operator=(const Worker& w)
		{
			if (this == &w)
				return *this;
			Object::_x = w._x;
			Object::_y = w._y;
			_dynamites = w._dynamites;
			_energy = w._energy;

			return *this;
		}

		/// <summary>
		/// Move the worker to the specified <see cref="Direction"/> on the <see cref="Board"/>.
		/// </summary>
		/// <param name="direction"><see cref="Direction"/> to which the worker should be moved.</param>
		/// <param name="board">The game's <see cref="Board"/>.</param>
		/// <param name="chests">A pointer to an array of <see cref="Chest"/>s.</param>
		/// <returns><see cref="MoveEffect"/> object indicating what happened after the movement.</returns>
		MoveEffect Move(Direction direction, Board* board, Chest* chests);

	}; // end of: class Worker

} // end of: namespace Game