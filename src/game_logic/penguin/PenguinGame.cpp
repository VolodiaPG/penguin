#include "PenguinGame.hpp"

namespace game
{
namespace penguin
{

PenguinGame::PenguinGame(const size_t dimension, const size_t number_of_penguins_per_team)
    : AbstractGame(new Board(dimension, number_of_penguins_per_team)) // nullptr during construct, then we define the board
{
}

PenguinGame::~PenguinGame()
{
    delete board;
}

bool PenguinGame::play(const int player_id, BoardCell *move)
{
    bool moved = board->performMove(player_id, move);
    if (moved)
    {
        ++numberMoves;
    }
    return moved;
}

void PenguinGame::revertPlay()
{
    --numberMoves;
    int player = 0;

    if (numberMoves % 2)
    {
        player = 1;
    }

    board->revertMove(player);
}

bool PenguinGame::isFinished() const
{
    return board->checkStatus() != 0;
}

int PenguinGame::getPlayerToPlay() const
{
    int nextPlayer = 2;

    if (numberMoves % 2)
    {
        nextPlayer = 1;
    }

    return nextPlayer;
}
} // namespace penguin
} // namespace game
