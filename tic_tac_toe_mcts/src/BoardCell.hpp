#ifndef BOARD_CELL_HPP_
#define BOARD_CELL_HPP_

#include <memory>

#include "Position.hpp"

namespace game
{

class BoardCell
{
private:
    /**
     * @brief Value of the cell
     * 
     */
    int value = 0;

public:
    /**
    * @brief Represents the position of the cell on the board
    * 
    */
    std::shared_ptr<Position> position = NULL;

    /**
    * @brief Construct a new Board Cell object
    * 
    * @param position cf position
    */
    BoardCell(std::shared_ptr<Position> &position);

    /**
     * @brief Construct a new Board Cell object
     * 
     */
    BoardCell();

    /**
    * @brief Get the value of the cell
    * 
    * @return int 
    */
    int getValue();

    /**
    * @brief Set the value of the cell
    * 
    * @param value the value
    * @return int the value
    */
    int setValue(int value);

    /**
     * @brief Set the value of the cell
     * 
     * @param value the value wanted
     * @return int the value set 
     */
    int operator=(int value)
    {
        return setValue(value);
    }

    /**
     * @brief tells if the cell is claimed or not
     * 
     * @return true the cell is claimed
     * @return false the cell isn't
     */
    bool isClaimed();
};

} // namespace game

#endif