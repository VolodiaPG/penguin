#include "TicTacToe.hpp"

namespace game
{
namespace tic_tac_toe
{

TicTacToe::TicTacToe()
    : AbstractGame(new Board()) // nullptr during construct, then we define the board
{
}

TicTacToe::~TicTacToe()
{
    delete board;
}

bool TicTacToe::play(const int player_id, BoardCell *move)
{
    ++numberMoves;
    return board->performMove(player_id, move);
}

void TicTacToe::revertPlay(BoardCell *cell)
{
    --numberMoves;
    int player = 0;

    if (numberMoves % 2)
    {
        player = 1;
    }
    // TODO maybe not the correct semantic, but should not infer anyway
    board->revertMove(player, cell);
}

bool TicTacToe::isFinished() const
{
    return board->checkStatus() != 0;
}

int TicTacToe::getPlayerToPlay() const
{
    int nextPlayer = 2;

    if (numberMoves % 2)
    {
        nextPlayer = 1;
    }

    return nextPlayer;
}
} // namespace tic_tac_toe
} // namespace game
