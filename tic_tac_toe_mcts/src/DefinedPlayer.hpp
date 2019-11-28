#ifndef DEFINED_PLAYER_HPP_
#define DEFINED_PLAYER_HPP_

#include "AbstractPlayer.hpp"
#include "AbstractGame.hpp"

namespace game
{

class DefinedPlayer : public AbstractPlayer
{
public:
    explicit DefinedPlayer(unsigned int id, AbstractGame *game);
    bool action(AbstractBoardCell *cell) override;
};

} // namespace game

#endif