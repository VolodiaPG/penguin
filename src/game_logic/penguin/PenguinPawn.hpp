#ifndef PENGUIN_PENGUIN_PLAYER_HPP_
#define PENGUIN_PENGUIN_PLAYER_HPP_

#include "../AbstractPawn.hpp"

namespace game
{
namespace penguin
{
class BoardCell;
class HumanPlayer;

class PenguinPawn : public AbstractPawn<HumanPlayer, BoardCell>
{
public:
    /**
     * @brief Construct a new Penguin Player object
     * 
     * @param id the id of the penguin
     * @param owner the owner of the penguin
     */
    explicit PenguinPawn(unsigned int id, HumanPlayer *owner);
};
} // namespace penguin
} // namespace game

#endif