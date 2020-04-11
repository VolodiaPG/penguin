#ifndef ABSTRACT_PLAYER_HPP_
#define ABSTRACT_PLAYER_HPP_

#include <stack>
#include "AbstractBoardCell.hpp"

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

    /**
     * @brief Store all the moves done
     * 
     */
    std::stack<AbstractBoardCell *> _moves_done;

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

    /**
     * @brief Dequeue the last move registered in the stack
     * 
     * @return AbstractBoardCell* the last move done
     */
    AbstractBoardCell *dequeueLastMove();

    /**
     * @brief Queue the move done at the top of the stack
     * 
     * @param move the move to stack
     */
    void addMoveDone(AbstractBoardCell *move);

    /**
     * @brief Get the number of moves that have been registered in the stack
     * 
     * @return size_t the number of moves still in the stack
     */
    size_t getNumberMovesDone() const { return _moves_done.size(); };

    /**
     * @brief Get the current cell
     * 
     * @return AbstractBoardCell* the current cell the player is standing on
     */
    AbstractBoardCell* getCurrentCell() { return _moves_done.top(); };
};

} // namespace game

#endif
