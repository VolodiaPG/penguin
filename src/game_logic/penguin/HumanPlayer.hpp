#ifndef PENGUIN_HUMAN_PLAYER_HPP_
#define PENGUIN_HUMAN_PLAYER_HPP_

#include <iostream>
#include "../AbstractPlayer.hpp"

namespace game
{
namespace penguin
{
class HumanPlayer : public AbstractPlayer
{
private:
    /**
     * @brief The score accumulated : the number of fish that each owned penguin ate
     * 
     */
    unsigned int _score = 0;

public:
    explicit HumanPlayer(unsigned int id);

    /**
     * @brief Adds to the score;
     * 
     * @param score the score to add
     */
    void addScore(unsigned int score) { _score += score; };

    /**
     * @brief Substract to the score
     * 
     * @param score the score to substract
     */
    void substractScore(unsigned int score) { _score -= score; };

    /**
     * @brief Returns the player's score
     * 
     * @return int the score
     */
    int getScore(){ return _score; };
};
} // namespace penguin
} // namespace game

#endif