#include "AbstractPlayer.hpp"

namespace game
{
AbstractPlayer::AbstractPlayer(unsigned int id)
    : id(id)
{
}

bool AbstractPlayer::equals_to(const AbstractPlayer &player) const
{
    return id == player.id;
}


} // namespace game