#ifndef ABSTRACT_PLAYER_HPP_
#define ABSTRACT_PLAYER_HPP_

#include "AbstractBoard.hpp"

namespace game
{
class AbstractPlayer
{
public:
    virtual ~AbstractPlayer(){};
    /**
     * @brief The player's id
     * 
     */
    unsigned int id;

    /**
     * @brief The player performs an action
     * 
     */
    virtual void action(AbstractBoard *board) = 0;
};
} // namespace game

#endif