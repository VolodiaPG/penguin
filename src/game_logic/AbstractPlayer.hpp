#ifndef ABSTRACT_PLAYER_HPP_
#define ABSTRACT_PLAYER_HPP_

#include <stack>

#include "Move.hpp"

namespace game
{

namespace tic_tac_toe
{
class Player;
class BoardCell;
} // namespace tic_tac_toe
namespace penguin
{
class HumanPlayer;
class BoardCell;
} // namespace penguin

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
    std::stack<Move> _moves_done;

    template <typename PlayerT, typename CellT>
    friend class AbstractPawn;

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
     * @brief Get the number of moves that have been registered in the stack
     * 
     * @return size_t the number of moves still in the stack
     */
    size_t getNumberMovesDone() const { return _moves_done.size(); };

    /**
     * @brief Dequeue the last move registered in the stack
     * 
     * @return Move the last move done
     */
    Move dequeueLastMove();

    /**
     * @brief Get the current cell
     * 
     * @return Move the current cell the player is standing on
     */
    Move getLastMoveDone() const;
};

} // namespace game

#endif
