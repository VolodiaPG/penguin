#include <algorithm>
#include <assert.h>

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
    bool ret = board->performMove(player, move);
    if (ret){
        ++numberMoves;
    }
    return ret;
}

const Move<BoardCell, Player> TicTacToe::revertPlay()
{
    --numberMoves;
    return board->revertMove();
}

bool TicTacToe::isFinished() const
{
    return board->checkStatus() != 0;
}

unsigned int TicTacToe::getPlayerToPlay()
{
    int nextPlayer = 2;

    if (numberMoves % 2)
    {
        nextPlayer = 1;
    }

    return nextPlayer;
}

std::vector<Move<BoardCell, Player>> TicTacToe::getAvailableMoves(Player *player)
{
    std::vector<BoardCell *> input = board->getAvailableCells(player);
    std::vector<Move<BoardCell, Player>> ret(input.size());
    // BoardCell *current_cell = player->getCurrentCell();
    std::transform(
        input.begin(),
        input.end(),
        ret.begin(),
        [player](BoardCell *cell) -> Move<BoardCell, Player> {
            return {
                nullptr,
                cell,
                player};
        });

    return ret;
}

int TicTacToe::checkStatus() const
{
    return board->checkStatus();
}

AbstractGame<BoardCell, Player, Player> *TicTacToe::clone() const
{
    TicTacToe *ttt = new TicTacToe(*this);
    ttt->board = board->clone();
    assert(ttt->numberMoves == numberMoves);
    return ttt;
}
} // namespace tic_tac_toe
} // namespace game
