#pragma message("iostream shouldn't be included here!")
#include <iostream>
#include <assert.h>

#include "../game_logic/AbstractGame.hpp"
#include "../game_logic/AbstractBoard.hpp"

#include "../game_logic/tic_tac_toe/BoardCell.hpp"
#include "../game_logic/tic_tac_toe/Player.hpp"

#include "../game_logic/penguin/BoardCell.hpp"
#include "../game_logic/penguin/HumanPlayer.hpp"
#include "../game_logic/penguin/PenguinPawn.hpp"

#include "Tree.hpp"

#include "../dbg.h"

namespace mcts
{

template <class CellT, class PlayerT, class PawnT>
Tree<CellT, PlayerT, PawnT>::Tree(
    game::AbstractGame<CellT, PlayerT, PawnT> *game,
    const MCTSConstraints &constraints)
    : game(game),
      constraints(constraints)
{
    rootNode = new Node<CellT, PawnT>();
    rootNode->isRoot = true;
}

template <class CellT, class PlayerT, class PawnT>
Tree<CellT, PlayerT, PawnT>::~Tree()
{
    if (rootNode)
        delete rootNode;
}

// template <class CellT, class PlayerT, class PawnT>
// size_t Tree<CellT, PlayerT, PawnT>::begin( )
// {
//     timer t;
//     while (t.milliseconds_elapsed() < static_cast<unsigned long>(constraints.time))
//     {
//         for (int ii = 0; ii < NUMBER_ITERATIONS_BEFORE_CHECKING_CHRONO; ++ii)
//         {
//             Node<CellT, PawnT> *promisingNode = selectBestChildAndDoAction(&rootNode);

//             if (!game->isFinished() && promisingNode->childNodes.size() == 0)
//             {
//                 expandNode(promisingNode);
//             }

//             Node<CellT, PawnT> *nodeToExplore = randomChooseChildOrFallbackOnNode(promisingNode);

//             if (nodeToExplore != promisingNode)
//             {
//                 doActionOnBoard(*nodeToExplore);
//             }

//             int winnerId = randomSimulation();

//             backPropagateAndRevertAction(winnerId, nodeToExplore);
//         }
//     }

//     return rootNode->visits;
// }

// template <class CellT, class PlayerT, class PawnT>
// void Tree<CellT, PlayerT, PawnT>::expandNode(Node<CellT, PawnT> *nodeToExpand)
// {
//     // the turn has already been played, now it's the next player's turn
//     PlayerT *player = game->board->getPlayerById(game->getPlayerToPlay());

//     for (const game::Move<CellT, PawnT> &move : game->getAvailableMoves(player))
//     {
//         Node<CellT, PawnT> *node = new Node<CellT, PawnT>();
//         node->parent = nodeToExpand;
//         node->move = move;

//         nodeToExpand->childNodes.push_back(node);
//     }
// }

template <class CellT, class PlayerT, class PawnT>
game::Move<CellT, PawnT> Tree<CellT, PlayerT, PawnT>::bestMove() const
{
    return nodeWithMaxVisits(rootNode)->move;
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

// template <class CellT, class PlayerT, class PawnT>
// double Tree<CellT, PlayerT, PawnT>::formula(
//     const Node<CellT, PawnT> &node,
//     const Node<CellT, PawnT> &nodeSuccessor) const
// {
//     double ret = std::numeric_limits<double>::max();
//     if (nodeSuccessor.visits != 0)
//     {
//         ret = nodeSuccessor.score / static_cast<double>(nodeSuccessor.visits) +
//               sqrt(2.0 * log(static_cast<double>(node.visits)) / static_cast<double>(nodeSuccessor.visits));
//     }

//     return ret;
// }

// template <class CellT, class PlayerT, class PawnT>
// void Tree<CellT, PlayerT, PawnT>::doActionOnBoard(const Node<CellT, PawnT> &nodeToGetTheActionFrom)
// {
//     game->play(nodeToGetTheActionFrom.move.pawn,
//                nodeToGetTheActionFrom.move.target);
// }

// template <class CellT, class PlayerT, class PawnT>
// const game::Move<CellT, PawnT> Tree<CellT, PlayerT, PawnT>::getRandomAvailableMoveFromBoard(const unsigned int &player_id) const
// {
//     std::vector<game::Move<CellT, PawnT>> cells = game->getAvailableMoves(game->board->getPlayerById(player_id));
//     // random index ranging between 0 and cells.size() not included; (eg. 0 and 3, 3 not included)
//     unsigned int index = rand() % cells.size();

//     return cells[index];
// }

// template <class CellT, class PlayerT, class PawnT>
// void Tree<CellT, PlayerT, PawnT>::backPropagateAndRevertAction(int winnerId, Node<CellT, PawnT> *terminalNode)
// {
//     Node<CellT, PawnT> *node = terminalNode;

//     // iterate until the root node, not excluded tho!
//     do
//     {
//         node->visits++;
//         if (!node->isRoot)
//         {
//             double increment = INCREMENT_DEFEAT;
//             if (static_cast<int>(node->move.pawn->getOwner()->getId()) == winnerId)
//             { // victory
//                 increment = INCREMENT_VICTORY;
//             }
//             else if (winnerId == -1)
//             { // draw
//                 increment = INCREMENT_DRAW;
//             }
//             node->score += increment;

//             if (node->parent)
//             { // make sure we don't play the rootnode, otherwise things will get messy very quickly!
//                 game->revertPlay();
//             }
//         }

//     } while ((node = node->parent) != nullptr);
//     //std::cout << "--------------------| Finished |----------------------" << std::endl;
// }

// template <class CellT, class PlayerT, class PawnT>
// Node<CellT, PawnT> *Tree<CellT, PlayerT, PawnT>::randomChooseChildOrFallbackOnNode(Node<CellT, PawnT> *node) const
// {
//     Node<CellT, PawnT> *ret = node;
//     if (node->childNodes.size() != 0)
//     {
//         unsigned int index = rand() % node->childNodes.size();
//         ret = node->childNodes[index];
//     }

//     return ret;
// }

// template <class CellT, class PlayerT, class PawnT>
// int Tree<CellT, PlayerT, PawnT>::randomSimulation() const
// {
//     size_t number_games_played = 0;
//     while (!game->isFinished())
//     {
//         const game::Move<CellT, PawnT> move = getRandomAvailableMoveFromBoard(game->getPlayerToPlay());
//         game->play(
//             move.pawn,
//             move.target);
//         ++number_games_played;
//     }

//     // check the victory
//     int winner = game->checkStatus();

//     // revert the random game
//     while (number_games_played-- > 0)
//     {
//         game->revertPlay();
//     }

//     return winner;
// }

// template <class CellT, class PlayerT, class PawnT>
// Node<CellT, PawnT> *Tree<CellT, PlayerT, PawnT>::selectBestChildAndDoAction(Node<CellT, PawnT> *input)
// {
//     Node<CellT, PawnT> *ret = input;

//     //if (ret->parent != nullptr)
//     if (!ret->isRoot)
//     {
//         doActionOnBoard(*ret);
//     }

//     while (ret->childNodes.size() != 0)
//     {
//         Node<CellT, PawnT> *interestingToReturn = nullptr;
//         double interestingValue = std::numeric_limits<double>::lowest();

//         // One child must be selected to further develop
//         for (Node<CellT, PawnT> *node : ret->childNodes)
//         {
//             double res = formula(
//                 *ret,
//                 *node);

//             if (res > interestingValue)
//             {
//                 // update ret
//                 interestingValue = res;
//                 interestingToReturn = node;
//             }
//         }

//         // exclude the root node that doesn't have any action associated...
//         //if (interestingToReturn->parent != nullptr)
//         if (!interestingToReturn->isRoot)
//         {
//             doActionOnBoard(*interestingToReturn);
//         }
//         ret = interestingToReturn;
//     }

//     return ret;
// }

template <class CellT, class PlayerT, class PawnT>
void Tree<CellT, PlayerT, PawnT>::moveRootToMove(const game::Move<CellT, PawnT> &move)
{
    {
        std::vector<game::Move<CellT, PawnT>> moves = game->getAvailableMoves(game->board->getPlayerById(move.pawn->getOwner()->getId()));
        const auto &it = std::find_if(
            std::begin(moves),
            std::end(moves),
            [move](const game::Move<CellT, PawnT> &move_testing) -> bool { return move == move_testing; });

        assert("The cell we are trying to play on is inexistant in the tree's game version" && it != std::end(moves));
        if (it != std::end(moves))
        {
            game->play(it->pawn, it->target);
        }
    }
    {
        const auto &nextRoot = std::find_if(
            std::begin(rootNode->childNodes),
            std::end(rootNode->childNodes),
            [move](Node<CellT, PawnT> *&node) -> bool { return node->move == move; });

        if (nextRoot != std::end(rootNode->childNodes))
        {
            rootNode->childNodes.erase(std::remove_if(
                std::begin(rootNode->childNodes),
                std::end(rootNode->childNodes),
                [move](Node<CellT, PawnT> *&node) -> bool { return node->move == move; }));

            if (rootNode)
                delete rootNode;

            rootNode = *nextRoot;
            rootNode->parent = nullptr;
            rootNode->move = {nullptr, nullptr, nullptr};
            rootNode->isRoot = true;
        }
    }

    //     for (const auto &node : rootNode->childNodes)
    //     // while (rootNode->childNodes.size() != 0)
    //     //for(unsigned long i = 0; i < rootNode->childNodes.size(); i++)
    //     {
    //         // Node<CellT, PawnT> *n = rootNode->childNodes.back();
    //         //Node* n = rootNode->childNodes.at(i);
    //         // rootNode->childNodes.pop_back();

    //         if (node->move == move)
    //         {
    //             assert(*node->move.target == *move.target);
    //             nextRoot = node;
    //         }
    //     }

    //     if (nextRoot)
    //     {
    //         rootNode->childNodes.clear();
    //         if (rootNode)
    //             delete rootNode;

    //         rootNode = nextRoot;
    //         rootNode->parent = nullptr;
    //         rootNode->move = {nullptr, nullptr, nullptr};
    //         rootNode->isRoot = true;
    //     }
    // }
    // }
}

template <class CellT, class PlayerT, class PawnT>
void Tree<CellT, PlayerT, PawnT>::merge(Tree *tree)
{
    //First, merge the rootNodes
    rootNode->visits += tree->rootNode->visits;
    rootNode->score += tree->rootNode->score;
    //If the current rootNode doesn't have any children, then make a clone of all children of tree
    //and add them to rootNode->childNodes
    if (rootNode->childNodes.size() == 0)
    {
        for (Node<CellT, PawnT> *node : tree->rootNode->childNodes)
        {
            Node<CellT, PawnT> *new_node = new Node<CellT, PawnT>();
            new_node->score = node->score;
            new_node->visits = node->visits;
            new_node->move = node->move;
            rootNode->childNodes.push_back(new_node);
        }
    }
    else
    //find the corresponding cell and add all visits and scores
    {
        for (auto child : rootNode->childNodes)
        {
            for (auto check_child : tree->rootNode->childNodes)
            {
                // if (child->targetedCell->equals(check_child->targetedCell))
                if (*child->move.target == *check_child->move.target)
                {
                    child->score += check_child->score;
                    child->visits += check_child->visits;
                }
            }
        }
    }
}

template <class CellT, class PlayerT, class PawnT>
Node<CellT, PawnT> &Tree<CellT, PlayerT, PawnT>::getRootNode()
{
    return *rootNode;
}

template class Tree<game::tic_tac_toe::BoardCell, game::tic_tac_toe::Player, game::tic_tac_toe::Player>;
template class Tree<game::penguin::BoardCell, game::penguin::HumanPlayer, game::penguin::PenguinPawn>;

} // namespace mcts