#include "../AbstractPlayer.hpp"
#include "PenguinPawn.hpp"
#include "Board.hpp"

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

bool HumanPlayer::equals_to(const HumanPlayer &player) const
{
    return _score == player._score &&
           _penguins == player._penguins;
}

void HumanPlayer::addPenguin(PenguinPawn *penguin)
{
    _penguins.push_back(penguin);
}

std::vector<PenguinPawn *> HumanPlayer::getPenguins() const
{
    return _penguins;
}
} // namespace penguin
} // namespace game