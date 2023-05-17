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

		Chest(int y, int x, Type type);

		MoveEffect Move(Direction direction, Board* board);

	}; // end of: class Chest

}; // end of: namespace Game