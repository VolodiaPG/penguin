#ifndef ABSTRACT_PLAYER_HPP_
#define ABSTRACT_PLAYER_HPP_

#include "AbstractBoardCell.hpp"
#include "AbstractGame.hpp"

namespace game
{
class AbstractGame;

class AbstractPlayer
{
private:
    /**
     * @brief The player's id
     * 
     */
    unsigned int id;

public:
    /**
     * @brief Construct a new Abstract Player object
     * 
     * @param id the id of the player
     */
    explicit AbstractPlayer(unsigned int id);

    virtual ~AbstractPlayer(){};

    /**
     * @brief Get player's id
     * 
     * @return constexpr unsigned int the id
     */
    constexpr unsigned int getId() const { return id; };
};

} // namespace game

#endif