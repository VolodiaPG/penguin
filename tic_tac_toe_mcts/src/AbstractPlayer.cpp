#include "AbstractPlayer.hpp"

namespace game
{

AbstractPlayer::AbstractPlayer(unsigned int id, AbstractGame *game)
    : id(id),
      game(game)
{
}

} // namespace game