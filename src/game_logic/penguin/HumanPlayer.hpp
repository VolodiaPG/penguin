#ifndef PENGUIN_HUMAN_PLAYER_HPP_
#define PENGUIN_HUMAN_PLAYER_HPP_

#include <vector>
#include "../AbstractPlayer.hpp"

namespace game
{

namespace penguin
{

// dummy declaration
class BoardCell;
class Board;
class PenguinPawn;

class HumanPlayer : public AbstractPlayer,
                    public IEquals_Derived<HumanPlayer, AbstractPlayer>
{
private:
    /**
     * @brief The score accumulated : the number of fish that each owned penguin ate
     * 
     */
    int _score;

    /**
     * @brief vector of all the penguins this player possesses in game
     * 
     */
    std::vector<PenguinPawn *> _penguins;

    /**
     * @brief Allow the Board Object to access private properties and methods, especially useful for addPenguin
     * 
     */
    friend class Board;
    void addPenguin(PenguinPawn *penguin);

protected:
    bool equals_to(const HumanPlayer &pawn) const override;

public:
    explicit HumanPlayer(unsigned int id);

    /**
     * @brief Adds to the score;
     * 
     * @param score the score to add
     */
    void addScore(int score);

    /**
     * @brief Substract to the score
     * 
     * @param score the score to substract
     */
    void substractScore(int score);

    /**
     * @brief Returns the player's score
     * 
     * @return int the score
     */
    int getScore() { return _score; };

    /**
     * @brief Get the penguins possessed by the player
     * 
     * @return std::vector<const unsigned int> the list of all the penguins
     */
    std::vector<PenguinPawn *> getPenguins() const;
};
} // namespace penguin
} // namespace game

#endif