#ifndef ABSTRACT_BOARD_HPP_
#define ABSTRACT_BOARD_HPP_

#include <vector>
#include <memory>

#include "AbstractBoardCell.hpp"
#include "AbstractPlayer.hpp"

namespace game
{

class AbstractPlayer;

/**
 * @brief Describe the basics of a Board
 * 
 */
class AbstractBoard
{
public:
    virtual ~AbstractBoard(){};

    /**
    * @brief perform a movement on the board
    * 
    * @param player the player that realizes the movement
    * @param cell the cell targeted
    * 
    * @return true if the move is allowed, false otherwise
    */
    virtual bool performMove(AbstractPlayer& player, AbstractBoardCell *cell) = 0;

    virtual void revertMove(AbstractBoardCell *cell) = 0;

    /**
     * @brief Status of the game
     * 
     * @return game_status 
     */
    virtual int checkStatus() const = 0;

    /**
     * @brief Get the Empty AbstractBoardCell Left
     * 
     * @return std::list<AbstractBoardCell> 
     */
    virtual std::vector<AbstractBoardCell *> getAvailableCells() const = 0;

    /**
     * @brief Get all of the AbstractBoardCell
     * 
     * @return std::list<AbstractBoardCell> 
     */
    virtual std::vector<AbstractBoardCell *> getBoardCells() const = 0;

    /**
     * @brief Get the Cell
     * 
     * @param line line coord
     * @param col col coord
     * @return the targeted cell
     */
    virtual AbstractBoardCell *getCell(int line, int col) const = 0;

    virtual size_t size() const = 0;
};

} // namespace game

#endif
