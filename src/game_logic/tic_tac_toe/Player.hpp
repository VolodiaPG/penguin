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
               public AbstractPawn<Player, BoardCell>,
               public IEquals_Derived<Player, AbstractPlayer>,
               public IEquals_Derived<Player, AbstractPawn<Player, BoardCell>>
{
protected:
    bool equals_to(const Player &player) const override;

public:
    explicit Player(unsigned int id);

    using AbstractPlayer::getId;
    using AbstractPawn::operator==;
};
} // namespace tic_tac_toe
} // namespace game

#endif