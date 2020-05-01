#ifndef ABSTRACT_PLAYER_HPP_
#define ABSTRACT_PLAYER_HPP_

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

protected:
    virtual bool equals_to(const AbstractPlayer &player) const;

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

    bool operator==(const AbstractPlayer &player) const { return equals_to(player); };
    bool operator!=(const AbstractPlayer &player) const { return !equals_to(player); };
};

} // namespace game

#endif
