#include "HumanPlayer.hpp"

namespace game
{
HumanPlayer::HumanPlayer(unsigned int id, AbstractGame *game)
    : AbstractPlayer(id, game)
{
}

bool HumanPlayer::action(AbstractBoardCell *cell)
{
    AbstractPlayer* that = this;
    return game->play(that, cell);
}
} // namespace game