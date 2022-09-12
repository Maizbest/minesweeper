#include "minesweeper/MinesweeperGame.h"

int main()
{
    std::cout << "main function execution" << std::endl;

    try
    {
        MinesweeperGame game;
        return game.start();
    }
    catch (std::exception any)
    {
        std::cout << any.what() << std::endl;
        return -1;
    }
    
}
