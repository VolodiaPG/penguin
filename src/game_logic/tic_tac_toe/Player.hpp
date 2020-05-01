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

class Player : public AbstractPlayer,
               public AbstractPawn<Player, BoardCell>
{
public:
    explicit Player(unsigned int id);

    using AbstractPlayer::getId;

    using AbstractPawn<Player, BoardCell>::operator==;
    using AbstractPawn<Player, BoardCell>::operator!=;
};
} // namespace tic_tac_toe
} // namespace game

#endif