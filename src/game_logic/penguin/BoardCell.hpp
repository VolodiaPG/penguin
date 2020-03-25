#ifndef PENGUIN_BOARD_CELL_HPP_
#define PENGUIN_BOARD_CELL_HPP_

#include <memory>

#include "../Position.hpp"
#include "../AbstractBoardCell.hpp"
#include "PenguinPlayer.hpp"

namespace game
{
namespace penguin
{
class PenguinPlayer;

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

    /**
     * @brief The player that currently owns the cell
     * 
     */
    PenguinPlayer *_owner = nullptr;

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

    /**
     * @brief Sets the gone flag
     * 
     * @param gone 
     */
    void setGone(bool gone) { _gone = gone; };

    /**
     * @brief Set the penguin who stands on the cell, ie the cell's owner atm
     * 
     * @param penguin The penguin that stands on top of the cell
     */
    void setOwner(PenguinPlayer &penguin) { _owner = &penguin; };

    /**
     * @brief Nobody owns the cell now
     * 
     */
    void clearOwner() { _owner = nullptr; };

    /**
     * @brief Get the penguin standing on the cell
     * 
     * @return PenguinPlayer* the penguin
     */
    PenguinPlayer *getOwner() { return _owner; };

    /**
     * @brief Is a penguin on the cell
     * 
     * @return true there is a penguin on the cell
     * @return false there is no penguin on the cell
     */
    bool isOwned() { return _owner != nullptr; };

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