#ifndef ABSTRACT_BOARD_HPP_
#define ABSTRACT_BOARD_HPP_

#include <list>
#include <memory>

#include "Position.hpp"

namespace game
{

/**
 * @brief Describe the basics of a Board
 * 
 * @tparam game_status_t the type of the value that checkStatus should return
 */
template <typename game_status_t>
class AbstractBoard
{
public:
    /**
    * @brief perform a movement on the board
    * 
    * @param player the player that realizes the movement (id)
    * @param pos the position targeted
    */
    virtual void performMove(int player, Position pos) = 0;

    /**
     * @brief Status of the game
     * 
     * @return game_status 
     */
    virtual game_status_t checkStatus() = 0;

    /**
     * @brief Get the Empty Positions Left
     * 
     * @return std::list<Position> 
     */
    virtual std::shared_ptr<std::list<Position>> getEmptyPositions() = 0;
};

} // namespace game

#endif