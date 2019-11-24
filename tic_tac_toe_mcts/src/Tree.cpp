#include "Tree.hpp"

namespace mcts
{

Tree::Tree(game::AbstractGame *game, game::MCTSPlayer *me, const MCTSConstraints &constraints)
    : playerMe(me),
      game(game),
      constraints(constraints)
{
    rootNode = new Node(nullptr, me, nullptr);
}

Tree::~Tree()
{
    if (rootNode)
    {
        delete rootNode;
    }
}

void Tree::begin()
{
    timer t;
    while (t.milliseconds_elapsed() < (unsigned long)constraints.time
           // && !rootNode->getIsFullyDone()
    )
    {
        for (int ii = 0; ii < NUMBER_ITERATIONS_BEFORE_CHECKING_CHRONO; ++ii)
        {
            Node *promisingNode = rootNode->selectBestChildAndDoAction(game->board);

            if (!game->isFinished())
            {
                // DEBUG(promisingNode->getPlayer()->getId());
                game::AbstractPlayer *player = promisingNode == rootNode
                                                   ? promisingNode->getPlayer()
                                                   : game->getNextPlayer(promisingNode->getPlayer());
                // DEBUG(promisingNode->getPlayer()->getId());
                // DEBUG(player->getId());
                promisingNode->expandNode(
                    game->board->getEmptyCells(),
                    player);
            }

            Node *nodeToExplore = promisingNode->randomChooseChildOrDefaultMe();

            if (nodeToExplore != promisingNode)
            {
                nodeToExplore->doAction(game->board);
            }
            int winnerId = nodeToExplore->randomSimulation(game);

            nodeToExplore->backPropagateAndRevertAction(winnerId, game->board);
        }
    }

    DEBUG(rootNode->visits);
}

game::AbstractBoardCell *Tree::bestMove() const
{
    return rootNode->nodeWithMaxVisits()->getTargetedCell();
}

} // namespace mcts