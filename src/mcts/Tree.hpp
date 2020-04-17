#ifndef TREE_HPP_
#define TREE_HPP_

#include <chrono>
#include "../game_logic/utils/Move.hpp"

#define NUMBER_ITERATIONS_BEFORE_CHECKING_CHRONO 100

namespace game
{
template <class, class, class>
class AbstractGame;
class AbstractBoardCell;
class AbstractPlayer;
} // namespace game

namespace mcts
{

template <class, class, class>
class Node;

struct timer
{
    typedef std::chrono::steady_clock clock;
    typedef std::chrono::milliseconds milliseconds;

    void reset() { start = clock::now(); }

    unsigned long long milliseconds_elapsed() const
    {
        return std::chrono::duration_cast<milliseconds>(clock::now() - start).count();
    }

private:
    clock::time_point start = clock::now();
};

typedef struct
{
    /**
     * @brief Time constraint in ms
     * 
     */
    int time;
} MCTSConstraints;

template <class CellT, class PlayerT, class PawnT>
class Tree
{
protected:
    Node<CellT, PlayerT, PawnT> *rootNode;
    void expandNode();
    game::AbstractGame<CellT, PlayerT, PawnT> *game;
    MCTSConstraints constraints;

    template <class, class, class>
    friend class Node;
public:

    explicit Tree(
        game::AbstractGame<CellT, PlayerT, PawnT> *game,
        const MCTSConstraints &constraints);
    ~Tree();

    /**
     * @brief Starts the MCTS
     * 
     * @return unsigned int the number of visits
     */
    unsigned int begin();
    game::Move<CellT, PawnT> bestMove() const;
};

} // namespace mcts
#endif /*TREE_HPP_*/