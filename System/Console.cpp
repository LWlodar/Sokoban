#include "Console.h"
#include "../Game/Board.h"
#include <iostream>

/*
* for system("color ...");
Cid	Color	Cid	Color
1	Blue	9	Light Blue
2	Green	0	Black
3	Aqua	A	Light Green
4	Red		B	Light Aqua
5	Purple	C	Light Red
6	Yellow	D	Light Purple
7	White	E	Light Yellow
8	Gray	F	Bright White
*/

using namespace System;

Console* Console::_instance = nullptr;

Console::Console()
{
	// set white background
	system("color 70");
	_screen = GetStdHandle(STD_OUTPUT_HANDLE);
	_keyboard = GetStdHandle(STD_INPUT_HANDLE);
	_textColor = 0;
	_backgroundColor = 0;

	//HWND hwnd = GetConsoleWindow();
	//MoveWindow(hwnd, 100, 100, 450, 450, TRUE);

	CONSOLE_CURSOR_INFO cursor;
	cursor.dwSize = 100;
	cursor.bVisible = false;
	SetConsoleCursorInfo(_screen, &cursor);

	CONSOLE_FONT_INFOEX font;
	font.cbSize = sizeof font;
	font.nFont = 0;
	font.dwFontSize.X = 20;
	font.dwFontSize.Y = 20;
	font.FontFamily = FF_DONTCARE;
	font.FontWeight = FW_NORMAL;
	wcscpy_s(font.FaceName, L"Sim Sun");
	SetCurrentConsoleFontEx(_screen, FALSE, &font);

	//SetTextColor(Red | Green | Blue);
	//SetBackgroundColor(0);
}

void Console::SetFont(const wchar_t* font, int size)
{
	CONSOLE_FONT_INFOEX finfo;
	finfo.cbSize = sizeof finfo;
	finfo.nFont = 0;
	finfo.dwFontSize.X = size;
	finfo.dwFontSize.Y = 20;
	finfo.FontFamily = FF_DONTCARE;
	finfo.FontWeight = FW_NORMAL;
	wcscpy_s(finfo.FaceName, font);
	SetCurrentConsoleFontEx(GetInstance()->_screen, FALSE, &finfo);
}

Console* Console::GetInstance(void)
{
	if (_instance == nullptr)
		_instance = new Console();
	return _instance;
}

void Console::ResetInstance(void)
{
	delete _instance;
	_instance = nullptr;
}

void Console::SetBackgroundColor(WORD color)
{
	_backgroundColor = 0;
	if (color & EColors::Red)
		_backgroundColor |= BACKGROUND_RED;
	if (color & EColors::Green)
		_backgroundColor |= BACKGROUND_GREEN;
	if (color & EColors::Blue)
		_backgroundColor |= BACKGROUND_BLUE;
	SetConsoleTextAttribute(_screen, _textColor | _backgroundColor);

} // end of: void Console::SetBackgroundColor(WORD color)

void Console::SetTextColor(WORD color)
{
	_textColor = 0;
	if (color & EColors::Red)
		_textColor |= BACKGROUND_RED;
	if (color & EColors::Green)
		_textColor |= BACKGROUND_GREEN;
	if (color & EColors::Blue)
		_textColor |= BACKGROUND_BLUE;
	SetConsoleTextAttribute(_screen, _textColor | _backgroundColor);

} // end of: void Console::SetTextColor(WORD color)

void Console::SetTitle(const char* title)
{
	SetConsoleTitle(title);
} // end of: void Console::SetTitle(char* title)

void Console::SetPosition(COORD position)
{
	SetConsoleCursorPosition(_screen, position);
} // end of: void SetPosition(COORD position)

int Console::GetKey(void)
{
	DWORD read;
	INPUT_RECORD event;

	ReadConsoleInput(Console::GetInstance()->_keyboard, &event, 1, &read);

	// check if the event was caused by the keyboard function and if a key was tapped
	if (event.EventType == KEY_EVENT && event.Event.KeyEvent.bKeyDown)
		// if yes: return its virtual code
		return event.Event.KeyEvent.wVirtualKeyCode;
	// otherwise: return default value
	return 0;

} // end of: int Console::GetKey(void)

void Console::Clear(void)
{
	COORD start;
	DWORD written;

	// start position of the cursor
	start.X = 0;
	start.Y = 0;

	Console* console = Console::GetInstance();

	// sets attributes for all character cells of console
	//FillConsoleOutputAttribute(m_screen, m_textColor | m_backgroundColor, 80*25, start, &written);

	// fulfills console with blanc space 80 colomns 25 rows-it's typical console size (3rd parameter)
	FillConsoleOutputCharacter(console->_screen, ' ', 80*50, start, &written);

	// sets position of the cursor, back at the beginning of the console
	SetConsoleCursorPosition(console->_screen, start);

} // end of: void Console::Clear(void)

void System::Console::DrawBoard(Game::Board* board)
{
	for (int i=0; i<board->Height; i++)
	{
		for (int j=0; j<board->Width; j++)
			std::cout << (*board)[i][j];
		std::cout << '\n';
	}
}
