#include "TicTacToe.hpp"

namespace game
{
namespace tic_tac_toe
{

TicTacToe::TicTacToe(AbstractPlayer *player1, AbstractPlayer *player2)
    : AbstractGame(nullptr), // nullptr during construct, then we define the board
      player1(player1),
      player2(player2)
{
    board = new Board();
}

TicTacToe::~TicTacToe()
{
    delete board;
}

bool TicTacToe::play(AbstractPlayer *player, AbstractBoardCell *move)
{
    ++numberMoves;
    return board->performMove(*player, move);
}

void TicTacToe::revertPlay(AbstractBoardCell *cell)
{
    --numberMoves;
    AbstractPlayer *player = player1;

    if (numberMoves % 2)
    {
        player = player2;
    }
    // TODO maybe not the correct semantic, but should not infer anyway
    board->revertMove(*player, cell);
}

bool TicTacToe::isFinished() const
{
    return board->checkStatus() != 0;
}

AbstractPlayer *TicTacToe::getPlayerToPlay() const
{
    AbstractPlayer *nextPlayer = player1;

    if (numberMoves % 2)
    {
        nextPlayer = player2;
    }

    return nextPlayer;
}
} // namespace tic_tac_toe
} // namespace game
