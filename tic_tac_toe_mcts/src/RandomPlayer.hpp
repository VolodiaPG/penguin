#ifndef RANDOM_PLAYER_HPP_
#define RANDOM_PLAYER_HPP_

#include <random>
#include "AbstractPlayer.hpp"
#include "Position.hpp"

namespace game
{

class RandomPlayer : public AbstractPlayer
{
private:
    /**
     * @brief Deactivate the behavior of the action, as it shouldn't be used that way
     * 
     * @param cell  
     * @return false all the time
     */
    bool action(AbstractBoardCell *) override { return false; };

public:
    explicit RandomPlayer(unsigned int id, AbstractGame *game);
    AbstractBoardCell *randomAction();
};

} // namespace game

#endif