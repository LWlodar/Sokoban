#pragma once
#include "Object.h"

namespace Game
{
	/// <summary>
	/// 
	/// </summary>
	class Chest : public Object
	{
	public:
		enum Type
		{
			Treasure,
			Wheeled,
			Fragile,
			Heavy
		};
	private:
		Type _type;


	public:

	#pragma region | Public members |


	#pragma endregion | Public members |

		Chest(int y=0, int x=0, Type type=Treasure);
		Chest& operator=(const Chest& c)
		{
			if (this == &c)
				return *this;
			Object::_x = c._x;
			Object::_y = c._y;
			_type = c._type;
			return *this;
		}
		bool operator==(const Type type)
		{
			return _type == type;
		}

		MoveEffect Move(Direction direction, Board* board);

	}; // end of: class Chest

}; // end of: namespace Game