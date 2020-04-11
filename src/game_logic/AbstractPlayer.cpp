#include "AbstractPlayer.hpp"

namespace game
{

AbstractPlayer::AbstractPlayer(unsigned int id)
    : id(id)
{
}

AbstractBoardCell *AbstractPlayer::dequeueLastMove()
{
    AbstractBoardCell *cell = _moves_done.top();
    _moves_done.pop();
    return cell;
}

void AbstractPlayer::addMoveDone(AbstractBoardCell *cell)
{
    _moves_done.push(cell);
}

} // namespace game