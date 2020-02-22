#include "PenguinPlayer.hpp"

namespace game
{
namespace penguin
{
PenguinPlayer::PenguinPlayer(unsigned int id, HumanPlayer &owner)
    : AbstractPlayer(id),
      owner(owner)
{
}
} // namespace penguin
} // namespace game