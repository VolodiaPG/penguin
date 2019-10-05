#ifndef ABSTRACT_BOARD_HPP_
#define ABSTRACT_BOARD_HPP_

#include <list>
#include <memory>

#include "Position.hpp"

namespace mcts
{

typedef enum
{
    IN_PROGRESS = 0,
    DRAW,
    P1,
    P2
} game_status;

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
    virtual game_status checkStatus() = 0;

    /**
     * @brief Get the Empty Positions Left
     * 
     * @return std::list<Position> 
     */
    virtual std::unique_ptr<std::list<Position>> getEmptyPositions() = 0;
};

} // namespace mcts

#endif