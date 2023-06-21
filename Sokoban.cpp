#include <iostream>
#include "System/Console.h"
#include "System/Files.h"
#include "Game/Core.h"

int main()
{
    // initialize the console/"GUI"
    System::Console::GetInstance()->SetTitle("Sokoban");
    System::Files::LoadLevel("level1.txt");
    Game::Core::StartGame();

    // free memory
    System::Console::Clear();
    System::Console::SetFont(L"Consolas", 0);
    System::Console::ResetInstance();
    Game::Core::ResetInstance();
    std::cout << "Thanks for playing!\nGoodbye :)";
    getchar();
}