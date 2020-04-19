#include "MCTS.hpp"

namespace mcts
{

template <class CellT, class PlayerT, class PawnT>
MCTS<CellT, PlayerT, PawnT>::MCTS(
    game::AbstractGame<CellT, PlayerT, PawnT> *game,
    mcts::Tree<CellT, PlayerT, PawnT> *tree,
    const MCTSConstraints &constraints)
    : constraints(constraints),
      game(game),
      tree(tree)
{
}

template <class CellT, class PlayerT, class PawnT>
MCTS<CellT, PlayerT, PawnT>::~MCTS()
{
}

template <class CellT, class PlayerT, class PawnT>
void MCTS<CellT, PlayerT, PawnT>::begin()
{
    timer t;
    root = tree->getRootNode();

    while (t.milliseconds_elapsed() < (unsigned long)constraints.time)
    {
        for (int ii = 0; ii < NUMBER_ITERATIONS_BEFORE_CHECKING_CHRONO; ++ii)
        {
            //std::cout << "Selection" << std::endl;
            Node<CellT, PawnT> *promisingNode = selectBestChildAndDoAction(root);

            //std::cout << "Expand" << std::endl;
            if (!game->isFinished())
            {

                expandNode(promisingNode);
            }

            //std::cout << "Random" << std::endl;
            Node<CellT, PawnT> *nodeToExplore = randomChooseChildOrFallbackOnNode(promisingNode);

            //std::cout << "Do Action" << std::endl;
            if (nodeToExplore != promisingNode)
            {
                doActionOnBoard(*nodeToExplore);
            }

            //std::cout << "Simulation" << std::endl;
            int winnerId = randomSimulation();

            //std::cout << "Backprop" << std::endl;
            backPropagateAndRevertAction(winnerId, nodeToExplore);
        }
    }

    DEBUG(root->visits);
}

template <class CellT, class PlayerT, class PawnT>
void MCTS<CellT, PlayerT, PawnT>::expandNode(Node<CellT, PawnT> *nodeToExpand)
{
    // the turn has already been played, now it's the next player's turn
    game::AbstractPlayer *nextPlayer = game->getPlayerToPlay();

    for (game::AbstractBoardCell *move : game->board->getAvailableCells())
    {
        Node<CellT, PawnT> *node = new Node<CellT, PawnT>();
        node->parent = nodeToExpand;
        node->player = nextPlayer;
        node->targetedCell = move;

        nodeToExpand->childNodes.push_back(node);
    }
}

template <class CellT, class PlayerT, class PawnT>
double MCTS<CellT, PlayerT, PawnT>::formula(
    const Node<CellT, PawnT> &node,
    const Node<CellT, PawnT> &nodeSuccessor) const
{
    double ret = std::numeric_limits<double>::max();
    if (nodeSuccessor.visits != 0)
    {
        ret = nodeSuccessor.score / (double)nodeSuccessor.visits +
              sqrt(2.0 * log((double)node.visits) / (double)nodeSuccessor.visits);
    }

    return ret;
}

template <class CellT, class PlayerT, class PawnT>
void MCTS<CellT, PlayerT, PawnT>::doActionOnBoard(const Node<CellT, PawnT> &nodeToGetTheActionFrom)
{
    game->play(nodeToGetTheActionFrom.player,
               nodeToGetTheActionFrom.targetedCell);
}

template <class CellT, class PlayerT, class PawnT>
game::AbstractBoardCell *MCTS<CellT, PlayerT, PawnT>::getRandomAvailableCellFromBoard() const
{
    std::vector<game::AbstractBoardCell *> cells = game->board->getAvailableCells();
    // random index ranging between 0 and cells.size() not included; (eg. 0 and 3, 3 not included)
    if (cells.size() == 0)
        throw - 1;
    unsigned int index = rand() % cells.size();

    return cells[index];
}

template <class CellT, class PlayerT, class PawnT>
void MCTS<CellT, PlayerT, PawnT>::backPropagateAndRevertAction(int winnerId, Node<CellT, PawnT> *terminalNode)
{
    Node<CellT, PawnT> *node = terminalNode;

    // iterate until the root node, not excluded tho!
    do
    {
        double increment = INCREMENT_DEFEAT;
        if ((int)node->player->getId() == winnerId)
        { // victory
            increment = INCREMENT_VICTORY;
        }
        else if (winnerId == -1)
        { // draw
            increment = INCREMENT_DRAW;
        }
        node->visits++;

        node->score += increment;
        if (node->parent)
        { // make sure we don't play the rootnode, otherwise things will get messy very quickly!
            game->revertPlay(node->targetedCell);
        }

    } while ((node = node->parent) != nullptr);
}

template <class CellT, class PlayerT, class PawnT>
Node<CellT, PawnT> *MCTS<CellT, PlayerT, PawnT>::randomChooseChildOrFallbackOnNode(Node<CellT, PawnT> *node) const
{
    Node<CellT, PawnT> *ret = node;
    if (node->childNodes.size() != 0)
    {
        unsigned int index = rand() % node->childNodes.size();
        ret = node->childNodes[index];
    }

    return ret;
}

template <class CellT, class PlayerT, class PawnT>
int MCTS<CellT, PlayerT, PawnT>::randomSimulation() const
{
    // save the actions done so we can revert them;
    std::queue<game::AbstractBoardCell *> playedCells;

    while (!game->isFinished())
    {
        try
        {
            game::AbstractBoardCell *cell = getRandomAvailableCellFromBoard();
            game->play(
                game->getPlayerToPlay(),
                cell);
            playedCells.push(cell);
        }
        catch (int code)
        {
        }
    }

    // check the victory
    int winner = game->checkStatus();

    // revert the random game
    while (!playedCells.empty())
    {
        game->revertPlay(playedCells.front());
        // remove the element
        playedCells.pop();
    }

    return winner;
}

template <class CellT, class PlayerT, class PawnT>
Node<CellT, PawnT> *MCTS<CellT, PlayerT, PawnT>::selectBestChildAndDoAction(Node<CellT, PawnT> *input)
{
    Node<CellT, PawnT> *ret = input;

    if (!ret->isRoot)
    {
        doActionOnBoard(*ret);
    }

    while (ret->childNodes.size() != 0)
    {
        Node<CellT, PawnT> *interestingToReturn = nullptr;
        double interestingValue = std::numeric_limits<double>::lowest();

        // One child must be selected to further develop
        for (Node<CellT, PawnT> *node : ret->childNodes)
        {
            double res = formula(
                *ret,
                *node);

            if (res > interestingValue)
            {
                // update ret
                interestingValue = res;
                interestingToReturn = node;
            }
        }

        // exclude the root node that doesn't have any action associated...
        if (!interestingToReturn->isRoot)
        {
            doActionOnBoard(*interestingToReturn);
        }
        ret = interestingToReturn;
    }

    return ret;
}

} // namespace mcts