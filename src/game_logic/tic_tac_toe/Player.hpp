#ifndef HUMAN_PLAYER_HPP_
#define HUMAN_PLAYER_HPP_

#include <iostream>
#include "../AbstractPlayer.hpp"

namespace game
{
class Player : public AbstractPlayer
{
public:
    explicit Player(unsigned int id);
};
} // namespace game

#endif