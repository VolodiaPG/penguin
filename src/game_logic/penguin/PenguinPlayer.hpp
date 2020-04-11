#ifndef PENGUIN_PENGUIN_PLAYER_HPP_
#define PENGUIN_PENGUIN_PLAYER_HPP_

#include "../AbstractPlayer.hpp"
#include "HumanPlayer.hpp"
#include "BoardCell.hpp"

namespace game
{
namespace penguin
{
class BoardCell;

class PenguinPlayer : public AbstractPlayer
{
private:
    /**
     * @brief The player that owns this penguin
     * 
     */
    HumanPlayer *_owner;

    /**
     * @brief The cell on which the penguin is standing on, and the previous one
     * 
     */
    BoardCell *_standingOn = nullptr;

public:
    /**
     * @brief Construct a new Penguin Player object
     * 
     * @param id the id of the penguin
     * @param owner the owner of the penguin
     */
    explicit PenguinPlayer(unsigned int id, HumanPlayer *owner);

    /**
     * @brief Get the Owner
     * 
     * @return HumanPlayer& the owner of the penguin
     */
    HumanPlayer *getOwner() const { return _owner; };

    /**
     * @brief set the cell on which the penguin is standing on
     * 
     * @param cell the cell on which the penguin is standing
     */
    void setStandingOn(BoardCell *cell) { _standingOn = cell; };

    /**
     * @brief Get the cell on which the penguin is standing on
     * 
     * @return BoardCell*  The cell on wich the penguin is standing on
     */
    BoardCell *getStandingOn() const { return _standingOn; };
};
} // namespace penguin
} // namespace game

#endif