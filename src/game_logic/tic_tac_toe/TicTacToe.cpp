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

void TicTacToe::revertPlay()
{
    --numberMoves;
    int player = 2;

    if (numberMoves % 2)
    {
        player = 1;
    }

    board->revertMove(player);
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

std::vector<Move> TicTacToe::getAvailableMoves(const unsigned int player_id)
{
    std::vector<BoardCell *> input = board->getAvailableCells(player_id);
    std::vector<Move> ret(input.size());
    std::transform(input.begin(), input.end(), ret.begin(), [player_id](BoardCell *cell) -> Move { return {player_id, cell}; });

    return ret;
}
} // namespace tic_tac_toe
} // namespace game
