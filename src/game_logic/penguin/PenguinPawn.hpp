#ifndef PENGUIN_PENGUIN_PLAYER_HPP_
#define PENGUIN_PENGUIN_PLAYER_HPP_

#include "../AbstractPawn.hpp"

namespace game
{
namespace penguin
{
class BoardCell;
class HumanPlayer;

#pragma message("added penguin id from counter as debug")

class PenguinPawn : public AbstractPawn<HumanPlayer, BoardCell>
{
private :
    unsigned int _penguin_id_from_counter;
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