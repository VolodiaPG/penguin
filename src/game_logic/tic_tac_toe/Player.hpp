#ifndef TIC_TAC_TOE_HUMAN_PLAYER_HPP_
#define TIC_TAC_TOE_HUMAN_PLAYER_HPP_

#include <iostream>
#include "../AbstractPlayer.hpp"
#include "../AbstractPawn.hpp"

namespace game
{
namespace tic_tac_toe
{
class BoardCell;

class Player : public AbstractPlayer<BoardCell, Player>,
               public AbstractPawn<Player, BoardCell>
{
public:
    explicit Player(unsigned int id);

    unsigned int getId() { return AbstractPlayer::getId(); };
};
} // namespace tic_tac_toe
} // namespace game

#endif