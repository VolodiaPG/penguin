#ifndef ABSTRACT_PLAYER_HPP_
#define ABSTRACT_PLAYER_HPP_

#include "History.hpp"

namespace game
{

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
    unsigned int getId() const { return id; };
};

} // namespace game

#endif
