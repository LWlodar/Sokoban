#pragma once
#include "../Game/Core.h"

namespace System
{
	/// <summary>
	/// Level files reading class.
	/// </summary>
	class Files
	{
	public:
		/// <summary>
		/// Load a single level.
		/// </summary>
		/// <param name="filename">Name of the file in the levels' folder.</param>
		static void LoadLevel(const char* filename);

	}; // end of: class Files

}; // end of: namespace System