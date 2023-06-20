#include "Game.h"
#include <iostream>


int main()
{
    try
    {
        Game game;
        game.runMenu();
    }
    catch (std::exception &e)
    {
        std::cout << e.what()<< "\n";
    }
}

