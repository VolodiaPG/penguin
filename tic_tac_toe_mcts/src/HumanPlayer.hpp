#ifndef HUMAN_PLAYER_HPP_
#define HUMAN_PLAYER_HPP_

#include <iostream>
#include "AbstractPlayer.hpp"

namespace game
{
class HumanPlayer : public AbstractPlayer
{
public:
    explicit HumanPlayer(unsigned int id);
    void action(AbstractBoard *board) override;
};
} // namespace game

#endif