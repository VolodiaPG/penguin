#ifndef MOVE_HPP_
#define MOVE_HPP_

#include "AbstractBoardCell.hpp"
#include "AbstractPlayer.hpp"

namespace game
{

struct Move
{
    unsigned int player_id;
    AbstractBoardCell *cell;

    // Move &operator=(const Move &other)
    // {
    //     if (this != &other)
    //     {
    //         player_id = other.player_id;
    //         cell = other.cell;
    //     }
    //     return *this;
    // }
};

} // namespace game

#endif