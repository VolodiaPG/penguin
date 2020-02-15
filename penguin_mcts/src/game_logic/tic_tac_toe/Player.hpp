#ifndef HUMAN_PLAYER_HPP_
#define HUMAN_PLAYER_HPP_

#include <iostream>
#include "../AbstractPlayer.hpp"

namespace game
{
namespace tic_tac_toe
{
class Player : public AbstractPlayer
{
public:
    explicit Player(unsigned int id);
};
} // namespace tic_tac_toe
} // namespace game

#endif