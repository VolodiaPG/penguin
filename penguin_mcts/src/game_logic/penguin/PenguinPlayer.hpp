#ifndef PENGUIN_PENGUIN_PLAYER_HPP_
#define PENGUIN_PENGUIN_PLAYER_HPP_

#include "../AbstractPlayer.hpp"
#include "HumanPlayer.hpp"

namespace game
{
namespace penguin
{
class PenguinPlayer : public AbstractPlayer
{
protected:
    HumanPlayer& owner;
public:
    explicit PenguinPlayer(unsigned int id, HumanPlayer &owner);
};
} // namespace penguin
} // namespace game

#endif