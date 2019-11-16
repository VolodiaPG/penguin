#include "AbstractGame.hpp"

namespace game
{

AbstractGame::AbstractGame(AbstractBoard *board)
    : AbstractInterface(), board(board)
{
}

void AbstractGame::loop()
{
    draw();
    while (!isFinished())
    {
        play();
        draw();
    }
}
} // namespace game