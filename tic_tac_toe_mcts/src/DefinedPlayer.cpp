#include "DefinedPlayer.hpp"

namespace game
{
DefinedPlayer::DefinedPlayer(unsigned int id, AbstractBoardCell *target) : AbstractPlayer(id), target(target)
{
}

AbstractBoardCell *DefinedPlayer::action(AbstractBoard *board)
{
    board->performMove(getId(), target);
    return target;
}
} // namespace game