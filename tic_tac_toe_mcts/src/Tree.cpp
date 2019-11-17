#include "Tree.hpp"

namespace mcts
{

Tree::Tree(game::AbstractGame *game, game::MCTSPlayer *me, const MCTSConstraints &constraints)
    : playerMe(me), game(game), constraints(constraints)
{
    State state = {nullptr};
    rootNode = new Node(this, nullptr, state);
}

Tree::~Tree()
{
    delete rootNode;
}

void Tree::begin()
{
    timer t;
    while (t.milliseconds_elapsed() < (unsigned long)constraints.time)
    {
        rootNode->execute();
    }
}

game::AbstractBoardCell* Tree::bestMove() const
{
    return rootNode->nodeWithMaxVictories()->getState().myAction;
}

} // namespace mcts