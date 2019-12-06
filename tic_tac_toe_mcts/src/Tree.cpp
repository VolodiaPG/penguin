#include "Tree.hpp"

namespace mcts
{

Tree::Tree(game::AbstractGame *game, game::AbstractPlayer *me, const MCTSConstraints &constraints)
    : playerMe(me),
      game(game),
      constraints(constraints)
{
    rootNode = new Node(nullptr, me, nullptr, game);
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
                promisingNode->expandNode(
                    game->board->getAvailableCells(),
                    game->getPlayerToPlay());
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

game::AbstractBoardCell *Tree::bestMove() const
{
    return rootNode->nodeWithMaxVisits()->getTargetedCell();
}

double Tree::formula(
    const Node_bis &node,
    const Node_bis &nodeSuccessor) const
{
    double ret = std::numeric_limits<double>::max();
    if (nodeSuccessor.visits != 0)
    {
        ret = (double)nodeSuccessor.score / (double)nodeSuccessor.visits +
              sqrt(2.0 * log((double)node.visits) / (double)nodeSuccessor.visits);
    }

    return ret;
}

void Tree::doActionOnBoard(const Node_bis &nodeToGetTheActionFrom)
{
    game->play(&nodeToGetTheActionFrom.player,
               &nodeToGetTheActionFrom.targetedCell);
}

game::AbstractBoardCell &Tree::getRandomAvailableCellFromBoard() const
{
    std::vector<game::AbstractBoardCell *> cells = game->board->getAvailableCells();

    // random index ranging between 0 and cells.size() not included; (eg. 0 and 3, 3 not included)
    unsigned int index = rand() % cells.size();

    return *cells[index];
}

void Tree::backPropagateAndRevertAction(Node_bis &terminalNode)
{
    int stateOfGame = game->checkStatus();

    Node_bis *node = &terminalNode;
    do
    {
        ++node->visits;
        if ((int)node->player.getId() == stateOfGame)
        {
            node->score += INCREMENT_VICTORY;
        }
        else if (stateOfGame == -1)
        {
            node->score += INCREMENT_DRAW;
        }
        else
        {
            node->score += INCREMENT_DEFEAT;
        }

        game->revertPlay(&node->targetedCell);

    } while ((node = node->parent) != nullptr);
}

Node_bis *Tree::randomChooseChildOrFallbackOnNode(Node_bis *node)
{
    Node_bis *ret = node;
    if (node->childNodes.size())
    {
        unsigned int index = rand() % node->childNodes.size();
        ret = node->childNodes[index];
    }

    return ret;
}

} // namespace mcts