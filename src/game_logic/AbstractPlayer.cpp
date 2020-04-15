#include "Move.hpp"
#include "AbstractBoardCell.hpp"
#include "AbstractPawn.hpp"
#include "AbstractPlayer.hpp"

namespace game
{

AbstractPlayer::AbstractPlayer(unsigned int id)
    : id(id)
{
}

Move AbstractPlayer::dequeueLastMove()
{
    Move move = _moves_done.top();
    _moves_done.pop();
    move.pawn->_current_cell = move.from;
    return move;
}

Move AbstractPlayer::getLastMoveDone() const
{
    return _moves_done.top();
}

} // namespace game