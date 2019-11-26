#ifndef DEFINED_PLAYER_HPP_
#define DEFINED_PLAYER_HPP_

#include "AbstractPlayer.hpp"
#include "AbstractBoardCell.hpp"

namespace game
{

/**
 * @brief Performs a move at a given target
 * 
 */
class DefinedPlayer : public AbstractPlayer
{
protected:
    AbstractBoardCell *target;

public:
    DefinedPlayer(unsigned int id, AbstractBoardCell *target);
    AbstractBoardCell* action(AbstractBoard *board) override;
};

} // namespace game

#endif
