#pragma once
#include "Object.h"

namespace Game
{
	/// <summary>
	/// A single chest.
	/// </summary>
	class Chest : public Object
	{
	public:
		/// <summary>
		/// Chest type.
		/// </summary>
		enum Type
		{
			Treasure,
			Wheeled,
			Fragile,
			Heavy
		};

	private:
		Type _type;


	#pragma region | Public methods |

	public:

		/// <summary>
		/// Initialization constructor.
		/// </summary>
		/// <param name="y">Row in which the chest lies.</param>
		/// <param name="x">Column in which the chest lies.</param>
		/// <param name="type">Type of the chest.</param>
		Chest(int y=0, int x=0, Type type=Treasure);

		/// <summary>
		/// Assign operator.
		/// </summary>
		/// <param name="c"></param>
		/// <returns>New <see cref="Chest"/> object.</returns>
		Chest& operator=(const Chest& c)
		{
			if (this == &c)
				return *this;
			Object::_x = c._x;
			Object::_y = c._y;
			_type = c._type;
			return *this;
		} // end of: Chest& operator=(const Chest& c)

		/// <summary>
		/// Compare operator.
		/// </summary>
		/// <param name="type"><see cref="Type"/> value.</param>
		/// <returns><see cref="bool"/> value indicating whether the chest
		/// is of the put <see cref="Type"/>.</returns>
		bool operator==(const Type type)
		{
			return _type == type;
		} // end of: bool operator==(const Type type)

		/// <summary>
		/// Move the object to the specified <see cref="Direction"/> on the <see cref="Board"/>.
		/// </summary>
		/// <param name="direction"><see cref="Direction"/> to which the object should be moved.</param>
		/// <param name="board">The game's <see cref="Board"/>.</param>
		/// <returns><see cref="MoveEffect"/> value indicating what happened after the movement.</returns>
		MoveEffect Move(Direction direction, Board* board);

	#pragma endregion | Public methods |

	}; // end of: class Chest

}; // end of: namespace Game