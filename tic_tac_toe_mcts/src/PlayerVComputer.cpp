#include "PlayerVComputer.hpp"

namespace game
{
PlayerVComputer::PlayerVComputer()
    : TicTacToe(nullptr, nullptr) // instanciate these variables in the body of the constructor
{
    player1 = new HumanPlayer(1, this);
    player2 = new MCTSPlayer(2, this);
}

PlayerVComputer::~PlayerVComputer()
{
    delete player1;
    delete player2;
}

bool PlayerVComputer::playPlayer1(int x, int y)
{
    AbstractBoardCell *cell = board->getCell(x, y);
    bool ret = false;

    if (cell)
    {
        ret = player1->action(cell);
    }

    return ret;
}

bool PlayerVComputer::playPlayer2()
{
    return player2->action(nullptr);
}

} // namespace game
