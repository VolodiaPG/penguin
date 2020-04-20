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

bool HumanPlayer::equals_to(const AbstractPlayer &player_raw) const
{
    bool ret = AbstractPlayer::equals_to(player_raw);
    const auto player = dynamic_cast<const HumanPlayer *>(&player_raw);
    ret = ret && player != nullptr;

    if (ret)
    {
        ret = _score == player->_score &&
              _penguins == player->_penguins;
    }

    return ret;
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