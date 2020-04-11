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
     * @brief Get the Owner
     * 
     * @return HumanPlayer& the owner of the penguin
     */
    HumanPlayer *getOwner() const { return _owner; };
};
} // namespace penguin
} // namespace game

#endif