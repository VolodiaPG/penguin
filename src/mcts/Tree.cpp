#pragma message("iostream shouldn't be included here!")
#include <iostream>

#include "Tree.hpp"

namespace mcts
{

template <class CellT, class PlayerT, class PawnT>
Tree<CellT, PlayerT, PawnT>::Tree(
    game::AbstractGame<CellT, PlayerT, PawnT> *game,
    const MCTSConstraints &constraints)
    : game(game),
      constraints(constraints)
{
    rootNode.isRoot = true;
}

template <class CellT, class PlayerT, class PawnT>
Tree<CellT, PlayerT, PawnT>::~Tree()
{
}

template <class CellT, class PlayerT, class PawnT>
void Tree<CellT, PlayerT, PawnT>::begin()
{
    std::cout << "Beginning MCTS search" << std::endl;
    timer t;
    while (t.milliseconds_elapsed() < (unsigned long)constraints.time)
    {
        for (int ii = 0; ii < NUMBER_ITERATIONS_BEFORE_CHECKING_CHRONO; ++ii)
        {
            Node<CellT, PawnT> *promisingNode = selectBestChildAndDoAction(&rootNode);

            if (!game->isFinished() && promisingNode->childNodes.size() == 0)
            {
                expandNode(promisingNode);
            }

            Node<CellT, PawnT> *nodeToExplore = randomChooseChildOrFallbackOnNode(promisingNode);

            if (nodeToExplore != promisingNode)
            {
                doActionOnBoard(*nodeToExplore);
            }

            int winnerId = randomSimulation();

            backPropagateAndRevertAction(winnerId, nodeToExplore);
        }
    }

    DEBUG(rootNode.visits);
}

template <class CellT, class PlayerT, class PawnT>
void Tree<CellT, PlayerT, PawnT>::expandNode(Node<CellT, PawnT> *nodeToExpand)
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
game::AbstractBoardCell *Tree<CellT, PlayerT, PawnT>::bestMove() const
{
    return nodeWithMaxVisits(&rootNode)->targetedCell;
}

template <class CellT, class PlayerT, class PawnT>
Node<CellT, PawnT> *Tree<CellT, PlayerT, PawnT>::nodeWithMaxVisits(const Node<CellT, PawnT> *nodeFrom) const
{
    Node<CellT, PawnT> *chosen = nullptr;
    int max = -1;

    for (Node<CellT, PawnT> *node : nodeFrom->childNodes)
    {
        if (node->visits > max)
        {
            max = node->visits;
            chosen = node;
        }
    }

    return chosen;
}

template <class CellT, class PlayerT, class PawnT>
double Tree<CellT, PlayerT, PawnT>::formula(
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
void Tree<CellT, PlayerT, PawnT>::doActionOnBoard(const Node<CellT, PawnT> &nodeToGetTheActionFrom)
{
    game->play(nodeToGetTheActionFrom.player,
               nodeToGetTheActionFrom.targetedCell);
}

template <class CellT, class PlayerT, class PawnT>
game::AbstractBoardCell *Tree<CellT, PlayerT, PawnT>::getRandomAvailableCellFromBoard() const
{
    std::vector<game::AbstractBoardCell *> cells = game->board->getAvailableCells();
    // random index ranging between 0 and cells.size() not included; (eg. 0 and 3, 3 not included)
    unsigned int index = rand() % cells.size();

    return cells[index];
}

template <class CellT, class PlayerT, class PawnT>
void Tree<CellT, PlayerT, PawnT>::backPropagateAndRevertAction(int winnerId, Node<CellT, PawnT> *terminalNode)
{
    Node<CellT, PawnT> *node = terminalNode;

    // iterate until the root node, not excluded tho!
    //std::cout << "--------------------| Starting |----------------------" << std::endl;
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
            //std::cout << node->targetedCell->to_string() << std::endl;
            //if(node->parent->targetedCell)
            //    std::cout << node->parent->targetedCell->to_string() << std::endl;
        }

    } while ((node = node->parent) != nullptr);
    //std::cout << "--------------------| Finished |----------------------" << std::endl;
}

template <class CellT, class PlayerT, class PawnT>
Node<CellT, PawnT> *Tree<CellT, PlayerT, PawnT>::randomChooseChildOrFallbackOnNode(Node<CellT, PawnT> *node) const
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
int Tree<CellT, PlayerT, PawnT>::randomSimulation() const
{
    // save the actions done so we can revert them;
    std::queue<game::AbstractBoardCell *> playedCells;

    while (!game->isFinished())
    {
        game::AbstractBoardCell *cell = getRandomAvailableCellFromBoard();
        game->play(
            game->getPlayerToPlay(),
            cell);
        playedCells.push(cell);
    }

    // check the victory
    int winner = game->checkStatus();

    // revert the random game
    //std::cout << "--------------------| Starting |----------------------" << std::endl;
    //std::cout << "Winner : " << winner << std::endl;
    while (!playedCells.empty())
    {
        game->revertPlay(playedCells.front());
        // remove the element
        playedCells.pop();
    }
    //std::cout << "--------------------| Finished |----------------------" << std::endl;

    return winner;
}

template <class CellT, class PlayerT, class PawnT>
Node<CellT, PawnT> *Tree<CellT, PlayerT, PawnT>::selectBestChildAndDoAction(Node<CellT, PawnT> *input)
{
    Node<CellT, PawnT> *ret = input;

    //if (ret->parent != nullptr)
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
        //if (interestingToReturn->parent != nullptr)
        if (!interestingToReturn->isRoot)
        {
            doActionOnBoard(*interestingToReturn);
        }
        ret = interestingToReturn;
    }

    return ret;
}

template <class CellT, class PlayerT, class PawnT>
void Tree<CellT, PlayerT, PawnT>::moveRootToCell(game::AbstractBoardCell *cell)
{
    Node<CellT, PawnT> *nextRoot = nullptr;

    while (rootNode.childNodes.size() != 0)
    //for(unsigned long i = 0; i < rootNode.childNodes.size(); i++)
    {
        Node<CellT, PawnT> *n = rootNode.childNodes.back();
        //Node* n = rootNode.childNodes.at(i);
        rootNode.childNodes.pop_back();
        if (n->targetedCell == cell)
        {
            nextRoot = n;
        }
        else
        {
            delete n;
        }
    }
    if (nextRoot != nullptr)
    {
        rootNode = *nextRoot;
        rootNode.parent = nullptr;
        rootNode.targetedCell = nullptr;
        rootNode.isRoot = true;
        for (unsigned long i = 0; i < rootNode.childNodes.size(); i++)
        {
            rootNode.childNodes.at(i)->parent = &rootNode;
        }
    }
}

} // namespace mcts