#ifndef BOARD_CELL_HPP_
#define BOARD_CELL_HPP_

#include <memory>

#include "Position.hpp"
#include "AbstractBoardCell.hpp"

namespace game
{

class BoardCell : public AbstractBoardCell
{
private:
    /**
     * @brief Value of the cell
     * 
     */
    int value = 0;

    /**
    * @brief Represents the position of the cell on the board
    * 
    */
    const Position position;

public:
    // /**
    //  * @brief Construct a new Board Cell object
    //  *
    //  */
    // explicit BoardCell();

    /**
    * @brief Construct a new Board Cell object
    * 
    * @param position passed by value to guarantee copy
    */
    explicit BoardCell(const Position &position);

    /**
    * @brief Get the value of the cell
    * 
    * @return int 
    */
    int getValue() const;

    /**
    * @brief Set the value of the cell
    * 
    * @param value the value
    * @return int the value
    */
    int setValue(int value);

    /**
     * @brief Get the Position object
     * 
     * @return the position
     */
    const Position &getPosition() const { return position; }

    /**
     * @brief tells if the cell is claimed or not
     * 
     * @return true the cell is claimed
     * @return false the cell isn't
     */
    bool isClaimed() const;
};

} // namespace game

#endif