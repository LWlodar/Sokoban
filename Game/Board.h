#pragma once

namespace Game
{
	/// <summary>
	/// A single board.
	/// </summary>
	class Board
	{
	private:
		char** _cells;
	public:
		/// <summary>
		/// Width of the board.
		/// </summary>
		int Width;

		/// <summary>
		/// Height of the board.
		/// </summary>
		int Height;

	public:
		/// <summary>
		/// Default constructor.
		/// </summary>
		Board();

		/// <summary>
		/// Copy constructor.
		/// </summary>
		/// <param name="board"></param>
		Board(Board* board);

		/// <summary>
		/// Size constructor.
		/// </summary>
		/// <param name="width">Board's width.</param>
		/// <param name="height">Board's height.</param>
		Board(int width, int height);

		/// <summary>
		/// Initialization constructor.
		/// </summary>
		/// <param name="cells">The board - <see cref="char"/> matrix.</param>
		/// <param name="width">Board's width.</param>
		/// <param name="height">Board's height.</param>
		Board(char** cells, int width, int height);

		/// <summary>
		/// Destructor.
		/// </summary>
		~Board();

		/// <summary>
		/// Index operator. Returns array of <see cref="char"/>s in the index row of the board.
		/// </summary>
		/// <param name="index">Index of the row.</param>
		/// <returns>Array of <see cref="char"/>s in the index row of the board.</returns>
		char* operator[](int index);

	}; // end of: class Board

}; // end of: namespace Game