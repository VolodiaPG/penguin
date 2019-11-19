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
    while (t.milliseconds_elapsed() < (unsigned long)constraints.time && !rootNode->getIsFullyDone())
    {
        for (int ii = 0; ii < NUMBER_ITERATIONS_BEFORE_CHECKING_CHRONO; ++ii)
        {
            rootNode->execute();
        }
    }

    DEBUG(rootNode->getTotalScenarii());
}

game::AbstractBoardCell *Tree::bestMove() const
{

    return rootNode->nodeWithMaxVisits()->getState().myAction;
}

} // namespace mcts