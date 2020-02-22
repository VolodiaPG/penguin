#ifndef PENGUIN_BOARD_CELL_HPP_
#define PENGUIN_BOARD_CELL_HPP_

#include <memory>

#include "../Position.hpp"
#include "../AbstractBoardCell.hpp"

namespace game
{
namespace penguin
{
class BoardCell : public AbstractBoardCell
{
private:
    /**
     * @brief if cell is still available for the player to move onto
     * 
     */
    bool _gone = false;

    /**
    * @brief Represents the position of the cell on the board
    * 
    */
    const Position position;

    /**
     * @brief The number of fish contained in the cell
     * 
     */
    const int _number_fish;

public:
    /**
     * @brief Construct a new Board Cell object
     * 
     * @param position The position
     * @param number_fish the number of fish contained in this cell
     */
    explicit BoardCell(const Position &position, int number_fish);

    /**
     * @brief Get the Position object
     * 
     * @return the position
     */
    const Position &getPosition() const { return position; }

    /**
     * @brief tells if the cell is gone or not
     * 
     * @return true the cell is gone
     * @return false the cell is still available for the players to move onto
     */
    bool isGone() const { return _gone; };

    void setGone(bool gone) { _gone = gone; };

    /**
     * @brief Get the number of fish contained inside the cell
     * 
     * @return int the number of fish
     */
    int getFish() const { return _number_fish; }
};
} // namespace penguin
} // namespace game

#endif