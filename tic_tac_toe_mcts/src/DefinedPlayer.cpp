#include "DefinedPlayer.hpp"

namespace game
{

DefinedPlayer::DefinedPlayer(unsigned int id, AbstractGame *game)
    : AbstractPlayer(id, game)
{
}

bool DefinedPlayer::action(AbstractBoardCell *targetCell)
{
    return AbstractPlayer::action(targetCell);
}
} // namespace game