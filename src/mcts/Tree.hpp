#ifndef TREE_HPP_
#define TREE_HPP_

#include <chrono>
#include "Node.hpp"
#include "../game_logic/AbstractPlayer.hpp"
#include "../game_logic/AbstractGame.hpp"
#include "../log.hpp"

#define NUMBER_ITERATIONS_BEFORE_CHECKING_CHRONO 100

namespace game
{
class MCTSPlayer;
}

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
    game::AbstractPlayer *playerMe;
    game::AbstractGame *game;
    MCTSConstraints constraints;

    explicit Tree(game::AbstractGame *game, game::AbstractPlayer *me, const MCTSConstraints &constraints);
    ~Tree();

    void begin();
    game::AbstractBoardCell *bestMove() const;
    // NodegetRootNode() const { return rootNode; };
};

} // namespace mcts
#endif /*TREE_HPP_*/