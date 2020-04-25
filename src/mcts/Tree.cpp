#include <algorithm>
#include <assert.h>

#include "../game_logic/AbstractGame.hpp"
#include "../game_logic/AbstractBoard.hpp"

#include "../game_logic/tic_tac_toe/BoardCell.hpp"
#include "../game_logic/tic_tac_toe/Player.hpp"

#include "../game_logic/penguin/BoardCell.hpp"
#include "../game_logic/penguin/HumanPlayer.hpp"
#include "../game_logic/penguin/PenguinPawn.hpp"

#include "Tree.hpp"

#define THREAD_NUMBER 4

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

template <class CellT, class PlayerT, class PawnT>
void Tree<CellT, PlayerT, PawnT>::moveRootToMove(const game::Move<CellT, PawnT> &move)
{
    if (rootNode->childNodes.size() > 0) // make sure the tree has been initiated
    {
        const auto &nextRoot = std::find_if(
            std::begin(rootNode->childNodes),
            std::end(rootNode->childNodes),
            [move](Node<CellT, PawnT> *&node) -> bool { return node->move == move; });
        // TODO current cell is not the right one !!!
        assert("There must be a branch/leaf selected because it has been developed already!" && nextRoot != std::end(rootNode->childNodes));

        if (nextRoot != std::end(rootNode->childNodes))
        {
            Node<CellT, PawnT> *next_root_node = *nextRoot;
            rootNode->childNodes.erase(std::remove_if(
                std::begin(rootNode->childNodes),
                std::end(rootNode->childNodes),
                [next_root_node](Node<CellT, PawnT> *&node) -> bool { return node == next_root_node; }));

            if (rootNode)
                delete rootNode;

            rootNode = next_root_node;
            rootNode->parent = nullptr;
            rootNode->move = {nullptr, nullptr, nullptr};
            rootNode->isRoot = true;
        } 
        std::vector<game::Move<CellT, PawnT>> moves = game->getAvailableMoves(game->board->getPlayerById(move.pawn->getOwner()->getId()));
        const auto &it = std::find_if(
            std::begin(moves),
            std::end(moves),
            [move](const game::Move<CellT, PawnT> &move_testing) -> bool { return move == move_testing; });

        //assert("The cell we are trying to play on is inexistant in the tree's game version" && it != std::end(moves));
        if (it != std::end(moves))
        {
            #ifndef NDEBUG
            bool ret = game->play(it->pawn, it->target);
            assert(ret == true);
            #else
            game->play(it->pawn, it->target);
            #endif
        }
    }
}

template <class CellT, class PlayerT, class PawnT>
void Tree<CellT, PlayerT, PawnT>::merge(const Tree *const& tree)
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
            // new_node->move = node->move;

            game::Move<CellT, PawnT> &move = node->move;
            std::vector<game::Move<CellT, PawnT>> moves = game->getAvailableMoves(game->board->getPlayerById(node->move.pawn->getOwner()->getId()));
            const auto &it = std::find_if(
                std::begin(moves),
                std::end(moves),
                [move](const game::Move<CellT, PawnT> &move_testing) -> bool { return move == move_testing; });
            
            assert("The cell we are trying to play on is inexistant in the tree's game version" && it != std::end(moves));
            if (it != std::end(moves))
            {
                new_node->move = *it;
            }

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
                if (child->move == check_child->move)
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