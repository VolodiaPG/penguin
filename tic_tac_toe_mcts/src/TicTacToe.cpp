#include "TicTacToe.hpp"

namespace game
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
    return board->performMove(player->getId(), move);
}

void TicTacToe::revertPlay(AbstractBoardCell *cell)
{
    --numberMoves;
    board->revertMove(cell);
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

} // namespace game
