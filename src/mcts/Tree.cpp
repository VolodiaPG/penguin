#include "Tree.hpp"

namespace mcts
{

Tree::Tree(
    game::AbstractGame<game::AbstractBoardCell, game::AbstractPlayer, game::AbstractPawn<game::AbstractPlayer, game::AbstractBoardCell>> *game,
    game::AbstractPlayer *me,
    const MCTSConstraints &constraints)
    : playerMe(me),
      game(game),
      constraints(constraints)
{
    rootNode = new Node(nullptr, {nullptr, nullptr, nullptr}, game);
    // TODO remove `playerMe` (useless)
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
    std::cout << "Beginning MCTS search" << std::endl;
    timer t;
    while (t.milliseconds_elapsed() < (unsigned long)constraints.time
           // && !rootNode->getIsFullyDone()
    )
    {
        for (int ii = 0; ii < NUMBER_ITERATIONS_BEFORE_CHECKING_CHRONO; ++ii)
        {
            Node *promisingNode = rootNode->selectBestChildAndDoAction();

            if (!game->isFinished())
            {
                // promisingNode->expandNode(
                //     game->board->getAvailableCells(promisingNode->getPlayer()->getId()),
                //     game->board->getPlayerById(game->getPlayerToPlay()));
                // dbg(game);
                const unsigned int id = game->getPlayerToPlay();
                // dbg(id);
                promisingNode->expandNode(game->getAvailableMoves(game->board->getPlayerById(id)));
            }

            Node *nodeToExplore = promisingNode->randomChooseChildOrDefaultMe();

            if (nodeToExplore != promisingNode)
            {
                nodeToExplore->doAction();
            }
            int winnerId = nodeToExplore->randomSimulation();

            nodeToExplore->backPropagateAndRevertAction(winnerId);
        }
    }

    DEBUG(rootNode->visits);
}

game::Move Tree::bestMove() const
{
    return rootNode->nodeWithMaxVisits()->getMove();
}

} // namespace mcts