#ifndef PENGUIN_HUMAN_PLAYER_HPP_
#define PENGUIN_HUMAN_PLAYER_HPP_

#include <iostream>
#include "../AbstractPlayer.hpp"

namespace game
{
namespace penguin
{
class Player : public AbstractPlayer
{
public:
    explicit Player(unsigned int id);
};
} // namespace penguin
} // namespace game

#endif