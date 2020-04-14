#ifndef TIC_TAC_TOE_HUMAN_PLAYER_HPP_
#define TIC_TAC_TOE_HUMAN_PLAYER_HPP_

#include <iostream>
#include "../AbstractPlayer.hpp"
#include "../AbstractPawn.hpp"
#include "BoardCell.hpp"

namespace game
{
class AbstractPlayer;
template<typename, typename> class AbstractPawn;
namespace tic_tac_toe
{
class Player : public AbstractPlayer, public AbstractPawn<Player, BoardCell>
{
public:
    explicit Player(unsigned int id);

    unsigned int getId() { return AbstractPlayer::getId(); };
};
} // namespace tic_tac_toe
} // namespace game

#endif