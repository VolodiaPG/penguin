#include "AbstractGame.hpp"

namespace game
{

AbstractGame::AbstractGame(AbstractBoard *board)
    : AbstractInterface(), board(board)
{
}

void AbstractGame::loop()
{
    while (!isFinished())
    {
        play();
        draw();
    }
}
} // namespace game