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

class Tree
{
protected:
    Node *rootNode;
    void expandNode();

public:
    game::AbstractGame<game::AbstractBoardCell, game::AbstractPlayer, game::AbstractPawn<game::AbstractPlayer, game::AbstractBoardCell>> *game;
    MCTSConstraints constraints;

    explicit Tree(
        game::AbstractGame<game::AbstractBoardCell, game::AbstractPlayer, game::AbstractPawn<game::AbstractPlayer, game::AbstractBoardCell>> *game,
        const MCTSConstraints &constraints);
    ~Tree();

    /**
     * @brief Starts the MCTS
     * 
     * @return unsigned int the number of visits
     */
    unsigned int begin();
    game::Move bestMove() const;
};

} // namespace mcts
#endif /*TREE_HPP_*/