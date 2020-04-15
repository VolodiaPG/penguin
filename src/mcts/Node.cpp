#include "Node.hpp"

namespace mcts
{
Node::Node(Node *parent,
           const game::Move& move,
           game::AbstractGame<game::AbstractBoardCell, game::AbstractPlayer, game::AbstractPawn<game::AbstractPlayer, game::AbstractBoardCell>> *game)
    : parent(parent),
      _move(move),
      game(game)
{
}

Node::~Node()
{
    for (Node *node : childNodes)
    {
        delete node;
    }
}

double Node::formula(int winsSuccessor, int numberVisitsSuccessor, int numberVisitsFather)
{
    if (numberVisitsSuccessor == 0)
    {
        return std::numeric_limits<double>::max();
    }

    return (double)winsSuccessor / (double)numberVisitsSuccessor + sqrt(2.0 * log((double)numberVisitsFather) / (double)numberVisitsSuccessor);
}

Node *Node::selectBestChildAndDoAction()
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
        Node *temp = ret;
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

        assert(ret != temp);
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

bool Node::doAction()
{
    // do our move
    return game->play(_move.pawn, _move.target);
}

void Node::revertAction()
{
    return game->revertPlay();
}

game::Move Node::getRandomAvailableMove(
    game::AbstractGame<game::AbstractBoardCell, game::AbstractPlayer, game::AbstractPawn<game::AbstractPlayer, game::AbstractBoardCell>> *game,
    const unsigned int player_id)
{
    std::vector<game::Move> moves = game->getAvailableMoves(game->board->getPlayerById(player_id));

    size_t moves_size = moves.size();
    assert(moves_size > 0);

    // random index ranging between 0 and moves.size() not included; (eg. 0 and 3, 3 not included)
    unsigned int index = rand() % moves_size;

    return moves[index];
}

int Node::randomSimulation() const
{
    int ii = 0;
    while (!game->isFinished())
    {
        game::Move random_move = getRandomAvailableMove(game, game->getPlayerToPlay());

        // dbg(random_move.pawn->getId());
        // dbg(((game::penguin::BoardCell *)random_move.cell)->getPosition().x);
        // dbg(((game::penguin::BoardCell *)random_move.cell)->getPosition().y);

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

void Node::backPropagateAndRevertAction(const int winnerId)
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

Node *Node::nodeWithMaxVisits() const
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

Node *Node::randomChooseChildOrDefaultMe()
{
    Node *ret = this;
    if (childNodes.size())
    {
        unsigned int index = rand() % childNodes.size();
        ret = childNodes[index];
    }

    return ret;
}

// void Node::expandNode(std::vector<game::Move>& possibleMove, game::AbstractPlayer *nextPlayer)
// {
//     for (game::Move& move : possibleMove)
//     {
//         Node *node = new Node(this, nextPlayer, move, game);
//         childNodes.push_back(node);
//     }
// }

void Node::expandNode(std::vector<game::Move> possibleMove)
{
    for (game::Move &move : possibleMove)
    {
        Node *node = new Node(this, move, game);
        childNodes.push_back(node);
    }
}

} // namespace mcts