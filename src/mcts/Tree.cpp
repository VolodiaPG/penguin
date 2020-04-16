#include "../game_logic/AbstractBoard.hpp"
#include "../game_logic/AbstractBoardCell.hpp"
#include "../game_logic/AbstractGame.hpp"
#include "../game_logic/AbstractPlayer.hpp"
#include "Node.hpp"

#include "Tree.hpp"

namespace mcts
{

template <class CellT, class PlayerT, class PawnT>
Tree<CellT, PlayerT, PawnT>::Tree(
    game::AbstractGame<CellT, PlayerT, PawnT> *game,
    const MCTSConstraints &constraints)
    :
      game(game),
      constraints(constraints)
{
    rootNode = new Node<CellT, PlayerT, PawnT>(nullptr, {nullptr, nullptr, nullptr}, game);
}

template <class CellT, class PlayerT, class PawnT>
Tree<CellT, PlayerT, PawnT>::~Tree()
{
    if (rootNode)
    {
        delete rootNode;
    }
}

template <class CellT, class PlayerT, class PawnT>
unsigned int Tree<CellT, PlayerT, PawnT>::begin()
{
    timer t;
    while (t.milliseconds_elapsed() < (unsigned long)constraints.time
           // && !rootNode->getIsFullyDone()
    )
    {
        for (int ii = 0; ii < NUMBER_ITERATIONS_BEFORE_CHECKING_CHRONO; ++ii)
        {
            Node<CellT, PlayerT, PawnT> *promisingNode = rootNode->selectBestChildAndDoAction();

            if (!game->isFinished())
            {
                const unsigned int id = game->getPlayerToPlay();
                promisingNode->expandNode(game->getAvailableMoves(game->board->getPlayerById(id)));
            }

            Node<CellT, PlayerT, PawnT> *nodeToExplore = promisingNode->randomChooseChildOrDefaultMe();

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

template <class CellT, class PlayerT, class PawnT>
game::Move<CellT, PawnT> Tree<CellT, PlayerT, PawnT>::bestMove() const
{
    return rootNode->nodeWithMaxVisits()->getMove();
}

} // namespace mcts