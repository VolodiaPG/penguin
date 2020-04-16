#include <vector>
#include <math.h>
#include <limits>
#include <assert.h>

#include "../game_logic/AbstractBoard.hpp"
#include "../game_logic/AbstractBoardCell.hpp"
#include "../game_logic/AbstractGame.hpp"
#include "../game_logic/AbstractPlayer.hpp"
#include "../game_logic/AbstractPawn.hpp"
#include "Tree.hpp"

#include "Node.hpp"

namespace mcts
{
template <class CellT, class PlayerT, class PawnT>
Node<CellT, PlayerT, PawnT>::Node(
    Node *parent,
    const game::Move<CellT, PawnT> &move,
    game::AbstractGame<CellT, PlayerT, PawnT> *game)
    : parent(parent),
      _move(move),
      game(game)
{
}

template <class CellT, class PlayerT, class PawnT>
Node<CellT, PlayerT, PawnT>::~Node()
{
    for (Node *node : childNodes)
    {
        delete node;
    }
}

template <class CellT, class PlayerT, class PawnT>
double Node<CellT, PlayerT, PawnT>::formula(int winsSuccessor, int numberVisitsSuccessor, int numberVisitsFather)
{
    if (numberVisitsSuccessor == 0)
    {
        return std::numeric_limits<double>::max();
    }

    return (double)winsSuccessor / (double)numberVisitsSuccessor + sqrt(2.0 * log((double)numberVisitsFather) / (double)numberVisitsSuccessor);
}

template <class CellT, class PlayerT, class PawnT>
Node<CellT, PlayerT, PawnT> *Node<CellT, PlayerT, PawnT>::selectBestChildAndDoAction()
{
    Node *ret = this;

    if (ret->_move.target)
    // TODO check if nothing went wrong commenting these multiple lines :)
    // if (parent)
    {
        ret->doAction();
    }

    while (ret->childNodes.size() != 0)
    {
        int parentVisits = ret->visits;

        double max = -std::numeric_limits<double>::max();
        Node<CellT, PlayerT, PawnT> *temp = ret;
        // One child must be selected to further develop
        for (Node *node : ret->childNodes)
        {
            double res = formula(
                node->victories,
                node->visits,
                parentVisits);

            if (res > max)
            {
                // update ret
                max = res;
                temp = node;
            }
        }

        assert("the Node that should have been returned is still identical to the porevious one, we are looping over the same element " &&
               ret != temp);
        ret = temp;

        // exclude the root node that doesn't have any action associated...
        if (ret->_move.target)
        // if (parent)
        {
            ret->doAction();
        }
    }

    return ret;
}

template <class CellT, class PlayerT, class PawnT>
bool Node<CellT, PlayerT, PawnT>::doAction()
{
    // do our move
    return game->play(_move.pawn, _move.target);
}

template <class CellT, class PlayerT, class PawnT>
void Node<CellT, PlayerT, PawnT>::revertAction()
{
    return game->revertPlay();
}

template <class CellT, class PlayerT, class PawnT>
game::Move<CellT, PawnT> Node<CellT, PlayerT, PawnT>::getRandomAvailableMove(
    game::AbstractGame<CellT, PlayerT, PawnT> *game,
    const unsigned int player_id)
{
    std::vector<game::Move<CellT, PawnT>> moves = game->getAvailableMoves(game->board->getPlayerById(player_id));

    size_t moves_size = moves.size();
    assert(moves_size > 0);

    // random index ranging between 0 and moves.size() not included; (eg. 0 and 3, 3 not included)
    unsigned int index = rand() % moves_size;

    return moves[index];
}

template <class CellT, class PlayerT, class PawnT>
int Node<CellT, PlayerT, PawnT>::randomSimulation() const
{
    int ii = 0;
    while (!game->isFinished())
    {
        game::Move<CellT, PawnT> random_move = getRandomAvailableMove(game, game->getPlayerToPlay());

        bool res = game->play(
            random_move.pawn,
            random_move.target);
        assert(res == true);
        ++ii;
    }

    // check the victory
    int winner = game->checkStatus();

    // revert play the random game the number of times we moved
    while (ii-- > 0)
    {
        game->revertPlay();
    }

    return winner;
}

template <class CellT, class PlayerT, class PawnT>
void Node<CellT, PlayerT, PawnT>::backPropagateAndRevertAction(const int winnerId)
{
    ++visits;
    const unsigned int player_id = _move.pawn ? _move.pawn->getOwner()->getId() : 0;
    if (winnerId == (int)player_id)
    {
        victories += 10;
    }
    else if (winnerId == -1)
    {
        victories++;
    }
    // else
    // {
    //     // victories+=20;
    // }

    if (parent != nullptr)
    {
        revertAction();

        // backpropagate again
        parent->backPropagateAndRevertAction(winnerId);
    }
}

template <class CellT, class PlayerT, class PawnT>
Node<CellT, PlayerT, PawnT> *Node<CellT, PlayerT, PawnT>::nodeWithMaxVisits() const
{
    Node *chosen = nullptr;
    int max = -1;

    for (Node *node : childNodes)
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
Node<CellT, PlayerT, PawnT> *Node<CellT, PlayerT, PawnT>::randomChooseChildOrDefaultMe()
{
    Node *ret = this;
    if (childNodes.size())
    {
        unsigned int index = rand() % childNodes.size();
        ret = childNodes[index];
    }

    return ret;
}

template <class CellT, class PlayerT, class PawnT>
void Node<CellT, PlayerT, PawnT>::expandNode(const std::vector<game::Move<CellT, PawnT>>& possibleMove)
{
    for (game::Move<CellT, PawnT> &move : possibleMove)
    {
        Node *node = new Node(this, move, game);
        childNodes.push_back(node);
    }
}

} // namespace mcts