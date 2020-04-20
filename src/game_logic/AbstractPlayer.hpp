#ifndef ABSTRACT_PLAYER_HPP_
#define ABSTRACT_PLAYER_HPP_

#include "utils/Iequals.hpp"

namespace game
{
class AbstractPlayer : public IEquals_Base<AbstractPlayer>
{
private:
    /**
     * @brief The player's id
     * 
     */
    unsigned int id;

protected:
    bool equals_to(const AbstractPlayer &player) const override;

public:
    /**
     * @brief Construct a new Abstract Player object
     * 
     * @param id the id of the player
     */
    explicit AbstractPlayer(unsigned int id);

    explicit AbstractPlayer(const AbstractPlayer &) = default;
    
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
