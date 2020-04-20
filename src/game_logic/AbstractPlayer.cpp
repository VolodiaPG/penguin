#include "AbstractPlayer.hpp"

namespace game
{
AbstractPlayer::AbstractPlayer(unsigned int id)
    : id(id)
{
}

bool AbstractPlayer::operator==(const AbstractPlayer &player) const
{
    return id == player.id;
}

} // namespace game