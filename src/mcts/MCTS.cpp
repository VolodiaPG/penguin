#include <assert.h>

#include "../game_logic/AbstractBoard.hpp"

#include "../game_logic/tic_tac_toe/BoardCell.hpp"
#include "../game_logic/tic_tac_toe/Player.hpp"

#include "../game_logic/penguin/BoardCell.hpp"
#include "../game_logic/penguin/HumanPlayer.hpp"
#include "../game_logic/penguin/PenguinPawn.hpp"

#include "MCTS.hpp"

#include "../dbg.h"

namespace mcts
{

template <class CellT, class PlayerT, class PawnT>
MCTS<CellT, PlayerT, PawnT>::MCTS(
    mcts::Tree<CellT, PlayerT, PawnT> *&tree,
    const MCTSConstraints &constraints)
    : constraints(constraints),
      tree(tree)
{
}

template <class CellT, class PlayerT, class PawnT>
MCTS<CellT, PlayerT, PawnT>::~MCTS()
{
}

template <class CellT, class PlayerT, class PawnT>
size_t MCTS<CellT, PlayerT, PawnT>::begin()
{
    Node<CellT, PawnT> &rootNode = tree->getRootNode();
    timer t;
    while (t.milliseconds_elapsed() < static_cast<unsigned long>(constraints.time))
    {
        for (int ii = 0; ii < NUMBER_ITERATIONS_BEFORE_CHECKING_CHRONO; ++ii)
        {
            Node<CellT, PawnT> *promisingNode = selectBestChildAndDoAction(&rootNode);

            if (!tree->game->isFinished() && promisingNode->childNodes.size() == 0)
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

    dbg(rootNode.visits);
    return rootNode.visits;
}

template <class CellT, class PlayerT, class PawnT>
void MCTS<CellT, PlayerT, PawnT>::expandNode(Node<CellT, PawnT> *nodeToExpand)
{
    // the turn has already been played, now it's the next player's turn
    PlayerT *player = tree->game->board->getPlayerById(tree->game->getPlayerToPlay());

    for (const game::Move<CellT, PawnT> &move : tree->game->getAvailableMoves(player))
    {
        assert("The player that should be playing is not the one that owns the pawns" && player->getId() == move.pawn->getOwner()->getId());
        Node<CellT, PawnT> *node = new Node<CellT, PawnT>();
        node->parent = nodeToExpand;
        node->move = move;

        nodeToExpand->childNodes.push_back(node);
    }
}

template <class CellT, class PlayerT, class PawnT>
double MCTS<CellT, PlayerT, PawnT>::formula(
    const Node<CellT, PawnT> &node,
    const Node<CellT, PawnT> &nodeSuccessor) const
{
    // dbg(nodeSuccessor.score);
    // dbg(nodeSuccessor.visits);
    // dbg(node.visits);
    double ret = std::numeric_limits<double>::max();
    if (nodeSuccessor.visits != 0)
    {
        ret = nodeSuccessor.score / static_cast<double>(nodeSuccessor.visits) +
              sqrt(2.0 * log(static_cast<double>(node.visits)) / static_cast<double>(nodeSuccessor.visits));
    }

    return ret;
}

template <class CellT, class PlayerT, class PawnT>
void MCTS<CellT, PlayerT, PawnT>::doActionOnBoard(const Node<CellT, PawnT> &nodeToGetTheActionFrom)
{
    tree->game->play(nodeToGetTheActionFrom.move.pawn,
                     nodeToGetTheActionFrom.move.target);
    // tree->game->play(nodeToGetTheActionFrom.player,
    //            nodeToGetTheActionFrom.targetedCell);
}

template <class CellT, class PlayerT, class PawnT>
const game::Move<CellT, PawnT> MCTS<CellT, PlayerT, PawnT>::getRandomAvailableMoveFromBoard(const unsigned int &player_id) const
{
    std::vector<game::Move<CellT, PawnT>> cells = tree->game->getAvailableMoves(tree->game->board->getPlayerById(player_id));
    // random index ranging between 0 and cells.size() not included; (eg. 0 and 3, 3 not included)
    unsigned int index = rand() % cells.size();

    return cells[index];

    // std::vector<game::AbstractBoardCell *> cells = tree->game->board->getAvailableCells();
    // // random index ranging between 0 and cells.size() not included; (eg. 0 and 3, 3 not included)
    // if (cells.size() == 0)
    //     throw - 1;
    // unsigned int index = rand() % cells.size();

    // return cells[index];
}

template <class CellT, class PlayerT, class PawnT>
void MCTS<CellT, PlayerT, PawnT>::backPropagateAndRevertAction(int winnerId, Node<CellT, PawnT> *terminalNode)
{
    Node<CellT, PawnT> *node = terminalNode;
    double increment = 0;

    while (!node->isRoot)
    {
        increment = INCREMENT_DEFEAT;
        if (static_cast<int>(node->move.pawn->getOwner()->getId()) == winnerId)
        { // victory
            increment = INCREMENT_VICTORY;
        }
        else if (winnerId == -1)
        { // draw
            increment = INCREMENT_DRAW;
        }

        ++node->visits;
        node->score += increment;

        tree->game->revertPlay();

        node = node->parent;
    }

    ++node->visits;
    node->score += increment; // node score is incremented the same as its children (playing for him)

    // iterate until the root node, not excluded tho!
    // do
    // {
    //     node->visits++;
    //     // if (!node->isRoot)
    //     // {
    //     double increment = INCREMENT_DEFEAT;
    //     if (static_cast<int>(node->move.pawn->getOwner()->getId()) == winnerId)
    //     { // victory
    //         increment = INCREMENT_VICTORY;
    //     }
    //     else if (winnerId == -1)
    //     { // draw
    //         increment = INCREMENT_DRAW;
    //     }
    //     node->score += increment;

    //     if (node->parent)
    //     { // make sure we don't play the rootnode, otherwise things will get messy very quickly!
    //         tree->game->revertPlay();
    //     }
    //     // }

    // } while ((node = node->parent) != nullptr);

    // Node<CellT, PawnT> *node = terminalNode;

    // // iterate until the root node, not excluded tho!
    // do
    // {
    //     double increment = INCREMENT_DEFEAT;
    //     if ((int)node->player->getId() == winnerId)
    //     { // victory
    //         increment = INCREMENT_VICTORY;
    //     }
    //     else if (winnerId == -1)
    //     { // draw
    //         increment = INCREMENT_DRAW;
    //     }
    //     node->visits++;

    //     node->score += increment;
    //     if (node->parent)
    //     { // make sure we don't play the rootnode, otherwise things will get messy very quickly!
    //         tree->game->revertPlay(node->targetedCell);
    //     }

    // } while ((node = node->parent) != nullptr);
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
    size_t number_games_played = 0;
    while (!tree->game->isFinished())
    {
        const game::Move<CellT, PawnT> move = getRandomAvailableMoveFromBoard(tree->game->getPlayerToPlay());
        tree->game->play(
            move.pawn,
            move.target);
        ++number_games_played;
    }

    // check the victory
    int winner = tree->game->checkStatus();

    // revert the random game
    while (number_games_played-- > 0)
    {
        tree->game->revertPlay();
    }

    return winner;

    // // save the actions done so we can revert them;
    // std::queue<game::AbstractBoardCell *> playedCells;

    // while (!tree->game->isFinished())
    // {
    //     try
    //     {
    //         game::AbstractBoardCell *cell = getRandomAvailableCellFromBoard();
    //         tree->game->play(
    //             tree->game->getPlayerToPlay(),
    //             cell);
    //         playedCells.push(cell);
    //     }
    //     catch (int code)
    //     {
    //     }
    // }

    // // check the victory
    // int winner = tree->game->checkStatus();

    // // revert the random game
    // while (!playedCells.empty())
    // {
    //     tree->game->revertPlay(playedCells.front());
    //     // remove the element
    //     playedCells.pop();
    // }

    // return winner;
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
        double interestingValue = -std::numeric_limits<double>::max();

        double res = 42;
        // One child must be selected to further develop
        for (Node<CellT, PawnT> *node : ret->childNodes)
        {
            res = formula(
                *ret,
                *node);

            // dbg(res);

            if (res > interestingValue)
            {
                // update ret
                interestingValue = res;
                interestingToReturn = node;
            }
        }

        assert(interestingToReturn != nullptr);
        assert("the Node that should have been returned is still identical to the porevious one, we are looping over the same element " &&
               ret != interestingToReturn);

        ret = interestingToReturn;

        // exclude the root node that doesn't have any action associated...
        if (!interestingToReturn->isRoot)
        {
            doActionOnBoard(*ret);
        }
    }

    return ret;
}

template class MCTS<game::tic_tac_toe::BoardCell, game::tic_tac_toe::Player, game::tic_tac_toe::Player>;
template class MCTS<game::penguin::BoardCell, game::penguin::HumanPlayer, game::penguin::PenguinPawn>;

} // namespace mcts