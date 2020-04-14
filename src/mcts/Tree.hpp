#ifndef TREE_HPP_
#define TREE_HPP_

#include <chrono>
#include <bits/stdc++.h>
#include "Node.hpp"
#include "../game_logic/AbstractPlayer.hpp"
#include "../game_logic/AbstractGame.hpp"
#include "../game_logic/AbstractBoardCell.hpp"
#include "../log.hpp"

#include "../dbg.h"

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
    game::AbstractGame<game::AbstractBoardCell, game::AbstractPlayer, game::AbstractPawn<game::AbstractPlayer, game::AbstractBoardCell>> *game;
    MCTSConstraints constraints;

    explicit Tree(
        game::AbstractGame<game::AbstractBoardCell, game::AbstractPlayer, game::AbstractPawn<game::AbstractPlayer, game::AbstractBoardCell>> *game,
        game::AbstractPlayer *me,
        const MCTSConstraints &constraints);
    ~Tree();

    void begin();
    game::Move bestMove() const;
    // NodegetRootNode() const { return rootNode; };
};

} // namespace mcts
#endif /*TREE_HPP_*/