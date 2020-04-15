#include <algorithm>
#include "Board.hpp"

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

bool TicTacToe::play(Player *player, BoardCell *move)
{
    ++numberMoves;
    return board->performMove(player, move);
}

void TicTacToe::revertPlay()
{
    --numberMoves;
    int player = 2;

    if (numberMoves % 2)
    {
        player = 1;
    }

    board->revertMove(board->getPawnById(player));
}

bool TicTacToe::isFinished() const
{
    return board->checkStatus() != 0;
}

unsigned int TicTacToe::getPlayerToPlay() const
{
    int nextPlayer = 2;

    if (numberMoves % 2)
    {
        nextPlayer = 1;
    }

    return nextPlayer;
}

std::vector<Move> TicTacToe::getAvailableMoves(Player *player)
{
    std::vector<BoardCell *> input = board->getAvailableCells(player);
    std::vector<Move> ret(input.size());
    BoardCell *current_cell = player->getCurrentCell();
    std::transform(
        input.begin(),
        input.end(),
        ret.begin(),
        [current_cell, player](BoardCell *cell) -> Move {
            return {
                (AbstractBoardCell *)current_cell,
                (AbstractBoardCell *)cell,
                (AbstractPawn<game::AbstractPlayer, game::AbstractBoardCell> *)player};
        });

    return ret;
}

int TicTacToe::checkStatus() const
{
    return board->checkStatus();
}
} // namespace tic_tac_toe
} // namespace game
