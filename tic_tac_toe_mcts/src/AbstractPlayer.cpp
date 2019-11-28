#include "AbstractPlayer.hpp"

namespace game
{

AbstractPlayer::AbstractPlayer(unsigned int id, AbstractGame *game)
    : id(id),
      game(game)
{
}

bool AbstractPlayer::action(AbstractBoardCell *cell)
{
  return game->play(this, cell);
}

} // namespace game