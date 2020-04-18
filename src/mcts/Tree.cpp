#pragma message("iostream shouldn't be included here!")
#include <iostream>

#include "../game_logic/AbstractGame.hpp"
#include "../game_logic/AbstractBoard.hpp"

#include "../game_logic/tic_tac_toe/BoardCell.hpp"
#include "../game_logic/tic_tac_toe/Player.hpp"

#include "../game_logic/penguin/BoardCell.hpp"
#include "../game_logic/penguin/HumanPlayer.hpp"
#include "../game_logic/penguin/PenguinPawn.hpp"

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
size_t Tree<CellT, PlayerT, PawnT>::begin()
{
    timer t;
    while (t.milliseconds_elapsed() < static_cast<unsigned long>(constraints.time))
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

    return rootNode.visits;
}

template <class CellT, class PlayerT, class PawnT>
void Tree<CellT, PlayerT, PawnT>::expandNode(Node<CellT, PawnT> *nodeToExpand)
{
    // the turn has already been played, now it's the next player's turn
    PlayerT* player = game->board->getPlayerById(game->getPlayerToPlay());

    for (const game::Move<CellT, PawnT> &move : game->getAvailableMoves(player))
    {
        Node<CellT, PawnT> *node = new Node<CellT, PawnT>();
        node->parent = nodeToExpand;
        node->move = move;

        nodeToExpand->childNodes.push_back(node);
    }
}

template <class CellT, class PlayerT, class PawnT>
game::Move<CellT, PawnT> Tree<CellT, PlayerT, PawnT>::bestMove() const
{
    return nodeWithMaxVisits(&rootNode)->move;
}

template <class CellT, class PlayerT, class PawnT>
Node<CellT, PawnT> *Tree<CellT, PlayerT, PawnT>::nodeWithMaxVisits(const Node<CellT, PawnT> *nodeFrom) const
{
    Node<CellT, PawnT> *chosen = nullptr;
    int max = -std::numeric_limits<int>::max();

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
        ret = nodeSuccessor.score / static_cast<double>(nodeSuccessor.visits) +
              sqrt(2.0 * log(static_cast<double>(node.visits)) / static_cast<double>(nodeSuccessor.visits));
    }

    return ret;
}

template <class CellT, class PlayerT, class PawnT>
void Tree<CellT, PlayerT, PawnT>::doActionOnBoard(const Node<CellT, PawnT> &nodeToGetTheActionFrom)
{
    game->play(nodeToGetTheActionFrom.move.pawn,
               nodeToGetTheActionFrom.move.target);
}

template <class CellT, class PlayerT, class PawnT>
const game::Move<CellT, PawnT> Tree<CellT, PlayerT, PawnT>::getRandomAvailableMoveFromBoard(const unsigned int &player_id) const
{
    std::vector<game::Move<CellT, PawnT>> cells = game->getAvailableMoves(game->board->getPlayerById(player_id));
    // random index ranging between 0 and cells.size() not included; (eg. 0 and 3, 3 not included)
    unsigned int index = rand() % cells.size();

    return cells[index];
}

template <class CellT, class PlayerT, class PawnT>
void Tree<CellT, PlayerT, PawnT>::backPropagateAndRevertAction(int winnerId, Node<CellT, PawnT> *terminalNode)
{
    Node<CellT, PawnT> *node = terminalNode;

    // iterate until the root node, not excluded tho!
    do
    {
        node->visits++;
        if (!node->isRoot)
        {
            double increment = INCREMENT_DEFEAT;
            if (static_cast<int>(node->move.pawn->getOwner()->getId()) == winnerId)
            { // victory
                increment = INCREMENT_VICTORY;
            }
            else if (winnerId == -1)
            { // draw
                increment = INCREMENT_DRAW;
            }
            node->score += increment;

            if (node->parent)
            { // make sure we don't play the rootnode, otherwise things will get messy very quickly!
                game->revertPlay();
            }
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
    size_t number_games_played = 0;
    while (!game->isFinished())
    {
        const game::Move<CellT, PawnT> move = getRandomAvailableMoveFromBoard(game->getPlayerToPlay());
        game->play(
            move.pawn,
            move.target);
        ++number_games_played;
    }

    // check the victory
    int winner = game->checkStatus();

    // revert the random game
    while (number_games_played-- > 0)
    {
        game->revertPlay();
    }

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
void Tree<CellT, PlayerT, PawnT>::moveRootToMove(const game::Move<CellT, PawnT> &move)
{
    Node<CellT, PawnT> *nextRoot = nullptr;

    while (rootNode.childNodes.size() != 0)
    //for(unsigned long i = 0; i < rootNode.childNodes.size(); i++)
    {
        Node<CellT, PawnT> *n = rootNode.childNodes.back();
        //Node* n = rootNode.childNodes.at(i);
        rootNode.childNodes.pop_back();
        if (n->move == move)
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
        rootNode.move = {nullptr, nullptr, nullptr};
        rootNode.isRoot = true;
        for (unsigned long i = 0; i < rootNode.childNodes.size(); i++)
        {
            rootNode.childNodes.at(i)->parent = &rootNode;
        }
    }
}

template class Tree<game::tic_tac_toe::BoardCell, game::tic_tac_toe::Player, game::tic_tac_toe::Player>;
template class Tree<game::penguin::BoardCell, game::penguin::HumanPlayer, game::penguin::PenguinPawn>;

} // namespace mcts