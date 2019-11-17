#ifndef RANDOM_PLAYER_HPP_
#define RANDOM_PLAYER_HPP_

#include <random>
#include "AbstractPlayer.hpp"
#include "Position.hpp"

namespace game
{

class RandomPlayer : public AbstractPlayer
{

public:
    explicit RandomPlayer(unsigned int id);
    AbstractBoardCell *action(AbstractBoard *board) override;
};

} // namespace game

#endif