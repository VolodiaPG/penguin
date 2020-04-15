#include "../game_logic/AbstractBoard.hpp"
#include "../game_logic/AbstractBoardCell.hpp"
#include "../game_logic/AbstractGame.hpp"
#include "../game_logic/AbstractPlayer.hpp"
#include "Node.hpp"

#include "Tree.hpp"

namespace mcts
{

Tree::Tree(
    game::AbstractGame<game::AbstractBoardCell, game::AbstractPlayer, game::AbstractPawn<game::AbstractPlayer, game::AbstractBoardCell>> *game,
    const MCTSConstraints &constraints)
    :
      game(game),
      constraints(constraints)
{
    rootNode = new Node(nullptr, {nullptr, nullptr, nullptr}, game);
}

Tree::~Tree()
{
    if (rootNode)
    {
        delete rootNode;
    }
}

unsigned int Tree::begin()
{
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
                const unsigned int id = game->getPlayerToPlay();
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

    return rootNode->visits;
}

game::Move Tree::bestMove() const
{
    return rootNode->nodeWithMaxVisits()->getMove();
}

} // namespace mcts