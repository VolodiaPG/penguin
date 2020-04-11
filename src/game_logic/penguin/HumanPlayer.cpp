#include "HumanPlayer.hpp"

namespace game
{
namespace penguin
{
HumanPlayer::HumanPlayer(unsigned int id)
    : AbstractPlayer(id),
      _score(0)
{
}

void HumanPlayer::addScore(int score)
{
    _score += score;
}

void HumanPlayer::substractScore(int score)
{
    _score -= score;
}
} // namespace penguin
} // namespace game