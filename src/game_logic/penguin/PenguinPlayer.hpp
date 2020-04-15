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
    BoardCell *_standingOn = nullptr, *_previousStandingOn = nullptr;

public:
    /**
     * @brief Construct a new Penguin Player object
     * 
     * @param id the id of the penguin
     * @param owner the owner of the penguin
     */
    explicit PenguinPlayer(unsigned int id, HumanPlayer *owner);

    /**
     * @brief Set the Standing On Cell
     * 
     * @param standingOn the cell on wich the player is currently standing
     */
    void setStandingOn(BoardCell *standingOn)
    {
        _previousStandingOn = _standingOn;
        _standingOn = standingOn;
    };

    /**
     * @brief Get the Standing On Cell
     * 
     * @return BoardCell* returns the cell where the penguin is currenlty standing
     */
    BoardCell *getStandingOn() { return _standingOn; };

    /**
     * @brief Get the Previous Standing On cell
     * 
     * @return BoardCell* The cell where the penguin was previously standing on, before he moved
     */
    BoardCell *getPreviousStandingOn() { return _previousStandingOn; };

    /**
     * @brief Get the Owner
     * 
     * @return HumanPlayer& the owner of the penguin
     */
    HumanPlayer *getOwner() const { return _owner; };
};
} // namespace penguin
} // namespace game

#endif